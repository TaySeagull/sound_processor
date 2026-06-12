#include <catch2/catch_test_macros.hpp>
#include "pipeline.h"
#include "waveform.h"
#include "mock_filter.h"

TEST_CASE("Pipeline adds and counts filters", "[pipeline]") {
    Pipeline pipeline;
    
    REQUIRE(pipeline.getFilterNumber() == 0);
    
    pipeline.addFilter(new MockNoOpFilter());
    REQUIRE(pipeline.getFilterNumber() == 1);
    
    pipeline.addFilter(new MockNoOpFilter());
    REQUIRE(pipeline.getFilterNumber() == 2);
}

TEST_CASE("Pipeline handles an empty pipeline", "[pipeline]") {
    Waveform waveform(44100, 1, 16);
    waveform.resize(10);
    
    Pipeline pipeline;
    IFilter::State state = pipeline.apply(&waveform);
    REQUIRE(state == IFilter::State::ok);
}

TEST_CASE("Pipeline operator[] access", "[pipeline]") {
    Pipeline pipeline;
    pipeline.addFilter(new MockNoOpFilter());
    pipeline.addFilter(new MockNoOpFilter());
    
    REQUIRE(pipeline[0] != nullptr);
    REQUIRE(pipeline[1] != nullptr);
    REQUIRE(pipeline[2] == nullptr);
}

TEST_CASE("Pipeline move semantic", "[pipeline]") {
    Pipeline pipeline1;
    pipeline1.addFilter(new MockCountingFilter());
    REQUIRE(pipeline1.getFilterNumber() == 1);
    
    Pipeline pipeline2 = std::move(pipeline1);
    
    REQUIRE(pipeline2.getFilterNumber() == 1);
    REQUIRE(pipeline1.getFilterNumber() == 0);
    
    Waveform waveform(44100, 1, 16);
    pipeline2.apply(&waveform);
    
    MockCountingFilter* counter = dynamic_cast<MockCountingFilter*>(pipeline2[0]);
    REQUIRE(counter != nullptr);
    REQUIRE(counter->getCallCount() == 1);
}

TEST_CASE("Pipeline virtual destructor works", "[pipeline]") {
    {
        Pipeline pipeline;
        pipeline.addFilter(new MockNoOpFilter());
    }
    SUCCEED("Destructor called correctly");
}

TEST_CASE("Pipeline stops on error", "[pipeline]") {
    Waveform waveform(44100, 1, 16);
    
    Pipeline pipeline;
    pipeline.addFilter(new MockCountingFilter());
    pipeline.addFilter(new MockErrorFilter());
    pipeline.addFilter(new MockCountingFilter());
    
    IFilter::State state = pipeline.apply(&waveform);
    REQUIRE(state == IFilter::State::error);
    
    MockCountingFilter* first = dynamic_cast<MockCountingFilter*>(pipeline[0]);
    MockCountingFilter* third = dynamic_cast<MockCountingFilter*>(pipeline[2]);
    
    REQUIRE(first != nullptr);
    REQUIRE(third != nullptr);
    REQUIRE(first->getCallCount() == 1);
    REQUIRE(third->getCallCount() == 0);
}