find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

find_package(fmt REQUIRED)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(OpenGL REQUIRED COMPONENTS OpenGL GLX)
endif ()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp" "*.hpp")

if (ENABLE_RANGES)
    message(STATUS "${CMAKE_PROJECT_NAME}: Use ranges (NPC_23.cpp)")
    list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/NPC_20.cpp)
else ()
    message(STATUS "${CMAKE_PROJECT_NAME}: Don't use ranges (NPC_20.cpp)")
    list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/NPC_23.cpp)
endif ()

add_library(lib_ms_pacman ${sources})

target_include_directories(lib_ms_pacman PUBLIC include)
target_link_libraries(lib_ms_pacman PUBLIC system-utils fmt::fmt sfml-system sfml-network sfml-graphics sfml-window)


if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(lib_ms_pacman PUBLIC OpenGL::OpenGL OpenGL::GLX)
endif ()
