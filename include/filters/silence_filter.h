#pragma once
#include <string>
#include "ifilter.h"

/**
 * @brief Filter that inserts a segment of silence (zero samples) into the audio
 */
class SilenceFilter : public IFilter {
public:
    explicit SilenceFilter(const std::string& unit_, double start_, double end_);

    ~SilenceFilter() override = default;

    State apply(Waveform* sound) override;

private:
    std::string unit_;
    double start_;
    double end_;
};