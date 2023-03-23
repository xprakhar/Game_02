
cmake_minimum_required (VERSION 3.8)

add_executable (Game_02 "Game_02.cpp"  "utils.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game_02 PROPERTY CXX_STANDARD 20)
endif()

target_compile_definitions (Game_02 PUBLIC VK_NO_PROTOTYPES)

target_include_directories (Game_02 PUBLIC "../ext/Volk")
target_link_libraries (Game_02 PUBLIC Volk)
target_link_libraries (Game_02 PUBLIC glfw)


