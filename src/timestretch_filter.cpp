#include "timestretch_filter.h"
#include <cmath>
#include <vector>

/**
 * @brief Constructor for timestretch filter
 */
TimestretchFilter::TimestretchFilter(double factor) : factor_(factor) {}

/**
 * @brief Applies timestretch filter
 * @details The method of linear interpolation
 * 
 * So, imagine we have 2 dots of sound (0 and 1). We need to find the dot between them to
 * make the soud steady. 
 * idx1 = 0
 * idx2 = 1
 * fraction = 0.5  // is the time we want to achieve
 * 
 * val = samples[0] * (1.0 - 0.5) + samples[1] * 0.5 = 150
 * 
 */
IFilter::State TimestretchFilter::apply(Waveform* sound) {
    if (!sound) {
        return State::error;
    }

    if (factor_ <= 0.0) {
        return State::error;
    }

    std::vector<int16_t>& samples = sound->getSamples();
    size_t oldSize = samples.size();
    
    size_t newSize = static_cast<size_t>(std::round(oldSize / factor_));
    
    if (newSize == 0) {
        samples.clear();
        return State::ok;
    }

    std::vector<int16_t> newSamples(newSize);

    for (size_t i = 0; i < newSize; ++i) {
        double srcIndex = i * factor_;
        
        size_t idx1 = static_cast<size_t>(srcIndex);
        size_t idx2 = idx1 + 1;
        
        double fraction = srcIndex - idx1;

        if (idx2 >= oldSize) {
            idx2 = idx1;
            fraction = 0.0;
        }

        double val = samples[idx1] * (1.0 - fraction) + samples[idx2] * fraction;
        
        if (val > 32767.0) val = 32767.0;
        if (val < -32768.0) val = -32768.0;
        
        newSamples[i] = static_cast<int16_t>(val);
    }

    samples = std::move(newSamples);

    return State::ok;
}