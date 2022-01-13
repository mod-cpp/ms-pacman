add_executable(ms_pacman main.cpp)
target_link_libraries(ms_pacman PUBLIC lib_ms_pacman)

set_target_properties(ms_pacman
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

add_custom_command(TARGET ms_pacman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
           ${PROJECT_SOURCE_DIR}/assets/maze1.png
           ${PROJECT_SOURCE_DIR}/assets/maze2.png
           ${PROJECT_SOURCE_DIR}/assets/maze3.png
           ${PROJECT_SOURCE_DIR}/assets/maze4.png
           ${PROJECT_SOURCE_DIR}/assets/sprites-ms-32.png
        ${PROJECT_SOURCE_DIR}/assets/font/retro_font.ttf
        $<TARGET_FILE_DIR:ms_pacman>)
