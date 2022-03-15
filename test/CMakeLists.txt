enable_testing()
find_package(Catch2 REQUIRED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

add_executable(ms_pacman_tests ${sources})
target_link_libraries(ms_pacman_tests Catch2::Catch2 lib_ms_pacman)
target_compile_definitions(ms_pacman_tests PUBLIC CATCH_CONFIG_CONSOLE_WIDTH=300)

# This setup the tests on CI. We disable the AI tests
# because you will have to implement them.
add_test(NAME ms_pacman_tests COMMAND ms_pacman_tests)

add_custom_command(TARGET ms_pacman_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/test/data/highscore.txt
        $<TARGET_FILE_DIR:ms_pacman_tests>)
