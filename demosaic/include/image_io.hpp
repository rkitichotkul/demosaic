#ifndef IMAGE_IO_HPP
#define IMAGE_IO_HPP

#include <opencv2/opencv.hpp>
#include <string>

// Function to load an image from a file
cv::Mat loadImage(const std::string& filename);

// Function to save a RAW Bayer image to a file
bool saveRawImage(const std::string& filename, const cv::Mat& bayerImage);

// Function to save a grayscale PNG image
bool saveGrayscaleImage(const std::string& filename, const cv::Mat& bayerImage);

#endif // IMAGE_IO_HPP