#include "JoSIM/ParameterName.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<std::string>);

namespace pyjosim {

void parameter_name(py::module &m)
{
    using namespace JoSIM;

    // Create a ParameterName class
    py::class_<ParameterName>(m, "ParameterName")
        // Initialize the ParameterName class
        .def(py::init<std::string, std::optional<std::string>>())
        // Expose the name member
        .def("name", &ParameterName::name)
        // Expose the subcircuit member
        .def("subcircuit", &ParameterName::subcircuit)
        // Expose the equality operator
        .def("__eq__", &ParameterName::operator==)
        // Expose the hashing algorithm
        .def("__hash__", [](ParameterName &parameter_name) {
            return std::hash<ParameterName>()(parameter_name);
        });
}

} // namespace pyjosim
