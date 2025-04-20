#include "image_io.hpp"
#include <iostream>

cv::Mat loadImage(const std::string& filename) {
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Failed to load image: " << filename << "\n";
    }
    return image;
}

bool saveRawImage(const std::string& filename, const cv::Mat& bayerImage) {
    FILE* rawFile = fopen(filename.c_str(), "wb");
    if (!rawFile) {
        std::cerr << "Failed to open output file: " << filename << "\n";
        return false;
    }
    fwrite(bayerImage.data, 1, bayerImage.total(), rawFile);
    fclose(rawFile);
    return true;
}

bool saveGrayscaleImage(const std::string& filename, const cv::Mat& bayerImage) {
    if (!cv::imwrite(filename, bayerImage)) {
        std::cerr << "Failed to save grayscale PNG: " << filename << "\n";
        return false;
    }
    return true;
}