#pragma once
#include <vector>
#include <cstdint>

class Waveform {
public:
    // task's constants
    static constexpr uint16_t DEFAULT_CHANNELS_NUMBER = 1;
    static constexpr uint32_t DEFAULT_SAMPLE_RATE = 44100;
    static constexpr uint16_t DEFAULT_BITS_PER_SAMPLE = 16;

    // Constructors
    Waveform();
    Waveform(uint32_t sampleRate_, uint16_t channels_, uint16_t bitsPerSample_);
    Waveform(size_t samplesNumber);

    // Getters
    uint16_t getChannels() const { return channels_; }
    uint32_t getSampleRate() const { return sampleRate_; }
    uint16_t getBitsPerSample() const { return bitsPerSample_; }

    // All samples
    size_t getNumSamples() const { return samples_.size(); }
    const std::vector<int16_t>& getSamples() const { return samples_; }
    std::vector<int16_t>& getSamples() { return samples_; }
    
    // One sample
    int16_t getSample(size_t index) const;
    void setSample(size_t index, int16_t value);
    
    // Change size
    void resize(size_t numSamples);
    void clear();
    
    // Add sample
    void appendSample(int16_t sample);
    void appendSamples(const std::vector<int16_t>& newSamples);

private:
    std::vector<int16_t> samples_;
    uint16_t channels_;
    uint32_t sampleRate_;
    uint16_t bitsPerSample_;
};