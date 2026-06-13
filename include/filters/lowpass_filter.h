#pragma once
#include "ifilter.h"

/**
 * @brief Filter that smooths the audio signal using a moving average 
 */
class LowpassFilter : public IFilter {
public:
    explicit LowpassFilter(int window_size);
    ~LowpassFilter() override = default;

    State apply(Waveform* sound) override;

    int getWindowSize() const { return _window_size; }

private:
    int _window_size;
};