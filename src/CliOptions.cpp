#include "JoSIM/CliOptions.hpp"

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {

void cli_options(py::module &m)
{
    using namespace JoSIM;

    // Create a python class called CliOptions
    py::class_<CliOptions>(m, "CliOptions")
        // Initialisation of the variable takes a vector of strings (arguments)
        .def(py::init([](std::vector<std::string> args) {
            // In case of help
            py::scoped_ostream_redirect cout;
            py::scoped_estream_redirect cerr;

            // Convert vector of strings to argc, argv
            int argc = args.size() + 1;
            // First argument is always the program name
            const char *josim_cstr = "JoSIM";
            auto argv = std::make_unique<const char *[]>(argc);

            argv[0] = josim_cstr;
            // Rest of the arguments come from the initialization of the CliOptions class
            for (std::size_t i = 0; i < args.size(); i++)
                argv[i + 1] = args[i].c_str();
            // CliOptions::parse(int argc, const char** argv) function
            return CliOptions::parse(argc, argv.get());
        }))
        // Expose the public member cir_file_name
        .def_readonly("cir_file_name", &CliOptions::cir_file_name)
        // Expose the public member output_file
        .def_readonly("output_file_name", &CliOptions::output_file)
        // Expose the public member analysis_type
        .def_readonly("analysis_type", &CliOptions::analysis_type)
        // Expose the public member verbose
        .def_readonly("verbose", &CliOptions::verbose)
        // Expose the public member SLU
        .def_readonly("slu", &CliOptions::SLU)
        // Expose the public member minimal
        .def_readonly("minimal", &CliOptions::minimal)
        // Expose the public member parallel
        .def_readonly("parallel", &CliOptions::parallel)
        // Expose the function CliOptions::display_help()
        .def_static("display_help", []() {
            py::scoped_ostream_redirect cout;
            py::scoped_estream_redirect cerr;
            CliOptions::display_help();
        })
        // Expose the function CliOptions::version_info()
        .def_static("version_info", []() {
            py::scoped_ostream_redirect cout;
            py::scoped_estream_redirect cerr;
            CliOptions::version_info();
        });
}

} // namespace pyjosim
