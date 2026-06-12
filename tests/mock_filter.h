#pragma once

#include "ifilter.h"
#include "waveform.h"

/**
 * @brief Mock filter that does nothing :)
 */
class MockNoOpFilter : public IFilter {
public:
    ~MockNoOpFilter() override = default;

    State apply(Waveform* sound) override {
        return State::ok;
    }
};

/**
 * @brief Mock filter that always returns error
 */
class MockErrorFilter : public IFilter {
public:
    ~MockErrorFilter() override = default;

    State apply(Waveform* sound) override {
        return State::error;
    }
};

/**
 * @brief Mock filter that counts how many times apply() was called
 */
class MockCountingFilter : public IFilter {
public:
    MockCountingFilter() : callCount_(0) {}
    ~MockCountingFilter() override = default;

    State apply(Waveform* sound) override {
        callCount_++;
        return State::ok;
    }

    int getCallCount() const { return callCount_; }

private:
    int callCount_;
};