cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_PREFIX_PATH "~/DEV/vcpkg/installed/arm64-osx/share/")
set(MyVKProject_DIR_ROOT       ${CMAKE_CURRENT_LIST_DIR})
set(MyVKProject_DIR_SOURCES    "${MyVKProject_DIR_ROOT}/src")
set(SHADER_OUTPUT_DIR "${CMAKE_BINARY_DIR}/shaders")

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
#file(GLOB_RECURSE SHADER_SOURCES "${MyVKProject_DIR_SOURCES}/*.frag" "${MyVKProject_DIR_SOURCES}/*.vert")
#foreach(SHADER_SOURCE ${SHADER_SOURCES})
#    get_filename_component(SHADER_NAME ${SHADER_SOURCE} NAME)
#    set(SHADER_OUTPUT "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv")
#    add_custom_command(
#        OUTPUT ${SHADER_OUTPUT}
#        COMMAND glslc ${SHADER_SOURCE} -o ${SHADER_OUTPUT}
#        DEPENDS ${SHADER_SOURCE}
#    )
#    list(APPEND SHADER_OUTPUTS ${SHADER_OUTPUT})
#endforeach()

#add_custom_target(
#    Shaders ALL
#    DEPENDS ${SHADER_OUTPUTS}
#)

add_executable(
    ${PROJECT_NAME}
    ${MyVKProject_SOURCES}
)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
