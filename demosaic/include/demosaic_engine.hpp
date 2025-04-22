#ifndef DEMOSAIC_ENGINE_HPP
#define DEMOSAIC_ENGINE_HPP

#include <opencv2/opencv.hpp>
#include <string>

// Function to perform demosaicing
cv::Mat demosaic(const cv::Mat& bayerImage, const std::string& bayerPattern);

#endif // DEMOSAIC_ENGINE_HPP