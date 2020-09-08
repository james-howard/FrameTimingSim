#include "FrameSinks/FrameRate.hpp"
#include "FrameSinks/NetworkDrops.hpp"

#include <cstdio>
#include <memory>
#include <vector>

/* Reads a CSV of frame timings on stdin, output statistics about it */
int main(int argc, char **argv)
{
    // A vector of sinks which will process the timing data.
    std::vector<std::unique_ptr<FrameSink>> sinks;
    sinks.emplace_back(std::make_unique<FrameRate>());
    sinks.emplace_back(std::make_unique<NetworkDrops>());

    FILE *input = stdin;
    if (argc >= 2 && strcmp(argv[1], "-") != 0)
    {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "Could not open file %s\n", argv[1]);
            exit(1);
        }
    }
    
    // Read input line at a time and process timing data
    char line[256];
    size_t lineNo = 0;
    while (fgets(line, sizeof(line), input) != NULL)
    {
        ++lineNo;
        if (lineNo == 1) continue; // skip header
        
        uint32_t frameNumber = 0;
        double captureTsMs = 0.0;
        double decodeTsMs = 0.0;
        
        sscanf(line, "%u,%lf,%lf", &frameNumber, &captureTsMs, &decodeTsMs);
        
        std::chrono::microseconds capture(static_cast<long long>(captureTsMs * 1000.0));
        std::chrono::microseconds decode(static_cast<long long>(decodeTsMs * 1000.0));
        
        // Process each line of timing data by each sink
        for (auto &sink : sinks)
        {
            sink->onFrame(frameNumber, capture, decode);
        }
    }
    
    // Finish and output stats
    for (auto &sink : sinks)
    {
        sink->onEndOfStream();
    }

    return 0;
}
