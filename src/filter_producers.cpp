#include <stdexcept>
#include <string>
#include <cstring>
#include "filter_producers.h"
#include "ampl_filter.h"
#include "timestretch_filter.h"
#include "silence_filter.h"
#include "sin_gen_filter.h"
#include "am_filter.h"
#include "fm_filter.h"

namespace FilterProducers {

/**
 * @brief Creates an AmplFilter from a filter descriptor
 */
IFilter* amplFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "ampl") != 0)
    {
        throw std::logic_error("Wrong descriptor for ampl filter producer");
    }
    
    if (fd.params.size() < 1)
    {
        throw std::logic_error("ampl filter requires 1 parameter: <amplitude>");
    }
    
    try
    {
        double ampl = std::stod(std::string(fd.params[0]));
        return new AmplFilter(ampl);

    } catch (const std::invalid_argument&){

        throw std::logic_error("Invalid amplitude value for ampl filter");

    } catch (const std::out_of_range&) {

        throw std::logic_error("Amplitude value out of range for ampl filter");
    }
}

/**
 * @brief Creates an TimestretchlFilter from a filter descriptor
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
 * @brief Creates an sinGenFilter from a filter descriptor
 */
IFilter* sinGenFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "sin") != 0)
    {
        throw std::logic_error("Wrong descriptor for sin filter producer");
    }
    if (fd.params.size() < 3)
    {
        throw std::logic_error("sin filter requires 3 parameters: <amplitude> <frequency_hz> <duration_ms>");
    }
    try {

        double ampl = std::stod(std::string(fd.params[0]));
        double freqHz = std::stod(std::string(fd.params[1]));
        double durationMs = std::stod(std::string(fd.params[2]));

        return new SinGenFilter(ampl, freqHz, durationMs);

    } catch (const std::invalid_argument&) {

        throw std::logic_error("Invalid parameter value for sin filter");

    } catch (const std::out_of_range&) {

        throw std::logic_error("Parameter value out of range for sin filter");
    }
}

/**
 * @brief Creates an silenceFilter from a filter descriptor
 */
IFilter* silenceFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "silence") != 0)
    {
        throw std::logic_error("Wrong descriptor for silence filter producer");
    }
    if (fd.params.size() < 2)
    {
        throw std::logic_error("silence filter requires 2 parameters: <start_sec> <duration_sec>");
    }
    try {
        double start = std::stod(std::string(fd.params[0]));
        double dur = std::stod(std::string(fd.params[1]));

        return new SilenceFilter(start, dur);

    } catch (...) {

        throw std::logic_error("Invalid parameters for silence filter");
    }
}

/**
 * @brief Creates an AmlFilter from a filter descriptor
 */
IFilter* amFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "am") != 0)
    {
        throw std::logic_error("Wrong descriptor for am filter producer");
    }
    if (fd.params.size() < 5)
    {
        throw std::logic_error("am filter requires 5 parameters: <amplitude> <carrier_freq> <mod_freq> <mod_index> <duration_ms>");
    }
    try {
        double ampl = std::stod(std::string(fd.params[0]));
        double carrier = std::stod(std::string(fd.params[1]));
        double mod = std::stod(std::string(fd.params[2]));
        double index = std::stod(std::string(fd.params[3]));
        double dur = std::stod(std::string(fd.params[4]));

        return new AmplitudeModulationFilter(ampl, carrier, mod, index, dur);

    } catch (...) {

        throw std::logic_error("Invalid parameters for am filter");
    }
}

/**
 * @brief Creates an fmFilter from a filter descriptor.
 */
IFilter* fmFilterCreator(const FilterDescriptor& fd) {
    if (std::strcmp(fd.name, "fm") != 0)
    {
        throw std::logic_error("Wrong descriptor for fm filter producer");
    }
    if (fd.params.size() < 5)
    {
        throw std::logic_error("fm filter requires 5 parameters: <amplitude> <carrier_freq> <mod_freq> <mod_index> <duration_ms>");
    }
    try {
        double ampl = std::stod(std::string(fd.params[0]));
        double carrier = std::stod(std::string(fd.params[1]));
        double mod = std::stod(std::string(fd.params[2]));
        double index = std::stod(std::string(fd.params[3]));
        double dur = std::stod(std::string(fd.params[4]));

        return new FrequencyModulationFilter(ampl, carrier, mod, index, dur);

    } catch (...) {

        throw std::logic_error("Invalid parameters for fm filter");
    }
}

}