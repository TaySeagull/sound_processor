#pragma once

#include <vector>
#include "ifilter.h"

/**
 * @class Pipeline
 * @brief A class that is a pipeline of filters applied sequentially to a waveform
 */
class Pipeline {
public:
    Pipeline() = default;

    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;


    Pipeline(Pipeline&& other) noexcept;
    Pipeline& operator=(Pipeline&& other) noexcept;


    IFilter::State apply(Waveform* sound);

    void addFilter(IFilter* filter);

    size_t getFilterNumber() const;


    IFilter* operator[](size_t i) const;

private:
    std::vector<IFilter*> filters_;
};