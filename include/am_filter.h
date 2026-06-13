#pragma once

#include "abstract_generator_filter.h"

/**
 * @brief Generates an Amplitude-Modulated (AM) signal
 * @details The volume (amplitude) of the fundamental tone (carrier)
 * changes smoothly according to the law of another, lower tone (modulator)
 * Formulf A * (1 + m * sin(2 * pi * f_m * t)) * sin(2 * pi * f_c * t)
 */
class AmplitudeModulationFilter : public AbstractGeneratorFilter {
public:

    AmplitudeModulationFilter(double amplitude, double carrierFreq, double modFreq, double modIndex, double durationMs);
    ~AmplitudeModulationFilter() override = default;

    State apply(Waveform* sound) override;

private:
    double amplitude_;
    double carrierFreq_;
    double modFreq_;
    double modIndex_;
    double durationMs_;
};