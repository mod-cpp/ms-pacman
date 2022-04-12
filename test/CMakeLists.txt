find_package(Catch2 REQUIRED)

file(GLOB unit_tests_sources CONFIGURE_DEPENDS "unit_tests/*.cpp")
add_executable(ms_pacman_unit_tests ${unit_tests_sources})
target_link_libraries(ms_pacman_unit_tests Catch2::Catch2 lib_ms_pacman)
target_compile_definitions(ms_pacman_unit_tests PUBLIC CATCH_CONFIG_CONSOLE_WIDTH=300)

file(GLOB exercises_sources CONFIGURE_DEPENDS "exercises/*.cpp")
add_executable(ms_pacman_exercises ${exercises_sources})
target_link_libraries(ms_pacman_exercises Catch2::Catch2 lib_ms_pacman)
target_compile_definitions(ms_pacman_exercises PUBLIC CATCH_CONFIG_CONSOLE_WIDTH=300)

include(Catch)
catch_discover_tests(ms_pacman_unit_tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/)
catch_discover_tests(ms_pacman_exercises WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/)
