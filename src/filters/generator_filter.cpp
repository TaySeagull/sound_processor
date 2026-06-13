#include <cmath>
#include "filters/generator_filter.h"


constexpr double PI = 3.14159265358979323846;

/**
 * @brief Constructor for a generator filter
 */
GeneratorFilter::GeneratorFilter(const std::string &type,
                                 double amplitude,
                                 double carrier_hz,
                                 double modulation_hz,
                                 double param4,
                                 double duration_ms)
    : type_(type), amplitude_(amplitude), carrier_hz_(carrier_hz),
      modulation_hz_(modulation_hz), param4_(param4), duration_ms_(duration_ms) {}

static int16_t clip(double val)
{
    if (val > 32767.0)
        return 32767;
    if (val < -32768.0)
        return -32768;
    return static_cast<int16_t>(val);
}

/**
 * @brief Applies a Generator
 */
IFilter::State GeneratorFilter::apply(Waveform *sound)
{
    if (!sound)
        return State::error;

    uint32_t sampleRate = sound->getSampleRate();
    size_t numSamples = static_cast<size_t>((duration_ms_ / 1000.0) * sampleRate);

    sound->clear();
    sound->resize(numSamples);

    std::vector<int16_t> &samples = sound->getSamples();

    for (size_t i = 0; i < numSamples; ++i)
    {
        double t = static_cast<double>(i) / sampleRate;
        double val = 0.0;

        if (type_ == "sin")
        {
            // s[i] = clamp(32767 * sin(2 * pi * frequency_hz * t))
            val = 32767.0 * std::sin(2.0 * PI * carrier_hz_ * t);
        }
        else if (type_ == "am")
        {
            // envelope = 1 + depth * sin(2 * pi * modulation_hz * t)
            // carrier = sin(2 * pi * carrier_hz * t)
            // s[i] = clamp(amplitude * 32767 * envelope * carrier)
            double envelope = 1.0 + param4_ * std::sin(2.0 * PI * modulation_hz_ * t);
            double carrier = std::sin(2.0 * PI * carrier_hz_ * t);
            val = amplitude_ * 32767.0 * envelope * carrier;
        }
        else if (type_ == "fm")
        {
            // phase = 2 * pi * carrier_hz * t + (deviation_hz / modulation_hz) * sin(2 * pi * modulation_hz * t)
            // s[i] = clamp(amplitude * 32767 * sin(phase))
            double phase = 2.0 * PI * carrier_hz_ * t + (param4_ / modulation_hz_) * std::sin(2.0 * PI * modulation_hz_ * t);
            val = amplitude_ * 32767.0 * std::sin(phase);
        }

        samples[i] = clip(val);
    }

    return State::ok;
}