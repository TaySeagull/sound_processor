#pragma once

#include "ifilter.h"

/**
 * @class SilenceFilter
 * @brief A class for adding silence
 */
class SilenceFilter : public IFilter {
public:
    explicit SilenceFilter(double startSec, double durationSec);
    ~SilenceFilter() override = default;

    State apply(Waveform* sound) override;

    double getStartSec() const { return startSec_; }
    double getDurationSec() const { return durationSec_; }

protected:
    double startSec_;
    double durationSec_;
};