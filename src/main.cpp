#include <memory>
#include <vector>
#include <platform_glfw.hpp>
#include <instance.hpp>
#include <surface.hpp>
#include <move_into.hpp>
#include <Logger.hpp>

int main() {
  platform::glfw::init();
  std::unique_ptr<vka::instance> instancePtr{};
  vka::instance_builder{}
    .add_layer(vka::standard_validation)
    .add_extensions(platform::glfw::get_required_instance_extensions())
    .build()
    .map(move_into{instancePtr})
    .map_error([](auto error) {
      multi_logger::get()->critical("Vulkan error creating instance: {}", error); 
      });

  std::unique_ptr<vka::surface> surfacePtr{};
  vka::surface_builder{}
    .width(900)
    .height(900)
    .title("vkaEngine Test app")
    .build(*instancePtr)
    .map(move_into{surfacePtr})
    .map_error([](auto error) {
      multi_logger::get()->critical("Error creating window or surface");
    });
  
  bool shouldClose{};
  while (!shouldClose) {
    shouldClose = platform::glfw::poll_os(*surfacePtr);
  }
}