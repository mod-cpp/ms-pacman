find_package(SFML COMPONENTS COMPONENTS window graphics CONFIG REQUIRED)

add_library(system-utils ${sources})

target_include_directories(system-utils PUBLIC .)
target_link_libraries(system-utils PUBLIC sfml-graphics)

target_sources(system-utils PRIVATE User.hpp Scaling.hpp)


if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_sources(system-utils PRIVATE Scaling.mm)
else()
    target_sources(system-utils PRIVATE Scaling.cpp)
endif ()

if(WIN32)
    target_sources(system-utils PRIVATE UserWin32.cpp)
    target_link_libraries(system-utils PUBLIC advapi32)
else()
    target_sources(system-utils PRIVATE UserPosix.cpp)
endif()
