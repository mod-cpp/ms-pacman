find_package(Catch2 REQUIRED)

file(GLOB benchmarks_sources CONFIGURE_DEPENDS "benchmarks/*.cpp")
add_executable(ms_pacman_benchmarks ${benchmarks_sources})
target_link_libraries(ms_pacman_benchmarks Catch2::Catch2 lib_ms_pacman)
target_compile_definitions(ms_pacman_benchmarks PUBLIC)

add_custom_command(TARGET ms_pacman_benchmarks POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/test/data/book.txt
        $<TARGET_FILE_DIR:ms_pacman_benchmarks>)

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
