find_package(Catch2 REQUIRED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

add_executable(ms_pacman_tests ${sources})
target_link_libraries(ms_pacman_tests Catch2::Catch2 lib_ms_pacman)
target_compile_definitions(ms_pacman_tests PUBLIC CATCH_CONFIG_CONSOLE_WIDTH=300)

include(Catch)
catch_discover_tests(ms_pacman_tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/)
