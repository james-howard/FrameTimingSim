#pragma once

#include <chrono>
#include <cstdint>

/*! Represents a consumer of frame timings.
 *  Subclassers can calculate statistics or 
 *  simulate a frame selection algorithm.
 */
class FrameSink
{
public:
    /*! Called for each frame read from the log.
     *  \param frameNumber 1 indexed, never goes backwards, typically sequential, 
     *                     but may have gaps due to network drops.
     *  \param captureTime The time at which this frame was captured on the server,
     *                     in the server's clock.
     *  \param decodeTime  The time at which this frame was decoded on the client,
     *                     in the client's clock.
     *  \note The server clock and the client clock have no correspondence.
     *        We can assume they are monotonic clocks and they tick at roughly
     *        the same rate, but there may be some clock skew over time.
     */                                                                    
    virtual void onFrame(uint32_t frameNumber, 
                         std::chrono::microseconds captureTime,
                         std::chrono::microseconds decodeTime) = 0;

    /*! Called when the last frame has been read from the log.
     *  Subclassers can output results in this method.
     */
    virtual void onEndOfStream() = 0;
    
    virtual ~FrameSink() { };
};
