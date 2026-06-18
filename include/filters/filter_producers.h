#pragma once
#include "ifilter.h"
#include "filter_descriptor.h"

// TODO: изменить продюссеры

/**
 * @brief Namespace containing filter producer functions
 */
namespace FilterProducers {
    IFilter* amplFilterCreator(const FilterDescriptor& fd);
    
    IFilter* timestretchFilterCreator(const FilterDescriptor& fd);
    
    IFilter* silenceFilterCreator(const FilterDescriptor& fd);
    
    IFilter* generatorFilterCreator(const FilterDescriptor& fd);

    IFilter* normalizeFilterCreator(const FilterDescriptor& fd);
    
    IFilter* lowpassFilterCreator(const FilterDescriptor& fd);
    
}