#pragma once

#include "FrameSink.hpp"

#include <cassert>
#include <cstdio>

/* Calculates number of frames dropped by the network */
class NetworkDrops : public FrameSink
{
public:
    void onFrame(uint32_t frameNumber, 
                 std::chrono::microseconds captureTime,
                 std::chrono::microseconds decodeTime) override
    {
        assert(frameNumber > m_prev);
        m_dropped += (frameNumber - m_prev) - 1;
        m_prev = frameNumber;
    }
    
    void onEndOfStream() override
    {
        printf("Network Drops: %u\n", m_dropped);
    }

private:
    uint32_t m_dropped = 0;
    uint32_t m_prev = 0;
};
