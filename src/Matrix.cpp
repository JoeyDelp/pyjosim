#include "./scoped_cout_null.hpp"

#include "JoSIM/Matrix.hpp"

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {
void matrix(py::module &m)
{
    using namespace JoSIM;

    // Create Matrix class
    py::class_<Matrix>(m, "Matrix")
        // Initialize matrix class
        .def(py::init([](Input &input) {
                scoped_cout_null cout;
                py::scoped_estream_redirect cerr;
                // Create JoSIM::Matrix object
                Matrix matrix;
                // Run create_matrix function with input
                matrix.create_matrix(input);
                // Run find_relevant_traces function
                find_relevant_traces(input, matrix);
                // Return the matrix object
                return matrix;
            }),
            py::keep_alive<1, 2>());
}

} // namespace pyjosim
