#pragma once
#include <vector>
#include <opencv2/core.hpp>

namespace VideoConstants {
    constexpr int CAMERA_INDEX = 0;
    constexpr double DEFAULT_FPS = 30.0;
    constexpr char WINDOW_NAME[] = "Video Display";

    // Encoder settings
    constexpr int DEFAULT_ENCODER_WIDTH  = 640;
    constexpr int DEFAULT_ENCODER_HEIGHT = 480;

    // Key mappings
    constexpr char KEY_QUIT   = 'q';
    constexpr char KEY_FLIP   = 'f';
    constexpr char KEY_INVERT = 'i';
    constexpr char KEY_SCALE  = 's';

    // Display resolutions (for window scaling)
    inline const std::vector<cv::Size> DISPLAY_RES = {
        cv::Size(320, 240),
        cv::Size(640, 480),
        cv::Size(1280, 720),
        cv::Size(1920, 1080)
    };

    constexpr char OUTPUT_FILE[] = "processed_video.mp4";
}
