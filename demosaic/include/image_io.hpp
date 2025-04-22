#ifndef IMAGE_IO_HPP
#define IMAGE_IO_HPP

#include <opencv2/opencv.hpp>
#include <string>

// Function to save a RAW Bayer image with metadata
bool saveRawImage(const std::string& filename, const cv::Mat& bayerImage, const std::string& bayerPattern);

// Function to save a grayscale PNG image
bool saveGrayscaleImage(const std::string& filename, const cv::Mat& bayerImage);

// Function to load an image from a file
cv::Mat loadImage(const std::string& filename);

// Function to load a simulated RAW Bayer image with metadata
cv::Mat loadRawImage(const std::string& filename, int& width, int& height, std::string& bayerPattern);

// Function to load a real RAW image using LibRaw
cv::Mat loadRealRawImage(const std::string& filename, int& width, int& height, std::string& bayerPattern);

#endif // IMAGE_IO_HPP