#ifndef BAYER_PATTERN_HPP
#define BAYER_PATTERN_HPP

#include <opencv2/opencv.hpp>
#include <string>

// Function to apply a Bayer pattern to an image
cv::Mat applyBayerPattern(const cv::Mat& image, const std::string& pattern);

// Function to convert a Bayer image to an RGB image
cv::Mat convertBayerToRGB(const cv::Mat& bayerImage, const std::string& bayerPattern);

#endif // BAYER_PATTERN_HPP