#include <vector>
#include "filters/lowpass_filter.h"

/**
 * @brief Constructor for LowpassFilter
 */
LowpassFilter::LowpassFilter(int window_size) : _window_size(window_size) {}

/**
 * @brief Applies LowpassFilter
 */
IFilter::State LowpassFilter::apply(Waveform* sound) {
    if (!sound) return State::error;

    const std::vector<int16_t>& oldSamples = sound->getSamples();
    size_t n = oldSamples.size();
    
    if (n == 0 || _window_size <= 1) return State::ok;

    std::vector<int16_t> newSamples(n);
    int halfWindow = _window_size / 2;

    for (size_t i = 0; i < n; ++i) {
        double sum = 0.0;
        
        for (int j = -halfWindow; j <= halfWindow; ++j) {
            int idx = static_cast<int>(i) + j;
            
            if (idx < 0) idx = 0;
            if (idx >= static_cast<int>(n)) idx = static_cast<int>(n) - 1;
            
            sum += oldSamples[idx];
        }
        
        double val = sum / _window_size;

        if (val > 32767.0) val = 32767.0;
        if (val < -32768.0) val = -32768.0;
        
        newSamples[i] = static_cast<int16_t>(val);
    }

    sound->getSamples() = std::move(newSamples);
    return State::ok;
}