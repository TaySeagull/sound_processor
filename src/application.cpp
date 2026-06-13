#include "application.h"
#include "filter_producers.h"
#include "wav_reader.h"
#include "wav_writer.h"
#include <iostream>

/**
 * @brief Configures all the filters
 */
void Application::configure() {
    converter_.addFilterProducer("ampl", FilterProducers::amplFilterCreator);
    converter_.addFilterProducer("timestretch", FilterProducers::timestretchFilterCreator);
    converter_.addFilterProducer("silence", FilterProducers::silenceFilterCreator);
    converter_.addFilterProducer("sin", FilterProducers::sinGenFilterCreator);
    converter_.addFilterProducer("am", FilterProducers::amFilterCreator);
    converter_.addFilterProducer("fm", FilterProducers::fmFilterCreator);
}

/**
 * @brief Starts the app
 */
int Application::start(int argc, char* argv[]) {
    ArgsParser parser;
    ArgsParser::Result parseResult = parser.parse(argc, argv);
    
    if (parseResult == ArgsParser::Result::noArgs) {
        parser.printHelp();
        return 0;
    }
    
    if (parseResult == ArgsParser::Result::badArgs) {
        return 1;
    }
    

    Pipeline pipeline = converter_.createPipeline(parser.getFilterDescriptors());
    

    Waveform waveform;

    if (parser.hasInputFile())
    {
        WavReader reader;
        waveform = reader.read(parser.getInputFileName());

    } else {

        waveform = Waveform(Waveform::DEFAULT_SAMPLE_RATE, 
                           Waveform::DEFAULT_CHANNELS_NUMBER, 
                           Waveform::DEFAULT_BITS_PER_SAMPLE);
    }
    

    IFilter::State state = pipeline.apply(&waveform);

    if (state != IFilter::State::ok) {
        std::cerr << "Error applying filters\n";
        return 1;
    }
    

    if (parser.hasOutputFile()) {
        WavWriter writer;
        writer.write(parser.getOutputFileName(), waveform);
    }
    
    return 0;
}