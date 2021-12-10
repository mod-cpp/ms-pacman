add_executable(pacman main.cpp)
target_link_libraries(pacman PUBLIC libpacman)

set_target_properties(pacman
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

add_custom_command(TARGET pacman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
           ${PROJECT_SOURCE_DIR}/assets/maze1.png
           ${PROJECT_SOURCE_DIR}/assets/maze2.png
           ${PROJECT_SOURCE_DIR}/assets/maze3.png
           ${PROJECT_SOURCE_DIR}/assets/maze4.png
           ${PROJECT_SOURCE_DIR}/assets/maze.png
           ${PROJECT_SOURCE_DIR}/assets/sprites32.png
           ${PROJECT_SOURCE_DIR}/assets/sprites-ms-32.png
        ${PROJECT_SOURCE_DIR}/assets/font/retro_font.ttf
        $<TARGET_FILE_DIR:pacman>)
