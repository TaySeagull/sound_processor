#include <cmath>
#include "filters/silence_filter.h"

/**
 * @brief Constructor for SilenceFilter
 */
SilenceFilter::SilenceFilter(const std::string& unit, double start, double end)
    : unit_(unit), start_(start), end_(end) {}

/**
 * @brief Applies SilenceFilter
 */
IFilter::State SilenceFilter::apply(Waveform* sound) {
    if (!sound) return State::error;

    uint32_t sampleRate = sound->getSampleRate();
    
    double samplesPerUnit = (unit_ == "ms") ? (sampleRate / 1000.0) : sampleRate;
    size_t startSample = static_cast<size_t>(std::round(start_ * samplesPerUnit));
    size_t endSample = static_cast<size_t>(std::round(end_ * samplesPerUnit));
    
    if (endSample < startSample) return State::error;
    
    size_t silenceLength = endSample - startSample + 1;
    std::vector<int16_t>& samples = sound->getSamples();
    size_t oldSize = samples.size();

    if (startSample >= oldSize) {
        samples.resize(startSample + silenceLength, 0);
        return State::ok;
    }
    
    size_t newSize = oldSize + silenceLength;
    std::vector<int16_t> newSamples(newSize, 0);

    for (size_t i = 0; i < startSample; ++i) {
        newSamples[i] = samples[i];
    }

    for (size_t i = startSample; i < oldSize; ++i) {
        newSamples[i + silenceLength] = samples[i];
    }
    
    samples = std::move(newSamples);
    return State::ok;
}