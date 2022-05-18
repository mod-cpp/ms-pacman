cmake_minimum_required(VERSION 3.16)

include(cmake/vcpkg.cmake)

project(ms-pacman LANGUAGES CXX)

option(ENABLE_RANGES "Enable ranges" FALSE)

if (WIN32)
    set(ENABLE_RANGES YES)
    set(RANGES_CXX 23)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "${CMAKE_PROJECT_NAME}: GCC version is ${CMAKE_CXX_COMPILER_VERSION}")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 10.1)
        set(ENABLE_RANGES YES)
        set(RANGES_CXX 20)
    endif ()
endif ()

if (ENABLE_RANGES)
    message(STATUS "${CMAKE_PROJECT_NAME}: Enabling use of ranges")
else ()
    message(STATUS "${CMAKE_PROJECT_NAME}: Disabling use of ranges")
endif ()

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
