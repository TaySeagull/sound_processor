#include <catch2/catch_test_macros.hpp>
#include "argument_parser.h"
#include <cstring>

struct ArgsHelper {
    std::vector<char*> argv;
    int argc;

    ArgsHelper(std::initializer_list<const char*> args) {
        for (const char* arg : args) {
            argv.push_back(const_cast<char*>(arg));
        }
        argc = static_cast<int>(argv.size());
    }
};

TEST_CASE("ArgsParser with no arguments", "[args_parser]") {
    ArgsParser parser;
    ArgsHelper args{"sound_processor"};
    
    REQUIRE(parser.parse(args.argc, args.argv.data()) == ArgsParser::Result::noArgs);
}

TEST_CASE("ArgsParser parses input and output files", "[args_parser]") {
    ArgsParser parser;
    ArgsHelper args{"sound_processor", "-i", "input.wav", "-o", "output.wav"};
    
    REQUIRE(parser.parse(args.argc, args.argv.data()) == ArgsParser::Result::ok);
    REQUIRE(std::strcmp(parser.getInputFileName(), "input.wav") == 0);
    REQUIRE(std::strcmp(parser.getOutputFileName(), "output.wav") == 0);
    REQUIRE(parser.hasFilters() == false);
}

TEST_CASE("ArgsParser parses a single filter without parameters", "[args_parser]") {
    ArgsParser parser;
    ArgsHelper args{"sound_processor", "-f", "ampl"};
    
    REQUIRE(parser.parse(args.argc, args.argv.data()) == ArgsParser::Result::ok);
    REQUIRE(parser.hasFilters() == true);
    REQUIRE(parser.getFilterDescriptors().size() == 1);
    REQUIRE(std::strcmp(parser.getFilterDescriptors()[0].name, "ampl") == 0);
    REQUIRE(parser.getFilterDescriptors()[0].params.empty() == true);
}

TEST_CASE("ArgsParser parses a filter with parameters", "[args_parser]") {
    ArgsParser parser;
    ArgsHelper args{"sound_processor", "-f", "ampl", "0.8"};
    
    REQUIRE(parser.parse(args.argc, args.argv.data()) == ArgsParser::Result::ok);
    REQUIRE(parser.getFilterDescriptors().size() == 1);
    REQUIRE(std::strcmp(parser.getFilterDescriptors()[0].name, "ampl") == 0);
    REQUIRE(parser.getFilterDescriptors()[0].params.size() == 1);
    REQUIRE(std::strcmp(parser.getFilterDescriptors()[0].params[0], "0.8") == 0);
}