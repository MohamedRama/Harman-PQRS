#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdexcept>
#include "VideoProcessor.hpp"
#include "Constants.hpp"
#include "Logger.hpp"


VideoProcessor::VideoProcessor(int encoderWidth, int encoderHeight)
    : encoderWidth_(encoderWidth), encoderHeight_(encoderHeight) {
    setupKeyActions();
}

VideoProcessor::~VideoProcessor() {
    if (writer_.isOpened()) writer_.release();
    if (cap_.isOpened()) cap_.release();
    cv::destroyAllWindows();
    LOG_INFO("Video processor resources released");
}

// Initialize camera and detect encoder resolution
void VideoProcessor::initializeCamera(int camIndex) {
    LOG_INFO("Initializing camera index " + std::to_string(camIndex));
    cap_.open(camIndex);
    if (!cap_.isOpened()) {
        throw std::runtime_error("Cannot open camera at index " + std::to_string(camIndex));
    }

    // Detect camera native resolution
    int camWidth  = static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_WIDTH));
    int camHeight = static_cast<int>(cap_.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Ensure multiples of 2 for H.264
    encoderWidth_  = (camWidth  / 2) * 2;
    encoderHeight_ = (camHeight / 2) * 2;

    // Detect FPS, fallback if unavailable
    double camFPS = cap_.get(cv::CAP_PROP_FPS);
    if (camFPS <= 1.0) {
        LOG_WARN("Camera FPS not reported. Defaulting to 30 FPS.");
        camFPS = VideoConstants::DEFAULT_FPS;
    }
    fps_ = camFPS;

    // Pick the first display resolution >= camera resolution
    displayIndex_ = 0;
    for (size_t i = 0; i < displayRes_.size(); ++i) {
        if (displayRes_[i].width >= camWidth && displayRes_[i].height >= camHeight) {
            displayIndex_ = i;
            break;
        }
    }

    LOG_INFO("Camera successfully initialized: " + std::to_string(camWidth) + "x" + std::to_string(camHeight) + " @ FPS: " + std::to_string(fps_));
}

// Initialize H.264 writer
void VideoProcessor::initializeWriter(const std::string& filename) {
    LOG_INFO("Initializing video writer: " + filename);
    writer_.open(
        filename,
        cv::VideoWriter::fourcc('a','v','c','1'),
        fps_,
        cv::Size(encoderWidth_, encoderHeight_)
    );

    if (!writer_.isOpened()) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }

    LOG_INFO("Writer initialized successfully");
}

// Setup key actions
void VideoProcessor::setupKeyActions() {
    keyActions_[VideoConstants::KEY_QUIT]   = [this]() { 
        shouldExit_ = true; LOG_INFO("Quit key pressed. Exiting..."); 
    };
    keyActions_[VideoConstants::KEY_FLIP]   = [this]() {
        flip_ = !flip_; LOG_INFO("Flip mode: " + std::string(flip_ ? "ON" : "OFF")); 
    };
    keyActions_[VideoConstants::KEY_INVERT] = [this]() {
        invert_ = !invert_; LOG_INFO("Invert mode: " + std::string(invert_ ? "ON" : "OFF"));
    };
    keyActions_[VideoConstants::KEY_SCALE]  = [this]() {
        displayIndex_ = (displayIndex_ + 1) % displayRes_.size();
        const auto& res = displayRes_[displayIndex_];
        LOG_INFO("Switched display resolution to " + std::to_string(res.width) + "x" + std::to_string(res.height));
    };
}

void VideoProcessor::run() {
    LOG_DEBUG("Running VideoProcessor");
    cv::namedWindow(VideoConstants::WINDOW_NAME, cv::WINDOW_AUTOSIZE);
    cv::Mat frame;

    while (!shouldExit_) {
        cap_ >> frame;
        if (frame.empty()) break;

        // --- PROCESSING ---
        cv::Mat processed = frame.clone();
        if (flip_)   cv::flip(processed, processed, -1);
        if (invert_) processed = 255 - processed;

        // --- ENCODING ---
        cv::Mat encoded;
        cv::resize(processed, encoded, cv::Size(encoderWidth_, encoderHeight_));
        writer_.write(encoded);

        // --- DISPLAY ---
        cv::Mat displayFrame;
        cv::resize(processed, displayFrame, displayRes_[displayIndex_]);

        cv::imshow(VideoConstants::WINDOW_NAME, displayFrame);

        // Adaptive wait based on FPS in milliseconds.
        int delay = (fps_ > 0.0) ? static_cast<int>(1000.0 / fps_) : VideoConstants::DEFAULT_FPS;
        int key = cv::waitKey(delay);
        if (key != -1) {
            auto it = keyActions_.find(static_cast<char>(key));
            if (it != keyActions_.end()) {
                it->second();
            }
        }
    }
}
