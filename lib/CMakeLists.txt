cmake_minimum_required (VERSION 3.8)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("glfw")
add_subdirectory("glad")
add_subdirectory("glm")
add_subdirectory("cglm")
add_subdirectory("PerlinNoise")

target_link_libraries(Shitcraft glfw)
target_link_libraries(Shitcraft glad)
include_directories("PerlinNoise/include")
target_link_libraries(Shitcraft cglm)
target_link_libraries(Shitcraft glm::glm)

target_link_libraries(Shitcraft OpenGL::GL)
