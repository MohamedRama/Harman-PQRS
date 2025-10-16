#include <iostream>
#include <cstdlib>
#include "VideoProcessor.hpp"


int main() {
    try {
        VideoProcessor vp(VideoConstants::DEFAULT_ENCODER_WIDTH, VideoConstants::DEFAULT_ENCODER_HEIGHT);
        vp.initializeCamera(VideoConstants::CAMERA_INDEX);
        vp.initializeWriter(VideoConstants::OUTPUT_FILE);
        vp.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
