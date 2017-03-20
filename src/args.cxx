#include <cxxopts.hpp>
#include <sys_config.hpp>

void ProcessArgs(int argc, char *argv[]) {
    cxxopts::Options options("smol16", "A 16bit style fantasy console");
    options.add_options()
        ("help", "Print help")
        ("i,input", "Input", cxxopts::value<std::string>())
        ("nographics", "Do not initialise graphics")
        ;

    options.parse_positional({"input", "output", "positional"});
    options.parse(argc, argv);

    if (options.count("help")) { // Display help
        std::cout << options.help({""}) << std::endl;
        exit(0);
    }
    if (options.count("nographics")) {
        g_config.noGraphics = true;
    }
    if (options.count("input")) { // Get cart name
        g_config.cart_path = options["input"].as<std::string>();
    } else {
        g_config.cart_path = "carts/editor";
    }
}
