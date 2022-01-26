cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(pyjosim
        VERSION 2.6
                DESCRIPTION
                "Python bindings for JoSIM"
                HOMEPAGE_URL
                "https://github.com/JoeyDelp/pyjosim"
        LANGUAGES CXX)

# Include cmake scripts
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/warnings.cmake)

pybind11_add_module(pyjosim
                    SHARED
                    THIN_LTO
                    src/AnalysisType.cpp
                    src/CliOptions.cpp
                    src/Input.cpp
                    src/Matrix.cpp
                    src/Netlist.cpp
                    src/Output.cpp
                    src/ParameterName.cpp
                    src/Parameters.cpp
                    src/Simulation.cpp
                    src/pyjosim.cpp
                    src/stl.cpp
  )

target_compile_features(pyjosim PUBLIC cxx_std_17)

set_target_properties(pyjosim PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

# Add include directories
target_include_directories(
  pyjosim
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

target_link_libraries(pyjosim PRIVATE josim::josim)
target_link_libraries(pyjosim PRIVATE suitesparse::klu)
target_link_libraries(pyjosim PRIVATE superlu)
target_link_libraries(pyjosim PRIVATE cblas)
