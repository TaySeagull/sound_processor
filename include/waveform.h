#pragma once
#include <vector>
#include <cstdint>

// TODO: скипать метаданные

/**
 * @class Waveform
 * @brief A class for the wav file structure
 */
class Waveform {
public:
    static constexpr uint16_t DEFAULT_CHANNELS_NUMBER = 1;
    static constexpr uint32_t DEFAULT_SAMPLE_RATE = 44100;
    static constexpr uint16_t DEFAULT_BITS_PER_SAMPLE = 16;

    Waveform();
    Waveform(uint32_t sampleRate_, uint16_t channels_, uint16_t bitsPerSample_);
    Waveform(size_t samplesNumber);

    uint16_t getChannels() const { return channels_; }
    uint32_t getSampleRate() const { return sampleRate_; }
    uint16_t getBitsPerSample() const { return bitsPerSample_; }

    size_t getNumSamples() const { return samples_.size(); }
    const std::vector<int16_t>& getSamples() const { return samples_; }
    std::vector<int16_t>& getSamples() { return samples_; }
    
    int16_t getSample(size_t index) const;
    void setSample(size_t index, int16_t value);

    void resize(size_t numSamples);
    void clear();

    void appendSample(int16_t sample);
    void appendSamples(const std::vector<int16_t>& newSamples);

private:
    std::vector<int16_t> samples_;
    uint16_t channels_;
    uint32_t sampleRate_;
    uint16_t bitsPerSample_;
};