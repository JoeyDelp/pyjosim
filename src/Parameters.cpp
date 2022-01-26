#include "JoSIM/Parameters.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(
    std::unordered_map<JoSIM::ParameterName, JoSIM::Parameter>);

namespace pyjosim {

void parameters(py::module &m)
{
    using namespace JoSIM;
    namespace py = pybind11;

    // Create a Parameters map object
    py::bind_map<std::unordered_map<ParameterName, Parameter>>(m, "Parameters")
        // Expose the parse_parameters function
        .def("parse", [](std::unordered_map<ParameterName, Parameter> &self) {
            parse_parameters(self);
        });

    // Create a Parameter class
    py::class_<Parameter>(m, "Parameter")
        // Initialize the Parameter class
        .def(py::init())
        // Expose the set_expression function
        .def("set_expression", &Parameter::set_expression)
        // Expose the set_value function
        .def("set_value", &Parameter::set_value)
        // Expose the get_expression function
        .def("get_expression", &Parameter::get_expression)
        // Expose the get_value function
        .def("get_value", &Parameter::get_value);
}

} // namespace pyjosim
