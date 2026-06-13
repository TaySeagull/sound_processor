#pragma once
#include <map>
#include <string>
#include "pipeline.h"
#include "filter_descriptor.h"

/**
 * @brief Function pointer type for filter producers from the task
 */
using FilterProducer = IFilter* (*)(const FilterDescriptor&);

/**
 * @brief Converts parsed command line arguments into a Pipeline.
 */
class CmdLineArgs2PipelineConverter {
public:
    CmdLineArgs2PipelineConverter() = default;

    Pipeline createPipeline(const std::vector<FilterDescriptor>& descriptors);

    void addFilterProducer(const char* filterName, FilterProducer producer);

    FilterProducer getFilterProducer(const char* filterName) const;

private:
    std::map<std::string, FilterProducer> producers_;
};