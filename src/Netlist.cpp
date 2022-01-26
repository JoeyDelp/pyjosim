#include "JoSIM/Netlist.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {
void netlist(py::module &m)
{
    using namespace JoSIM;

    // Create Netlist class
    py::class_<Netlist>(m, "Netlist")
        // Expose expand_subcircuit function
        .def("expand_subcircuits", &Netlist::expand_subcircuits)
        // Expose expand_maindesign function
        .def("expand_maindesign", &Netlist::expand_maindesign);
}

} // namespace pyjosim
