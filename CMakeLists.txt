cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_PREFIX_PATH "~/DEV/vcpkg/installed/arm64-osx/share/")
set(MyVKProject_DIR_ROOT       ${CMAKE_CURRENT_LIST_DIR})
set(MyVKProject_DIR_SOURCES    "${MyVKProject_DIR_ROOT}/src")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(SHADER_OUTPUT_DIR "${CMAKE_BINARY_DIR}/shaders")
set(SHADER_INPUT_DIR "${MyVKProject_DIR_ROOT}/Resources/Shaders")
set(MODEL_INPUT_DIR "${MyVKProject_DIR_ROOT}/Resources/Models")
set(MODEL_OUTPUT_DIR "${CMAKE_BINARY_DIR}/models")

project(MyVKProject 
    LANGUAGES CXX C
)

# Sources
macro(MyVKProject_FILES_APPEND)
    file(GLOB_RECURSE FILES_APPEND CONFIGURE_DEPENDS ${ARGV})
    list(APPEND MyVKProject_SOURCES ${FILES_APPEND})
endmacro()
macro(MyVKProject_SOURCES_APPEND)
    MyVKProject_FILES_APPEND(${ARGV0}/*.h)
    MyVKProject_FILES_APPEND(${ARGV0}/*.cpp)
endmacro()

MyVKProject_SOURCES_APPEND(${MyVKProject_DIR_SOURCES})

# Shaders
## Compile shaders
file(GLOB_RECURSE SHADER_SOURCES "${SHADER_INPUT_DIR}/*.frag" "${SHADER_INPUT_DIR}/*.vert")
foreach(SHADER_SOURCE ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER_SOURCE} NAME)
    set(SHADER_OUTPUT "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv")
    add_custom_command(
        OUTPUT ${SHADER_OUTPUT}
        COMMAND glslc ${SHADER_SOURCE} -o ${SHADER_OUTPUT}
        DEPENDS ${SHADER_SOURCE}
    )
    list(APPEND SHADER_OUTPUTS ${SHADER_OUTPUT})
endforeach()

add_custom_target(
    Shaders ALL
    DEPENDS ${SHADER_OUTPUTS}
)

# Models
# Create the destination directory in the build directory
add_custom_command(
    OUTPUT ${MODEL_OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${MODEL_OUTPUT_DIR}
)

# Copy the directory and its contents using a custom target
add_custom_target(CopyModels
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${MODEL_INPUT_DIR} ${MODEL_OUTPUT_DIR}
    DEPENDS ${MODEL_OUTPUT_DIR}
) 

# Soloud
add_subdirectory("soloud/contrib/")


add_executable(
    ${PROJECT_NAME}
    ${MyVKProject_SOURCES}
)

add_dependencies(
    ${PROJECT_NAME}
    CopyModels
)


find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)

find_package(tinyobjloader CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyobjloader::tinyobjloader)

find_package(OpenAL CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenAL::OpenAL "-framework OpenAL")