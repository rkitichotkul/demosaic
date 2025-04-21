#include "image_io.hpp"
#include "bayer_pattern.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <mode> <raw_file> [save_name]\n";
        std::cerr << "Modes:\n";
        std::cerr << "  custom - Load a custom RAW file with metadata (e.g., .raw)\n";
        std::cerr << "  real   - Load a real RAW image (e.g., .NEF, .RAF)\n";
        std::cerr << "Optional:\n";
        std::cerr << "  save_name - Base name to save grayscale and RGB images\n";
        return -1;
    }

    std::string mode = argv[1];
    std::string rawFile = argv[2];
    std::string saveName = (argc > 3) ? argv[3] : "";

    int width, height;
    std::string bayerPattern;
    cv::Mat bayerImage;

    if (mode == "custom") {
        // Load the custom RAW image
        bayerImage = loadRawImage(rawFile, width, height, bayerPattern);
        if (bayerImage.empty()) {
            std::cerr << "Failed to load custom RAW image.\n";
            return -1;
        }
    } else if (mode == "real") {
        // Load the real RAW image
        bayerImage = loadRealRawImage(rawFile, width, height, bayerPattern);
        if (bayerImage.empty()) {
            std::cerr << "Failed to load real RAW image.\n";
            return -1;
        }
    } else {
        std::cerr << "Invalid mode: " << mode << "\n";
        std::cerr << "Valid modes are 'custom' or 'real'.\n";
        return -1;
    }

    std::cout << "Loaded raw image with dimensions: " << width << " x " << height << "\n";
    std::cout << "Bayer pattern: " << bayerPattern << "\n";

    // Display the Bayer image (optional)
    cv::imshow("Bayer Image", bayerImage);
    cv::waitKey(0);

    // Save grayscale and RGB images if save name is provided
    if (!saveName.empty()) {
        // Save grayscale image
        std::string grayscaleFile = saveName + "_grayscale.png";
        if (!saveGrayscaleImage(grayscaleFile, bayerImage)) {
            std::cerr << "Failed to save grayscale image: " << grayscaleFile << "\n";
        } else {
            std::cout << "Grayscale image saved to: " << grayscaleFile << "\n";
        }

        // Convert Bayer to RGB and save
        cv::Mat rgbImage = convertBayerToRGB(bayerImage, bayerPattern);
        std::string rgbFile = saveName + "_rgb.png";
        if (!cv::imwrite(rgbFile, rgbImage)) {
            std::cerr << "Failed to save RGB image: " << rgbFile << "\n";
        } else {
            std::cout << "RGB image saved to: " << rgbFile << "\n";
        }

    }

    return 0;
}