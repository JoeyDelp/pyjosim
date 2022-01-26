include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

CPMAddPackage(
  NAME pybind11
  GITHUB_REPOSITORY pybind/pybind11
  VERSION 2.9.0
)

CPMAddPackage(
  NAME josim
  GITHUB_REPOSITORY JoeyDelp/JoSIM
  GIT_TAG master
  OPTIONS
    "MAKING_STATIC_BUILD ON"
)