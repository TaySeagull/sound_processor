#pragma once

#include "ifilter.h"

/**
 * @brief Filter that multiplies all samples by a constant amplitude
 */
class AmplFilter : public IFilter {
public:
    explicit AmplFilter(double ampl);
    ~AmplFilter() override = default;

    State apply(Waveform* sound) override;

    double getAmpl() const { return ampl_; }

protected:
    double ampl_;
};