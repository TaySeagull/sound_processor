#pragma once
#include "abstract_generator_filter.h"
#include <string>

/**
 * @brief Unified generator filter supporting three waveform types.
 * @details This filter generates audio based on the specified type: sin, am, fm
 */
class GeneratorFilter : public AbstractGeneratorFilter {
public:
    GeneratorFilter(const std::string& type,
                    double amplitude,
                    double carrier_hz,
                    double modulation_hz,
                    double param4,
                    double duration_ms);
    ~GeneratorFilter() override = default;

    State apply(Waveform* sound) override;

private:
    std::string type_;
    double amplitude_;
    double carrier_hz_;
    double modulation_hz_;
    double param4_;
    double duration_ms_;
};