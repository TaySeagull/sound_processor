#pragma once
#include "ifilter.h"

/**
 * @class AbstractGeneratorFilter
 * @brief Abstract base class for generator filters.
 */
class AbstractGeneratorFilter:public IFilter {
public:
    ~AbstractGeneratorFilter() override = default;

protected:
    AbstractGeneratorFilter() = default;
};