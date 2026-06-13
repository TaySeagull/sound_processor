#include "silence_filter.h"

/**
 * @brief Constructor for silence filter
 */
SilenceFilter::SilenceFilter(double startSec, double durationSec)
    : startSec_(startSec), durationSec_(durationSec) {}

IFilter::State SilenceFilter::apply(Waveform* sound) {
    if (!sound || sound->getSamples().empty()) {
        return State::error;
    }

    uint32_t sampleRate = sound->getSampleRate();
    size_t startSample = static_cast<size_t>(startSec_ * sampleRate);
    size_t durationSamples = static_cast<size_t>(durationSec_ * sampleRate);
    size_t endSample = startSample + durationSamples;

    if (startSample >= sound->getSamples().size()) {
        return State::ok;
    }
    if (endSample > sound->getSamples().size()) {
        endSample = sound->getSamples().size();
    }

    std::vector<int16_t>& samples = sound->getSamples();
    for (size_t i = startSample; i < endSample; ++i) {
        samples[i] = 0;
    }

    return State::ok;
}