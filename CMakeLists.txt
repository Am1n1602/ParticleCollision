cmake_minimum_required(VERSION 3.15)

project(RandomCollision)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

# Add the executable
add_executable(RandomCollision Source.cpp)

# Set the C++ standard
set_target_properties(RandomCollision PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)


# Link the raylib library
target_link_libraries(RandomCollision PRIVATE raylib)

# Add additional compiler options if needed
if (MSVC)
    target_compile_options(RandomCollision PRIVATE /W4)
else()
    target_compile_options(RandomCollision PRIVATE -Wall -Wextra -pedantic)
endif()
