cmake_minimum_required(VERSION 3.5)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

fetchcontent_declare(
  cglm
  GIT_REPOSITORY https://github.com/recp/cglm.git
  GIT_TAG v0.8.5
  GIT_PROGRESS TRUE
)

if(NOT cglm_POPULATED)
  message("populating cglm")
  fetchcontent_populate(cglm)
  add_subdirectory(${cglm_SOURCE_DIR} ${cglm_BUILD_DIR})
endif()