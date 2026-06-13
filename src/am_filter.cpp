#include "am_filter.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

/**
 * @brief Constructor for am filter
 */
AmplitudeModulationFilter::AmplitudeModulationFilter(double amplitude, double carrierFreq, double modFreq, double modIndex, double durationMs)
    : amplitude_(amplitude), carrierFreq_(carrierFreq), modFreq_(modFreq), modIndex_(modIndex), durationMs_(durationMs) {}

/**
 * @brief Applies am filter
 */
IFilter::State AmplitudeModulationFilter::apply(Waveform* sound) {
    if (!sound) return State::error;

    uint32_t sampleRate = sound->getSampleRate();
    size_t numSamples = static_cast<size_t>((durationMs_ / 1000.0) * sampleRate);
    
    sound->clear();
    sound->resize(numSamples);
    
    std::vector<int16_t>& samples = sound->getSamples();
    double maxAmpl = 32767.0 * amplitude_;
    
    for (size_t i = 0; i < numSamples; ++i) {
        double t = static_cast<double>(i) / sampleRate;
        
        // Formula(1) A * (1 + m * sin(2 * pi * f_m * t)) * sin(2 * pi * f_c * t)
        double modulator = 1.0 + modIndex_ * std::sin(2.0 * PI * modFreq_ * t);
        double carrier = std::sin(2.0 * PI * carrierFreq_ * t);
        
        double val = maxAmpl * modulator * carrier;
        
        if (val > 32767.0) val = 32767.0;
        if (val < -32768.0) val = -32768.0;
        
        samples[i] = static_cast<int16_t>(val);
    }
    
    return State::ok;
}