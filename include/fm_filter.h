#pragma once

#include "abstract_generator_filter.h"

/**
 * @brief Generates a Frequency-Modulated (FM) signal
 * @details The pitch (frequency) of the main signal smoothly
 * "floats" up and down according to the law of the other tone
 * 
 * Formula A * sin(2 * pi * f_c * t + I * sin(2 * pi * f_m * t))
 */
class FrequencyModulationFilter : public AbstractGeneratorFilter {
public:
    FrequencyModulationFilter(double amplitude, double carrierFreq, double modFreq, double modIndex, double durationMs);
    ~FrequencyModulationFilter() override = default;

    State apply(Waveform* sound) override;

private:
    double amplitude_;
    double carrierFreq_;
    double modFreq_;
    double modIndex_;
    double durationMs_;
};