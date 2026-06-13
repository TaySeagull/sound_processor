#pragma once
#include "ifilter.h"

/**
 * @class NormalizeFilter
 * @brief Filter that scales the audio signal so that its maximum absolute 
 *        sample equals a specified fraction of the maximum int16_t value
 */
class NormalizeFilter : public IFilter {
public:
    explicit NormalizeFilter(double peak = 1.0);
    ~NormalizeFilter() override = default;

    State apply(Waveform* sound) override;

    double getPeak() const { return peak_; }

private:
    double peak_;
};