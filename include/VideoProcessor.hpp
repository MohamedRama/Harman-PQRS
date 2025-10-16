#pragma once
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include "Constants.hpp"

class VideoProcessor {
public:
    VideoProcessor(int encoderWidth = VideoConstants::DEFAULT_ENCODER_WIDTH, int encoderHeight = VideoConstants::DEFAULT_ENCODER_HEIGHT);
    ~VideoProcessor();

    void initializeCamera(int camIndex);
    void initializeWriter(const std::string& filename);
    void run();

    void setFlip(bool val) { flip_ = val; }
    void setInvert(bool val) { invert_ = val; }
    void resetDisplayIndex(size_t index = 0) { displayIndex_ = index; }
    void triggerKey(char key) {
        if (keyActions_.count(key)) keyActions_[key]();
    }

private:
    int encoderWidth_;
    int encoderHeight_;
    double fps_ = VideoConstants::DEFAULT_FPS;
    bool flip_ = false;
    bool invert_ = false;
    size_t displayIndex_ = 0;
    bool shouldExit_ = false;

    cv::VideoCapture cap_;
    cv::VideoWriter writer_;
    const std::vector<cv::Size>& displayRes_ = VideoConstants::DISPLAY_RES;

    std::unordered_map<char, std::function<void()>> keyActions_;

    void setupKeyActions();
};
