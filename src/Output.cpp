#include "JoSIM/Output.hpp"

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<JoSIM::Trace>);

namespace pyjosim {
void output(py::module &m)
{
    using namespace JoSIM;
    
    // Create Trace class
    py::class_<Trace>(m, "Trace")
        // Expose type member
        .def_readonly("type", &Trace::type_)
        // Expose name member
        .def_property_readonly("name", [](const Trace &trace) {
            auto &&name = trace.name_;
            if (name.front() == '"' &&
                name.back() == '"' && name.size() >= 2) {
                return std::string(name.begin() + 1, name.begin() + name.size() - 1);
            }
            return std::string(name);
        })
        // Expose data member
        .def_property_readonly("data", [](Trace &trace) {
            auto &vec = trace.data_;
            double *data = vec.data();
            size_t size = vec.size();
            return py::array_t<double>(size, data);
        }, py::return_value_policy::reference_internal);

    // Expose traces vector
    py::bind_vector<std::vector<Trace>>(m, "Traces");

    // Create Output class
    py::class_<Output>(m, "Output")
        // Initialize output
        .def(py::init([](Input &input, Matrix &matrix, Simulation &simulation) {
                // Create a JoSIM::Output object
                Output output;
                // Call the write_output function
                output.write_output(input, matrix, simulation);
                // Return the output object
                return output;
             }),
             py::keep_alive<1, 2>(), py::keep_alive<1, 3>(),
             py::keep_alive<1, 4>())
        // Expose the output traces member
        .def_readonly("traces", &Output::traces, py::return_value_policy::reference_internal);
}

} // namespace pyjosim
