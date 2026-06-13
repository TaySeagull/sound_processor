#include <stdexcept>
#include <cmath>
#include "waveform.h"

/**
 * @brief Default constructor for Waveform
 */
Waveform::Waveform(): sampleRate_(DEFAULT_SAMPLE_RATE), channels_(DEFAULT_CHANNELS_NUMBER), bitsPerSample_(DEFAULT_BITS_PER_SAMPLE) {}

/**
 * @brief Constructor that creates waveform with specified number of samples
 */
Waveform::Waveform(size_t samplesNumber) {}

/**
 * @brief Constructor that creates waveform with custom parameters.
 */
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

/**
 * @brief Gets the sample value at the specified index
 */
int16_t Waveform::getSample(size_t index) const {
    if (index >= samples_.size()) {
        throw std::out_of_range("Sample index out of range");
    }
    return samples_[index];
}

/**
 * @brief Sets the sample value at the specified index
 */
void Waveform::setSample(size_t index, int16_t value) {
    if (index >= samples_.size()) {
        throw std::out_of_range("Sample index out of range");
    }
    samples_[index] = value;
}

/**
 * @brief Resizes the sample buffer to the specified number of samples
 */
void Waveform::resize(size_t numSamples) {
    samples_.resize(numSamples, 0);
}

/**
 * @brief Clears all samples from the waveform
 */
void Waveform::clear() {
    samples_.clear();
}

/**
 * @brief Appends a single sample to the end of the waveform
 */
void Waveform::appendSample(int16_t sample) {
    samples_.push_back(sample);
}

/**
 * @brief Appends multiple samples to the end of the waveform
 */
void Waveform::appendSamples(const std::vector<int16_t>& newSamples) {
    samples_.insert(samples_.end(), newSamples.begin(), newSamples.end());
}