#pragma once
#include "waveform.h"

/**
 * @class IFilter
 * @brief Abstract base interface for all audio filters
 */
class IFilter {
public:
    enum class State {
        ok,
        error
    };

    virtual ~IFilter() = default;

    virtual State apply(Waveform* sound) = 0;
};