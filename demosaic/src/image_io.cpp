#include "image_io.hpp"
#include <iostream>
#include <libraw/libraw.h>

bool saveRawImage(const std::string& filename, const cv::Mat& bayerImage, const std::string& bayerPattern) {
    FILE* rawFile = fopen(filename.c_str(), "wb");
    if (!rawFile) {
        std::cerr << "Failed to open output file: " << filename << "\n";
        return false;
    }

    // Write metadata (image size and Bayer pattern)
    int width = bayerImage.cols;
    int height = bayerImage.rows;
    fprintf(rawFile, "WIDTH %d\n", width);
    fprintf(rawFile, "HEIGHT %d\n", height);
    fprintf(rawFile, "BAYER %s\n", bayerPattern.c_str());

    // Write a separator to distinguish metadata from raw pixel data
    fprintf(rawFile, "DATA\n");

    // Write raw pixel data
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

cv::Mat loadImage(const std::string& filename) {
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Failed to load image: " << filename << "\n";
    }
    return image;
}

cv::Mat loadRawImage(const std::string& filename, int& width, int& height, std::string& bayerPattern) {
    FILE* rawFile = fopen(filename.c_str(), "rb");
    if (!rawFile) {
        std::cerr << "Failed to open raw file: " << filename << "\n";
        return cv::Mat();
    }

    // Read metadata
    if (fscanf(rawFile, "WIDTH %d\n", &width) != 1 ||
        fscanf(rawFile, "HEIGHT %d\n", &height) != 1) {
        std::cerr << "Failed to read image dimensions from raw file.\n";
        fclose(rawFile);
        return cv::Mat();
    }

    char bayerBuffer[16];
    if (fscanf(rawFile, "BAYER %15s\n", bayerBuffer) != 1) {
        std::cerr << "Failed to read Bayer pattern from raw file.\n";
        fclose(rawFile);
        return cv::Mat();
    }
    bayerPattern = std::string(bayerBuffer);

    // Skip the "DATA" line
    char dataLine[16];
    if (!fgets(dataLine, sizeof(dataLine), rawFile) || std::string(dataLine).find("DATA") == std::string::npos) {
        std::cerr << "Failed to find DATA section in raw file.\n";
        fclose(rawFile);
        return cv::Mat();
    }

    // Read raw pixel data
    cv::Mat bayerImage(height, width, CV_8UC1);
    size_t readBytes = fread(bayerImage.data, 1, bayerImage.total(), rawFile);
    if (readBytes != bayerImage.total()) {
        std::cerr << "Failed to read raw pixel data from file.\n";
        fclose(rawFile);
        return cv::Mat();
    }

    fclose(rawFile);
    return bayerImage;
}

cv::Mat loadRealRawImage(const std::string& filename, int& width, int& height, std::string& bayerPattern) {
    LibRaw rawProcessor;

    // Open the RAW file
    if (rawProcessor.open_file(filename.c_str()) != LIBRAW_SUCCESS) {
        std::cerr << "Failed to open RAW file: " << filename << "\n";
        return cv::Mat();
    }

    // Unpack the RAW data
    if (rawProcessor.unpack() != LIBRAW_SUCCESS) {
        std::cerr << "Failed to unpack RAW file: " << filename << "\n";
        return cv::Mat();
    }

    // Get image dimensions
    width = rawProcessor.imgdata.sizes.raw_width;
    height = rawProcessor.imgdata.sizes.raw_height;

    // Determine the Bayer pattern
    auto normalizeColor = [](int color) { return (color == 3) ? 1 : color; };

    int c00 = normalizeColor(rawProcessor.COLOR(0, 0)); // Top-left pixel
    int c01 = normalizeColor(rawProcessor.COLOR(0, 1)); // Top-right pixel
    int c10 = normalizeColor(rawProcessor.COLOR(1, 0)); // Bottom-left pixel
    int c11 = normalizeColor(rawProcessor.COLOR(1, 1)); // Bottom-right pixel

    if (c00 == 0 && c01 == 1 && c10 == 1 && c11 == 2) {
        bayerPattern = "RGGB";
    } else if (c00 == 2 && c01 == 1 && c10 == 1 && c11 == 0) {
        bayerPattern = "BGGR";
    } else if (c00 == 1 && c01 == 0 && c10 == 2 && c11 == 1) {
        bayerPattern = "GRBG";
    } else if (c00 == 1 && c01 == 2 && c10 == 0 && c11 == 1) {
        bayerPattern = "GBRG";
    } else {
        std::cerr << "Unknown Bayer pattern.\n";
        return cv::Mat();
    }

    // Access the raw Bayer data
    ushort* rawData = rawProcessor.imgdata.rawdata.raw_image;
    if (!rawData) {
        std::cerr << "Failed to access raw Bayer data.\n";
        return cv::Mat();
    }

    // Get the maximum value of the raw data
    int maxValue = rawProcessor.imgdata.color.maximum;

    // Create a CV_16UC1 Mat to store the Bayer data
    cv::Mat bayerImage16(height, width, CV_16UC1, rawData);

    // Normalize the 16-bit Bayer data to 8-bit
    cv::Mat bayerImage8;
    bayerImage16.convertTo(bayerImage8, CV_8UC1, 255.0 / maxValue);

    // Recycle the LibRaw processor
    rawProcessor.recycle();

    return bayerImage8;
}

