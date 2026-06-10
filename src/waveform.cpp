#include <stdexcept>
#include <cmath>
#include "waveform.h"

Waveform::Waveform(): sampleRate_(DEFAULT_SAMPLE_RATE), channels_(DEFAULT_CHANNELS_NUMBER), bitsPerSample_(DEFAULT_BITS_PER_SAMPLE) {}

Waveform::Waveform(size_t samplesNumber) {}

Waveform::Waveform(uint32_t sampleRate, uint16_t channels, uint16_t bitsPerSample): sampleRate_(sampleRate), channels_(channels), bitsPerSample_(bitsPerSample)
{
    if (sampleRate == 0) {
        throw std::invalid_argument("Sample rate must be greater than 0");
    }
    if (channels == 0) {
        throw std::invalid_argument("Number of channels must be greater than 0");
    }
    if (bitsPerSample == 0) {
        throw std::invalid_argument("Bits per sample must be greater than 0");
    }
}

int16_t Waveform::getSample(size_t index) const {
    if (index >= samples_.size()) {
        throw std::out_of_range("Sample index out of range");
    }
    return samples_[index];
}

void Waveform::setSample(size_t index, int16_t value) {
    if (index >= samples_.size()) {
        throw std::out_of_range("Sample index out of range");
    }
    samples_[index] = value;
}

void Waveform::resize(size_t numSamples) {
    samples_.resize(numSamples, 0);
}

void Waveform::clear() {
    samples_.clear();
}

void Waveform::appendSample(int16_t sample) {
    samples_.push_back(sample);
}

void Waveform::appendSamples(const std::vector<int16_t>& newSamples) {
    samples_.insert(samples_.end(), newSamples.begin(), newSamples.end());
}