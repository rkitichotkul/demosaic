/**
 * @file main_demosaic.cpp
 * @author Kao Kitichotkul
 * @brief Main application for demosaicing a RAW image.
 * @details This application takes a RAW image (simulated or real) and performs demosaicing
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "demosaic_engine.hpp"
#include "image_io.hpp"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <raw_type: sim|real> <path_to_raw_image> <output_path>" << std::endl;
        return -1;
    }

    std::string rawType = argv[1];
    std::string inputPath = argv[2];
    std::string outputPath = argv[3];

    cv::Mat bayerImage;
    int width = 0, height = 0;
    std::string bayerPattern;

    // Load the RAW image based on the type
    if (rawType == "sim") {
        bayerImage = loadRawImage(inputPath, width, height, bayerPattern);
    } else if (rawType == "real") {
        bayerImage = loadRealRawImage(inputPath, width, height, bayerPattern);
    } else {
        std::cerr << "Invalid raw_type. Use 'sim' or 'real'." << std::endl;
        return -1;
    }

    if (bayerImage.empty()) {
        std::cerr << "Failed to load image: " << inputPath << std::endl;
        return -1;
    }

    // Perform demosaicing using the Bayer pattern
    cv::Mat demosaicedImage = demosaic(bayerImage, bayerPattern);

    if (!demosaicedImage.empty()) {
        // Save the result
        if (!cv::imwrite(outputPath, demosaicedImage)) {
            std::cerr << "Failed to save image to: " << outputPath << std::endl;
            return -1;
        }

        cv::waitKey(0);
    }

    return 0;
}