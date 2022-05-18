option(ENABLE_RANGES "Enable ranges" FALSE)

if (WIN32)
    set(ENABLE_RANGES YES)
endif ()

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 10.1)
    set(ENABLE_RANGES YES)
endif()

if (ENABLE_RANGES)
    message(STATUS "${CMAKE_PROJECT_NAME}: Enabling use of ranges")
endif ()
