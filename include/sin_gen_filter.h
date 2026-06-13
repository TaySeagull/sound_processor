#pragma once
#include "abstract_generator_filter.h"

/**
 * @brief Generates a sine wave with specified parameters.
 */
class SinGenFilter : public AbstractGeneratorFilter {
public:
    SinGenFilter(double ampl, double freqHz, double durationMs);

    ~SinGenFilter() override = default;

    State apply(Waveform* sound) override;

    double getAmpl() const { return ampl_; }
    double getFreqHz() const { return freq_; }
    double getDurationMs() const { return duration_; }

protected:
    double ampl_;
    double freq_;
    double duration_;
};