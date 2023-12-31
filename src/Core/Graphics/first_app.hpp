#pragma once

#include "../../../soloud/include/soloud.h"
#include "../../../soloud/include/soloud_wav.h"
#include "lve_descriptors.hpp"
#include "lve_device.hpp"
#include "lve_game_object.hpp"
#include "lve_renderer.hpp"
#include "lve_window.hpp"

// std
#include <memory>
#include <vector>

namespace lve {
class FirstApp {
public:
  static constexpr int WIDTH = 1920;
  static constexpr int HEIGHT = 1080;

  FirstApp();
  ~FirstApp();

  FirstApp(const FirstApp &) = delete;
  FirstApp &operator=(const FirstApp &) = delete;

  void run();

  // Definitions of Soloud variables
  SoLoud::Soloud soloud; // Engine core
  SoLoud::Wav egg1;
  SoLoud::Wav sound1;
  SoLoud::Wav sound2;

  // States
  bool show_demo_window = true;
  bool show_another_window = false;
  bool show_text_editor = false;
  bool show_camera_window = true;
  bool enable_camera = true;

private:
  void loadGameObjects();

  LveWindow lveWindow{WIDTH, HEIGHT, "Vulkan Tutorial"};
  LveDevice lveDevice{lveWindow};
  LveRenderer lveRenderer{lveWindow, lveDevice};

  // note: order of declarations matters
  std::unique_ptr<LveDescriptorPool> globalPool{};
  LveGameObject::Map gameObjects;
};
} // namespace lve
