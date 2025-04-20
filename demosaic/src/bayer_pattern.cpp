#include "bayer_pattern.hpp"
#include <stdexcept>

cv::Mat applyBayerPattern(const cv::Mat& image, const std::string& pattern) {
    CV_Assert(image.channels() == 3); // Ensure the input image is in RGB format

    cv::Mat bayer(image.rows, image.cols, CV_8UC1);

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            const cv::Vec3b& pixel = image.at<cv::Vec3b>(y, x);

            if (pattern == "RGGB") {
                if (y % 2 == 0) {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[2] : pixel[1]; // R or G
                } else {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[1] : pixel[0]; // G or B
                }
            } else if (pattern == "BGGR") {
                if (y % 2 == 0) {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[0] : pixel[1]; // B or G
                } else {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[1] : pixel[2]; // G or R
                }
            } else if (pattern == "GRBG") {
                if (y % 2 == 0) {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[1] : pixel[2]; // G or R
                } else {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[0] : pixel[1]; // B or G
                }
            } else if (pattern == "GBRG") {
                if (y % 2 == 0) {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[1] : pixel[0]; // G or B
                } else {
                    bayer.at<uchar>(y, x) = (x % 2 == 0) ? pixel[2] : pixel[1]; // R or G
                }
            } else {
                throw std::invalid_argument("Unsupported Bayer pattern: " + pattern);
            }
        }
    }

    return bayer;
}

cv::Mat convertBayerToRGB(const cv::Mat& bayerImage, const std::string& bayerPattern) {
    cv::Mat rgbImage(bayerImage.rows, bayerImage.cols, CV_8UC3, cv::Scalar(0, 0, 0));

    for (int y = 0; y < bayerImage.rows; ++y) {
        for (int x = 0; x < bayerImage.cols; ++x) {
            uchar value = bayerImage.at<uchar>(y, x);

            if (bayerPattern == "RGGB") {
                if (y % 2 == 0) {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[2] = value; // Red
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    }
                } else {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[0] = value; // Blue
                    }
                }
            } else if (bayerPattern == "BGGR") {
                if (y % 2 == 0) {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[0] = value; // Blue
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    }
                } else {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[2] = value; // Red
                    }
                }
            } else if (bayerPattern == "GRBG") {
                if (y % 2 == 0) {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[2] = value; // Red
                    }
                } else {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[0] = value; // Blue
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    }
                }
            } else if (bayerPattern == "GBRG") {
                if (y % 2 == 0) {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[0] = value; // Blue
                    }
                } else {
                    if (x % 2 == 0) {
                        rgbImage.at<cv::Vec3b>(y, x)[2] = value; // Red
                    } else {
                        rgbImage.at<cv::Vec3b>(y, x)[1] = value; // Green
                    }
                }
            } else {
                throw std::invalid_argument("Unsupported Bayer pattern: " + bayerPattern);
            }
        }
    }

    return rgbImage;
}