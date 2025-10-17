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

**Requirements:**
- CMake ≥ 3.10
- OpenCV ≥ 4.0
- C++ compiler (GCC, Clang, MSVC, or MinGW)

## Install Dependencies

### 🐧 Linux

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install -y cmake build-essential libopencv-dev
```

**Fedora/RHEL/CentOS:**
```bash
sudo dnf install cmake gcc-c++ opencv-devel
```

**Arch Linux:**
```bash
sudo pacman -S cmake gcc opencv
```

### 🍎 macOS

**Homebrew:**
```bash
brew install cmake opencv
```

### 🪟 Windows

1. Install [CMake](https://cmake.org/download/)
2. Download [OpenCV for Windows](https://opencv.org/releases/)
3. Extract and set `OpenCV_DIR` environment variable to `<opencv_path>/build`

# Build Instructions

**Build:**
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

**Clean:**
```bash
rm -rf build
```

# ▶️ Run the Program

**Linux/macOS:**
```bash
./video_processor_cpp
```

**Windows:**
```bash
video_processor_cpp.exe
```

# 🧪 Run Tests

**Linux/macOS:**
```bash
./TestsVideoProcessor
```

**Windows:**
```bash
TestsVideoProcessor.exe
```

# Key Action controls:

Press the following keyboard buttons to do an operation (make sure you are on the video window)
```
f	Toggle flip
i	Toggle invert colors
s	Cycle video scale
q	Quit program
```
