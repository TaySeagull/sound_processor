#include <stdexcept>
#include <string>
#include "cmd_line_args_2_pipeline_converter.h"

/**
 * @brief Creates a pipeline from filter descriptors
 */
Pipeline CmdLineArgs2PipelineConverter::createPipeline(
    const std::vector<FilterDescriptor>& descriptors) {
    
    Pipeline pipeline;
    
    for (const FilterDescriptor& descriptor : descriptors) {
        FilterProducer producer = getFilterProducer(descriptor.name);
        
        if (!producer) {
            throw std::runtime_error(
                std::string("Unknown filter: ") + descriptor.name);
        }
        
        IFilter* filter = producer(descriptor);
        
        if (!filter) {
            throw std::runtime_error(
                std::string("Failed to create filter: ") + descriptor.name);
        }
        
        pipeline.addFilter(filter);
    }
    
    return pipeline;
}

/**
 * @brief Registers a filter producer for a given filter name
 */
void CmdLineArgs2PipelineConverter::addFilterProducer(
    const char* filterName, FilterProducer producer) {
    producers_[std::string(filterName)] = producer;
}

/**
 * @brief Retrieves a filter producer by name
 */
FilterProducer CmdLineArgs2PipelineConverter::getFilterProducer(
    const char* filterName) const {
    
    auto it = producers_.find(std::string(filterName));
    if (it == producers_.end()) {
        return nullptr;
    }
    
    return it->second;
}