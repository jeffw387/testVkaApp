cmake_minimum_required(VERSION 3.10)

project(testVkaApp LANGUAGES CXX)

add_subdirectory(external/vkaEngine)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
  vkaEngine)
target_compile_features(main PRIVATE cxx_std_17)