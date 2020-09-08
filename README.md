# FrameTimingSim

Reads a video frame timing log, simulates frame selection algorithms, and outputs statistics.

# Building

Command line:

```
cmake -S . -B build 
cmake --build build
```

IDE:

```
cmake -G Xcode .
open FrameTimingSim.xcodeproj
```

# Running

`./build/FrameTimingSim < data/frame_timing.csv`

OR

`./build/FrameTimingSim data/frame_timing.csv`

## CSV Format

```
frame_number,capture_ts_ms,decode_ts_ms
1,1434428.867,6382.766
2,1434462.396,6386.526
3,1434479.591,6388.660
4,1434495.775,6391.698
...
```
