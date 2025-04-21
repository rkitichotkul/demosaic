#include "image_io.hpp"
#include "bayer_pattern.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <input_png> <output_raw> <bayer_pattern>\n";
        std::cerr << "Bayer patterns: RGGB, BGGR, GRBG, GBRG\n";
        return -1;
    }

    std::string inputFile = argv[1];
    std::string outputRawFile = argv[2];
    std::string bayerPattern = argv[3];

    // Load the input .PNG/.JPG/... image
    cv::Mat image = loadImage(inputFile);
    if (image.empty()) {
        return -1;
    }

    // Apply the Bayer pattern
    cv::Mat bayerImage;
    try {
        bayerImage = applyBayerPattern(image, bayerPattern);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return -1;
    }

    // Save the Bayer image as a RAW file
    if (!saveRawImage(outputRawFile, bayerImage, bayerPattern)) {
        return -1;
    }

    // Save the Bayer image as a grayscale PNG
    std::string outputPngFile = outputRawFile + ".png";
    if (!saveGrayscaleImage(outputPngFile, bayerImage)) {
        return -1;
    }

    // Convert the Bayer image to an RGB image
    cv::Mat rgbImage;
    try {
        rgbImage = convertBayerToRGB(bayerImage, bayerPattern);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return -1;
    }

    // Save the RGB image as a PNG
    std::string outputRgbPngFile = outputRawFile + "_rgb.png";
    if (!cv::imwrite(outputRgbPngFile, rgbImage)) {
        std::cerr << "Failed to save RGB PNG: " << outputRgbPngFile << "\n";
        return -1;
    }

    std::cout << "Bayer image saved to " << outputRawFile << "\n";
    std::cout << "Grayscale PNG saved to " << outputPngFile << "\n";
    std::cout << "RGB PNG saved to " << outputRgbPngFile << "\n";

    return 0;
}