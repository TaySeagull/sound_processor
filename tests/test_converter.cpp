#include <catch2/catch_test_macros.hpp>
#include "cmd_line_args_2_pipeline_converter.h"
#include "filters/filter_producers.h"
#include "filters/ampl_filter.h"
#include "filters/generator_filter.h"
#include "argument_parser.h"
#include "filters/timestretch_filter.h"


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

TEST_CASE("Converter creates pipeline with ampl filter", "[converter]") {
    CmdLineArgs2PipelineConverter converter;
    converter.addFilterProducer("ampl", FilterProducers::amplFilterCreator);
    
    ArgsHelper args{"sound_processor", "-f", "ampl", "0.5"};
    ArgsParser parser;
    parser.parse(args.argc, args.argv.data());
    
    Pipeline pipeline = converter.createPipeline(parser.getFilterDescriptors());
    
    REQUIRE(pipeline.getFilterNumber() == 1);
    
    Waveform waveform(44100, 1, 16);
    waveform.resize(10);
    for (size_t i = 0; i < 10; ++i) {
        waveform.setSample(i, 1000);
    }
    
    pipeline.apply(&waveform);
    REQUIRE(waveform.getSample(0) == 500);
}

TEST_CASE("Converter creates pipeline with generator sin", "[converter]") {
    CmdLineArgs2PipelineConverter converter;
    converter.addFilterProducer("generator", FilterProducers::generatorFilterCreator);
    
    ArgsHelper args{"sound_processor", "-f", "generator", "sin", "440", "1000"};
    ArgsParser parser;
    parser.parse(args.argc, args.argv.data());
    
    Pipeline pipeline = converter.createPipeline(parser.getFilterDescriptors());
    
    REQUIRE(pipeline.getFilterNumber() == 1);
    
    Waveform waveform(44100, 1, 16);
    pipeline.apply(&waveform);
    
    REQUIRE(waveform.getNumSamples() == 44100);
}

TEST_CASE("Converter creates pipeline with multiple filters", "[converter]") {
    CmdLineArgs2PipelineConverter converter;
    converter.addFilterProducer("ampl", FilterProducers::amplFilterCreator);
    converter.addFilterProducer("timestretch", FilterProducers::timestretchFilterCreator);
    
    ArgsHelper args{
        "sound_processor",
        "-f", "ampl", "0.5",
        "-f", "timestretch", "2.0"
    };
    ArgsParser parser;
    parser.parse(args.argc, args.argv.data());
    
    Pipeline pipeline = converter.createPipeline(parser.getFilterDescriptors());
    
    REQUIRE(pipeline.getFilterNumber() == 2);
}

TEST_CASE("Converter throws error for unknown filter", "[converter]") {
    CmdLineArgs2PipelineConverter converter;
    
    ArgsHelper args{"sound_processor", "-f", "unknown_filter"};
    ArgsParser parser;
    parser.parse(args.argc, args.argv.data());
    
    REQUIRE_THROWS_AS(
        converter.createPipeline(parser.getFilterDescriptors()),
        std::runtime_error
    );
}

TEST_CASE("Converter throws error for invalid parameters", "[converter]") {
    CmdLineArgs2PipelineConverter converter;
    converter.addFilterProducer("ampl", FilterProducers::amplFilterCreator);
    
    ArgsHelper args{"sound_processor", "-f", "ampl"};
    ArgsParser parser;
    parser.parse(args.argc, args.argv.data());
    
    REQUIRE_THROWS_AS(
        converter.createPipeline(parser.getFilterDescriptors()),
        std::logic_error
    );
}

TEST_CASE("Converter handles empty filter list", "[converter]") {
    CmdLineArgs2PipelineConverter converter;
    
    ArgsHelper args{"sound_processor"};
    ArgsParser parser;
    parser.parse(args.argc, args.argv.data());
    
    Pipeline pipeline = converter.createPipeline(parser.getFilterDescriptors());
    
    REQUIRE(pipeline.getFilterNumber() == 0);
}