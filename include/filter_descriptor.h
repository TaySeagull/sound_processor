#pragma once

#include <vector>

/**
 * @struct FilterDescriptor
 * @brief Describes a filter with its name and parameters
 */
struct FilterDescriptor {
    const char* name;
    std::vector<const char*> params;
};