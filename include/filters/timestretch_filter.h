#pragma once
#include "ifilter.h"

/**
 * @class TimestretchFilter
 * @brief Filter that changes the speed of the audio
 */
class TimestretchFilter : public IFilter {
public:
    explicit TimestretchFilter(double factor);
    ~TimestretchFilter() override = default;

    State apply(Waveform* sound) override;

    double getFactor() const { return factor_; }

protected:
    double factor_;
};