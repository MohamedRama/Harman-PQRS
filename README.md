# Harman-PQRS

Video Processor

A real-time, cross-platform video processor written in C++ using OpenCV.
It captures video from your webcam, applies live transformations, and outputs the processed stream in H.264 format.

# Features
```
- Capture video from webcam (default system camera)

- Real-time video display and processing

- Invert colors toggle

- Scale between 320x240, 640x480, 1280x720, 1920x1080

- Processed output as H.264 encoded video
```

#Structure
```
Harman_PQRS/
.
├── CMakeLists.txt
├── Constants.hpp
├── Logger.hpp
├── Makefile
├── README.md
├── include
│   └── VideoProcessor.hpp
├── src
│   ├── VideoProcessor.cpp
│   └── main.cpp
└── tests
    └── TestsVideoProcessor.cpp
```

# Build Requirements
🐧 Linux / macOS
```
CMake ≥ 3.10

OpenCV ≥ 4.0

C++ compiler

Install dependencies:

Ubuntu/Debian:

sudo apt update
sudo apt install -y cmake build-essential libopencv-dev

macOS (Homebrew):

brew install cmake opencv

```

🪟 Windows
```
CMake

OpenCV for Windows

In Git Bash / MSYS2 you can use make directly.
If using MinGW, run mingw32-make instead.
```

# Build Instructions

Build (automatic with Makefile)

`make`

The compiled binary will appear in:

`build/video_processor_cpp`

Remove the build directory and binaries:

`make clean`

Rebuild (Clean + Build)

`make rebuild`

# ▶️ Run the Program

`./build/video_processor_cpp`


# Key Action controls:

Press the following keyboard buttons to do an operation (make sure you are on the video window)
```
f	Toggle flip
i	Toggle invert colors
s	Cycle video scale
q	Quit program
```
