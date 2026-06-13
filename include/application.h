#pragma once
#include "argument_parser.h"
#include "cmd_line_args_2_pipeline_converter.h"

/**
 * @brief Main application class
 */
class Application {
public:
    Application() = default;

    void configure();

    int start(int argc, char* argv[]);

private:
    CmdLineArgs2PipelineConverter converter_;
};