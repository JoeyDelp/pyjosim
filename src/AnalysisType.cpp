#include "JoSIM/AnalysisType.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {

void analysis_type(py::module &m)
{
    using namespace JoSIM;
    // Expose the two analysis types
    py::enum_<AnalysisType>(m, "AnalysisType")
        .value("Voltage", AnalysisType::Voltage)
        .value("Phase", AnalysisType::Phase);
}

} // namespace pyjosim
