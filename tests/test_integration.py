from pyjosim import CliOptions, Input, Matrix, Simulation, Output
import matplotlib.pyplot as plt


def josim_cli(args):
    cli = CliOptions(args)
    josim_input = Input(cli.analysis_type, cli.verbose, cli.minimal)
    josim_input.parse_input(cli.cir_file_name)
    parameters = josim_input.parameters

    if len(parameters) > 0:
        parameters.parse()

    josim_input.parse_models()

    netlist = josim_input.netlist
    netlist.expand_subcircuits()
    netlist.expand_maindesign()

    josim_input.identify_simulation()

    matrix = Matrix(josim_input)
    simulation = Simulation(josim_input, matrix)
    output = Output(josim_input, matrix, simulation)

    return output.traces

if __name__ == "__main__":
    result = josim_cli(["./tests/ex_jtl_basic.cir"])
    plt.xlabel(result[0].name)
    plt.ylabel(result[1].name)
    plt.title('ex_jtl_basic.cir')
    plt.plot(result[0].data, result[1].data)
    plt.show()


