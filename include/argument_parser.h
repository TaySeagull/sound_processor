#pragma once
#include <vector>
#include "filters/filter_descriptor.h"

/**
 * @class ArgsParser
 * @brief A class for parsing CLA
 */
class ArgsParser {
public:
    enum class Result {
        ok,
        noArgs,
        badArgs
    };

    ArgsParser() = default;

    Result parse(int argc, char* argv[]);
    void printHelp() const;

    const char* getInputFileName() const { return inputFileName_; }
    const char* getOutputFileName() const { return outputFileName_; }
    const std::vector<FilterDescriptor>& getFilterDescriptors() const { return filterDescriptors_; }

    bool hasInputFile() const { return inputFileName_ != nullptr; }
    bool hasOutputFile() const { return outputFileName_ != nullptr; }
    bool hasFilters() const { return !filterDescriptors_.empty(); }

private:
    const char* inputFileName_ = nullptr;
    const char* outputFileName_ = nullptr;
    std::vector<FilterDescriptor> filterDescriptors_;

    bool isFlag(const char* arg) const;
};