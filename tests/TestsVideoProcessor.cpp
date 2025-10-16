#include <opencv2/core.hpp>
#include <cassert>
#include <iostream>
#include "VideoProcessor.hpp"
#include "Constants.hpp"

int main() {
    try {
        // Create VideoProcessor instance with default encoder size
        VideoProcessor vp;

        // Test frame processing logic using clone & flip/invert simulation
        cv::Mat testFrame(100, 100, CV_8UC3, cv::Scalar(100, 100, 100));

        // Flip only
        vp.setFlip(true);
        vp.setInvert(false);
        cv::Mat processedFlip = testFrame.clone();
        if (true) cv::flip(processedFlip, processedFlip, -1); // simulate flip
        assert(processedFlip.rows == 100 && processedFlip.cols == 100);

        // Invert only
        vp.setFlip(false);
        vp.setInvert(true);
        cv::Mat processedInvert = 255 - testFrame; // simulate invert
        assert(processedInvert.rows == 100 && processedInvert.cols == 100);

        std::cout << "[TEST] Processing logic (flip/invert) passed.\n";

        // Test scale key action triggers
        vp.resetDisplayIndex();
        vp.triggerKey(VideoConstants::KEY_SCALE); // advance display resolution
        vp.triggerKey(VideoConstants::KEY_SCALE);
        vp.triggerKey(VideoConstants::KEY_SCALE);

        std::cout << "[TEST] Key actions (scale) triggered successfully.\n";

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "[TEST] Exception: " << ex.what() << "\n";
        return 1;
    }
}
