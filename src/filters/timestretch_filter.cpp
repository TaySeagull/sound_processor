#include <vector>
#include <cmath>
#include "filters/timestretch_filter.h"

/**
 * @brief Constructor for TimestretchFilter
 */
TimestretchFilter::TimestretchFilter(double factor) : factor_(factor) {}

/**
 * @brief Applies TimestretchFIlter using formulas from the task
 */
IFilter::State TimestretchFilter::apply(Waveform* sound) {
    if (!sound || factor_ <= 0.0) {
        return State::error;
    }

    const std::vector<int16_t>& oldSamples = sound->getSamples();
    size_t oldSize = oldSamples.size();
    
    // newSize = round(oldSize * factor)
    size_t newSize = static_cast<size_t>(std::round(oldSize * factor_));
    
    if (newSize == 0) {
        sound->clear();
        return State::ok;
    }

    std::vector<int16_t> newSamples(newSize);

    for (size_t i = 0; i < newSize; ++i) {

        // pos = i / factor
        double pos = static_cast<double>(i) / factor_;
        size_t l = static_cast<size_t>(pos);
        double frac = pos - l;

        if (l >= oldSize) {
            l = oldSize - 1;
            frac = 0.0;
        }
        
        size_t l_next = l + 1;
        if (l_next >= oldSize) {
            newSamples[i] = oldSamples[l];
        } else {
            double val = oldSamples[l] * (1.0 - frac) + oldSamples[l_next] * frac;
            
            if (val > 32767.0) val = 32767.0;
            if (val < -32768.0) val = -32768.0;
            newSamples[i] = static_cast<int16_t>(val);
        }
    }

    sound->getSamples() = std::move(newSamples);
    return State::ok;
}