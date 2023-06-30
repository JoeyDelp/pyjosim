#include "JoSIM/Input.hpp"
#include "JoSIM/Model.hpp"

#include <pybind11/pybind11.h>
//#include <pybind11/stl.h>
namespace py = pybind11;

namespace pyjosim {

void input(py::module &m)
{
    using namespace JoSIM;

    // Create Input class
    py::class_<Input>(m, "Input")
        // Initialization of the Input object
        .def(py::init<AnalysisType,int,bool>())
        // Expose the netlist object
        .def_readwrite("netlist", &Input::netlist)
        // Expose the parameters object
        .def_readwrite("parameters", &Input::parameters)
        // Create a copy of the input for use internally
        .def("clone", [](const Input &input) -> Input { return input; })
        // Expose the parse_models function from the Model class
        .def("parse_models", [](Input &self) {
            for (const auto &model : self.netlist.models) {
                auto pair =
                    std::make_pair(model.second, model.first.second);
                Model::parse_model(pair, self.netlist.models_new,
                                self.parameters);
            }
        })
        // Expose the controls object
        .def_property_readonly("controls", [](Input &input) { 
            return input.controls; 
        })
        // Expose the parse_input funciton
        .def("parse_input", [](Input &self, std::string path) { 
            self.parse_input(path); 
        })
        // Expose the identify_simulation function from Transient class
        .def("identify_simulation", [](Input &self) {
            Transient::identify_simulation(self.controls, self.transSim);
        })
        // Create a clear_all_plots function for use internally
        .def("clear_all_plots", [](Input &input) {
            input.controls.erase(std::remove_if(
                input.controls.begin(), input.controls.end(),
                [](const std::vector<std::string> &str) {
                    for (const auto value : {"PLOT", "SAVE", "PRINT"}) {
                        if (str.front().find(value) != std::string::npos) {
                            return true;
                        }
                    }
                    return false;
                }), input.controls.end());
        })
        // Create a add_plot function for use internally
        .def("add_plot", [](Input &input, const std::string &str) {
            tokens_t t = Misc::tokenize(str);
            t.insert(t.begin(), "PRINT");
            input.controls.emplace_back(t);
        });
}

} // namespace pyjosim
