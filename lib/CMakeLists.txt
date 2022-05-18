find_package(SFML COMPONENTS COMPONENTS window graphics system CONFIG REQUIRED)
find_package(fmt REQUIRED)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(OpenGL REQUIRED COMPONENTS OpenGL GLX)
endif ()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp" "*.hpp")

if (ENABLE_RANGES)
    list(REMOVE_ITEM ${sources} NPC_23.cpp)
else ()
    list(REMOVE_ITEM ${sources} NPC_20.cpp)
endif ()

add_library(lib_ms_pacman ${sources})

target_include_directories(lib_ms_pacman PUBLIC include)
target_link_libraries(lib_ms_pacman PUBLIC system-utils fmt::fmt sfml-graphics)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(lib_ms_pacman PUBLIC OpenGL::OpenGL OpenGL::GLX)
endif ()
