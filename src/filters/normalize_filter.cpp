#include <cmath>
#include "filters/normalize_filter.h"

/**
 * @brief Constructor for NormalizeFilter
 */
NormalizeFilter::NormalizeFilter(double peak) : peak_(peak) {}

/**
 * @brief Applises NormalizeFilter
 */
IFilter::State NormalizeFilter::apply(Waveform* sound) {
    if (!sound) return State::error;

    std::vector<int16_t>& samples = sound->getSamples();
    if (samples.empty()) return State::ok;

    int16_t currentPeak = 0;
    for (int16_t s : samples) {
        int16_t absS = std::abs(s);
        if (absS > currentPeak) {
            currentPeak = absS;
        }
    }

    if (currentPeak == 0) return State::ok;

    double scale = (peak_ * 32767.0) / currentPeak;

    for (size_t i = 0; i < samples.size(); ++i) {
        double val = samples[i] * scale;
        
        if (val > 32767.0) val = 32767.0;
        if (val < -32768.0) val = -32768.0;
        
        samples[i] = static_cast<int16_t>(val);
    }

    return State::ok;
}