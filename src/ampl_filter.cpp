#include "ampl_filter.h"

/**
 * @brief Constructor for ampl_filter
 */
AmplFilter::AmplFilter(double ampl): ampl_(ampl) {}

/**
 * @brief Applies ampl filter
 */
IFilter::State AmplFilter::apply(Waveform* sound) {
    if (!sound) {
        return State::error;
    }

    std::vector<int16_t>& samples = sound->getSamples();
    
    for (size_t i = 0; i < samples.size(); ++i) {
        double val = static_cast<double>(samples[i]) * ampl_; // double cause we don't want to lose accuracy
        
        if (val > 32767.0) val = 32767.0;
        if (val < -32768.0) val = -32768.0;
        
        samples[i] = static_cast<int16_t>(val);
    }
    
    return State::ok;
}