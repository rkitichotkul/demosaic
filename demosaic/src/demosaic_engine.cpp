#include "demosaic_engine.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

// Function to perform demosaicing
cv::Mat demosaic(const cv::Mat& bayerImage, const std::string& bayerPattern) {
    if (bayerImage.empty()) {
        std::cerr << "Input image is empty!" << std::endl;
        return cv::Mat();
    }

    cv::Mat demosaicedImage;

    // Use the Bayer pattern to perform demosaicing
    if (bayerPattern == "RGGB") {
        cv::cvtColor(bayerImage, demosaicedImage, cv::COLOR_BayerBG2BGR);
    } else if (bayerPattern == "BGGR") {
        cv::cvtColor(bayerImage, demosaicedImage, cv::COLOR_BayerRG2BGR);
    } else if (bayerPattern == "GRBG") {
        cv::cvtColor(bayerImage, demosaicedImage, cv::COLOR_BayerGB2BGR);
    } else if (bayerPattern == "GBRG") {
        cv::cvtColor(bayerImage, demosaicedImage, cv::COLOR_BayerGR2BGR);
    } else {
        // Default to RGGB if the pattern is unknown
        cv::cvtColor(bayerImage, demosaicedImage, cv::COLOR_BayerBG2BGR);
    }

    return demosaicedImage;
}