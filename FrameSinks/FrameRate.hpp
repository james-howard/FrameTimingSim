#pragma once

#include "FrameSink.hpp"

#include <algorithm>

/* Calculates and outputs average streaming framerate in frames-per-second */
class FrameRate : public FrameSink
{
public:
    void onFrame(uint32_t frameNumber, 
                 std::chrono::microseconds captureTime,
                 std::chrono::microseconds decodeTime) override
    {
        ++m_frameCount;
        m_start = std::min(captureTime, m_start);
        m_end = std::max(captureTime, m_end);
    }
    
    void onEndOfStream() override
    {
        using namespace std::chrono;
    
        if (m_frameCount > 0)
        {
            using DoubleSecondsDuration = duration<double, std::ratio<1, 1>>;
            auto rate = static_cast<double>(m_frameCount) /
                        duration_cast<DoubleSecondsDuration>(m_end - m_start).count();
            printf("Streaming framerate: %.3fFPS\n", rate);
        }
    }

private:
    uint32_t m_frameCount = 0;
    std::chrono::microseconds m_start = std::chrono::microseconds::max();
    std::chrono::microseconds m_end = std::chrono::microseconds::min();
};
