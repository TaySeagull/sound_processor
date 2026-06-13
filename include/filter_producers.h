#pragma once

#include "ifilter.h"
#include "filter_descriptor.h"

/**
 * @brief Namespace containing filter producer functions
 */
namespace FilterProducers {
    
    IFilter* amplFilterCreator(const FilterDescriptor& filter_describtor);

    IFilter* timestretchFilterCreator(const FilterDescriptor& filter_describtor);

    IFilter* silenceFilterCreator(const FilterDescriptor& filter_describtor);

    IFilter* amFilterCreator(const FilterDescriptor& filter_describtor);

    IFilter* fmFilterCreator(const FilterDescriptor& filter_describtor);
    
    IFilter* sinGenFilterCreator(const FilterDescriptor& filter_describtor);
    
}