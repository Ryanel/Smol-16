#include <cxxopts.hpp>
#include "includes/config.hpp"

void ProcessArgs(int argc, char *argv[])
{
    cxxopts::Options options("sasm", "Assembler for Smol-16");
    options.add_options()
        ("help", "Print help")
        ("i,input", "Input", cxxopts::value<std::string>())
    ;

    options.parse_positional({ "input", "output", "positional" });
    options.parse(argc, argv);

    if (options.count("help"))   // Display help
    {
        std::cout << options.help({ "" }) << std::endl;
        exit(0);
    }
}
