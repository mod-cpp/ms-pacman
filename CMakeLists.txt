cmake_minimum_required(VERSION 3.16)

include(cmake/vcpkg.cmake)

project(ms-pacman LANGUAGES CXX)

include(cmake/Sanitizers.cmake)
set(ENABLE_SANITIZER_ADDRESS YES)
enable_sanitizers()

include(cmake/ranges.cmake)

if (ENABLE_RANGES)
    set(CMAKE_CXX_STANDARD ${RANGES_CXX})
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

enable_testing()

add_subdirectory(system-utils)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
