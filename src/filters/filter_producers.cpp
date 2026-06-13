#include <stdexcept>
#include <string>
#include <cstring>
#include "filters/filter_producers.h"
#include "filters/ampl_filter.h"
#include "filters/timestretch_filter.h"
#include "filters/silence_filter.h"
#include "filters/generator_filter.h"
#include "filters/normalize_filter.h"
#include "filters/lowpass_filter.h"


namespace FilterProducers {

/**
 * @brief Creates an AmplFilter from descriptor
 */
IFilter* amplFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "ampl") != 0)
    {
        throw std::logic_error("Wrong descriptor for ampl filter producer");
    }
    
    if (fd.params.size() < 1)
    {
        throw std::logic_error("ampl filter requires 1 parameter: <factor>");
    }
    
    try {

        double factor = std::stod(std::string(fd.params[0]));
        return new AmplFilter(factor);

    } catch (const std::invalid_argument&) {

        throw std::logic_error("Invalid factor value for ampl filter");

    } catch (const std::out_of_range&) {

        throw std::logic_error("Factor value out of range for ampl filter");
    }
}

/**
 * @brief Creates a TimestretchFilter from descriptor
*/
IFilter* timestretchFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "timestretch") != 0)
    {
        throw std::logic_error("Wrong descriptor for timestretch filter producer");
    }
    
    if (fd.params.size() < 1)
    {
        throw std::logic_error("timestretch filter requires 1 parameter: <factor>");
    }
    try {

        double factor = std::stod(std::string(fd.params[0]));
        return new TimestretchFilter(factor);

    } catch (const std::invalid_argument&) {

        throw std::logic_error("Invalid factor value for timestretch filter");

    } catch (const std::out_of_range&) {

        throw std::logic_error("Factor value out of range for timestretch filter");
    }
}

/**
 * @brief Creates a SilenceFilter from descriptor
 */
IFilter* silenceFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "silence") != 0)
    {
        throw std::logic_error("Wrong descriptor for silence filter producer");
    }
    if (fd.params.size() < 3)
    {
        throw std::logic_error("silence filter requires 3 parameters: <unit> <start> <end>");
    }
    try {

        std::string unit = std::string(fd.params[0]);
        double start = std::stod(std::string(fd.params[1]));
        double end = std::stod(std::string(fd.params[2]));

        return new SilenceFilter(unit, start, end);

    } catch (...) {

        throw std::logic_error("Invalid parameters for silence filter");
    }
}

/**
 * @brief Creates a GeneratorFilter (unified sin/am/fm) from descriptor
 */
IFilter* generatorFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "generator") != 0)
    {
        throw std::logic_error("Wrong descriptor for generator filter producer");
    }
    if (fd.params.size() < 1)
    {
        throw std::logic_error("generator requires subtype: sin, am, or fm");
    }
    
    std::string subtype = std::string(fd.params[0]);
    
    if (subtype == "sin") {
        if (fd.params.size() < 3)
        {
            throw std::logic_error("generator sin requires: <frequency_hz> <duration_ms>");
        }

        double freq = std::stod(std::string(fd.params[1]));
        double dur = std::stod(std::string(fd.params[2]));

        return new GeneratorFilter("sin", 1.0, freq, 0.0, 0.0, dur);
    }
    else if (subtype == "am") {
        if (fd.params.size() < 6)
        {
            throw std::logic_error("generator am requires: <amplitude> <carrier_hz> <modulation_hz> <depth> <duration_ms>");
        }

        double ampl = std::stod(std::string(fd.params[1]));
        double carrier = std::stod(std::string(fd.params[2]));
        double mod = std::stod(std::string(fd.params[3]));
        double depth = std::stod(std::string(fd.params[4]));
        double dur = std::stod(std::string(fd.params[5]));

        return new GeneratorFilter("am", ampl, carrier, mod, depth, dur);
    }
    else if (subtype == "fm") {
        if (fd.params.size() < 6)
        {
            throw std::logic_error("generator fm requires: <amplitude> <carrier_hz> <modulation_hz> <deviation_hz> <duration_ms>");
        }

        double ampl = std::stod(std::string(fd.params[1]));
        double carrier = std::stod(std::string(fd.params[2]));
        double mod = std::stod(std::string(fd.params[3]));
        double deviation = std::stod(std::string(fd.params[4]));
        double dur = std::stod(std::string(fd.params[5]));

        return new GeneratorFilter("fm", ampl, carrier, mod, deviation, dur);
    }
    
    throw std::logic_error("Unknown generator subtype: " + subtype);
}

/**
 * @brief Creates a NormalizeFilter from descriptor
 */
IFilter* normalizeFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "normalize") != 0)
    {
        throw std::logic_error("Wrong descriptor for normalize filter producer");
    }
    
    double peak = 1.0;

    if (fd.params.size() >= 1)
    {
        try {

            peak = std::stod(std::string(fd.params[0]));

        } catch (...) {

            throw std::logic_error("Invalid peak value for normalize filter");
        }
    }
    
    return new NormalizeFilter(peak);
}

/**
 * @brief Creates a LowpassFilter from descriptor
 */
IFilter* lowpassFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "lowpass") != 0)
    {
        throw std::logic_error("Wrong descriptor for lowpass filter producer");
    }
    
    if (fd.params.size() < 1)
    {
        throw std::logic_error("lowpass filter requires 1 parameter: <window_size>");
    }
    
    try {

        int window_size = std::stoi(std::string(fd.params[0]));

        if (window_size < 1 || window_size % 2 == 0)
        {
            throw std::logic_error("window_size must be an odd number >= 1");
        }

        return new LowpassFilter(window_size);

    } catch (const std::logic_error&) {
        throw;

    } catch (...) {

        throw std::logic_error("Invalid window_size value for lowpass filter");
    }
}

}