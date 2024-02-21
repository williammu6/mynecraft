# cmake_minimum_required(VERSION 3.24)
cmake_minimum_required(VERSION 3.5)
project(Mynecraft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
endif()

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++20-designator")

file(GLOB_RECURSE src CONFIGURE_DEPENDS "*src/*.hpp" "src/*.cpp")

add_executable(Mynecraft ${src})
add_compile_options(-Wc++20-designator)

add_subdirectory("lib/glfw")
add_subdirectory("lib/glad")
add_subdirectory("lib/glm")
add_subdirectory("lib/PerlinNoise")

find_package(OpenGL REQUIRED)

link_directories("/opt/homebrew/lib")
include_directories("/opt/homebrew/include")
include_directories("lib/PerlinNoise/include")

target_link_libraries(Mynecraft glfw)
target_link_libraries(Mynecraft glad)
target_link_libraries(Mynecraft glm::glm)
target_link_libraries(Mynecraft OpenGL::GL)

include(ExternalProject)

find_package(Python COMPONENTS Interpreter Development)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # For MSVC, you might want to adjust these flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
endif()

