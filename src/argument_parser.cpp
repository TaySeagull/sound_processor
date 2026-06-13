#include <iostream>
#include <cstring>
#include "argument_parser.h"

/**
 * @brief Parses command line arguments
 */
ArgsParser::Result ArgsParser::parse(int argc, char* argv[]) {
    inputFileName_ = nullptr;
    outputFileName_ = nullptr;
    filterDescriptors_.clear();

    if (argc == 1) {
        return Result::noArgs;
    }

    int idx = 1;
    while (idx < argc) {
        const char* arg = argv[idx];

        if (std::strcmp(arg, "-i") == 0) {
            if (idx + 1 >= argc) {
                std::cerr << "Error: -i flag requires an argument\n";
                return Result::badArgs;
            }

            if (inputFileName_ != nullptr) {
                std::cerr << "Error: -i flag specified multiple times\n";
                return Result::badArgs;
            }

            inputFileName_ = argv[idx + 1];
            idx += 2;
        }
        else if (std::strcmp(arg, "-o") == 0) {
            if (idx + 1 >= argc) {
                std::cerr << "Error: -o flag requires a file name argument\n";
                return Result::badArgs;
            }

            if (outputFileName_ != nullptr) {
                std::cerr << "Error: -o flag specified multiple times\n";
                return Result::badArgs;
            }

            outputFileName_ = argv[idx + 1];
            idx += 2;
        }
        else if (std::strcmp(arg, "-f") == 0) {
            if (idx + 1 >= argc) {
                std::cerr << "Error: -f flag requires a filter name argument\n";
                return Result::badArgs;
            }

            if (isFlag(argv[idx + 1])) {
                std::cerr << "Error: -f flag requires a filter name, not another flag\n";
                return Result::badArgs;
            }

            FilterDescriptor descriptor;
            descriptor.name = argv[idx + 1];
            idx += 2;

            while (idx < argc && !isFlag(argv[idx])) {
                descriptor.params.push_back(argv[idx]);
                idx++;
            }

            filterDescriptors_.push_back(descriptor);
        }
        else {
            std::cerr << "Error: unknown argument '" << arg << "'\n";
            return Result::badArgs;
        }
    }

    return Result::ok;
}

/**
 * @brief Prints help
 */
void ArgsParser::printHelp() const {
    std::cout << "Sound Processor\n";
    std::cout << "Usage:\n";
    std::cout << "  sound_processor [options]\n";
    std::cout << "Options:\n";
    std::cout << "  -i <file>     Input WAV file\n";
    std::cout << "  -o <file>     Output WAV file\n";
    std::cout << "  -f <name> [params...]  Apply filter with given name and parameters\n";
    std::cout << "If no arguments are provided, this help is shown.\n";
}

/**
 * @brief Checks whether a string is a command line flag (starts with '-').
 */
bool ArgsParser::isFlag(const char* arg) const {
    return arg[0] == '-';
}