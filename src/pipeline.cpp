#include <utility>
#include "pipeline.h"

/**
 * @brief Destructor for pipeline
 */
Pipeline::~Pipeline() {
    for (IFilter* filter : filters_) {
        delete filter;
    }
}

/**
 * @brief Move-constuctor for pipeline
 */
Pipeline::Pipeline(Pipeline&& other) noexcept : filters_(std::move(other.filters_)) {}

/**
 * @brief Move-operator for pipeline
 */
Pipeline& Pipeline::operator=(Pipeline&& other) noexcept {
    if (this != &other) {
        for (IFilter* filter : filters_) {
            delete filter;
        }

        filters_ = std::move(other.filters_);
    }
    return *this;
}

/**
 * @brief Applies all the filters one by one
 */
IFilter::State Pipeline::apply(Waveform* sound) {
    for (IFilter* filter : filters_) {
        IFilter::State state = filter->apply(sound);

        if (state != IFilter::State::ok) {
            return state;
        }
    }
    return IFilter::State::ok;
}

/**
 * @brief Adds new filter
 */
void Pipeline::addFilter(IFilter* filter) {
    filters_.push_back(filter);
}

/**
 * @brief Returns the number of filters
 */
size_t Pipeline::getFilterNumber() const {
    return filters_.size();
}

/**
 * @brief Gets the filter by its number
 */
IFilter* Pipeline::operator[](size_t i) const {
    if (i >= filters_.size()) {
        return nullptr;
    }
    return filters_[i];
}