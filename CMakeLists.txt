# cmake_minimum_required(VERSION 3.24)
cmake_minimum_required(VERSION 3.5)
project(Shitcraft)

set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE src CONFIGURE_DEPENDS "*src/*.hpp" "src/*.cpp")

add_executable(Shitcraft ${src})

add_subdirectory("lib/glfw")
add_subdirectory("lib/glad")
add_subdirectory("lib/glm")
add_subdirectory("lib/PerlinNoise")

find_package(OpenGL REQUIRED)


link_directories("/opt/homebrew/lib")
include_directories("/opt/homebrew/include")
include_directories("lib/PerlinNoise/include")

target_link_libraries(Shitcraft glfw)
target_link_libraries(Shitcraft glad)
target_link_libraries(Shitcraft glm::glm)
target_link_libraries(Shitcraft  OpenGL::GL)


include(ExternalProject)

find_package(Python COMPONENTS Interpreter Development)