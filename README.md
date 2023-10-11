
# Computer Vision: Keypoints, Descriptors, and Matching

This project is a part of the Computer Vision 2023 course, instructed by Professor P. Zanuttigh, G. Rizzoli, and D. Shenaj. The primary objective of this lab is to explore key points, Descriptors, and Matching techniques with the goal of restoring corrupted regions in images using patch data.

## Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Getting Started](#getting-started)
4. [Methods and Implementation](#methods-and-implementation)
5. [Optional Steps](#optional-steps)
6. [Contributions](#contributions)
7. [License](#license)

## Introduction

The core mission of this project is to develop a C++ software application that can effectively restore corrupted regions within images by leveraging patch data. The primary steps and objectives of the project are as follows:

1. **Loading Data**: Load the corrupted image and the relevant patches from the provided datasets. Different datasets offer varying levels of complexity, so you can choose the one that matches your needs.

2. **Feature Extraction**: Utilize SIFT (Scale-Invariant Feature Transform) to extract distinctive features from both the input image and the patches. Note that SIFT features require OpenCV version 4.4 or higher.

3. **Feature Matching**: Perform feature matching between the image and patches. OpenCV's `cv::BFMatcher` class is the tool of choice for this step. Ensure that you use the L2 distance metric for SIFT features, as Hamming distance is more suitable for ORB features.

4. **Refining Matches**: Refine the initial matches by selecting those with a distance less than a user-defined threshold (referred to as "ratio") multiplied by the minimum distance among the matches.

5. **Transformation Estimation**: Assume an affine transformation links the images and patches. Using the refined matches, employ the RANSAC (Random Sample Consensus) algorithm to find the transformation. The set of inliers can be obtained using the `findHomography()` function with CV_RANSAC as the third parameter.

6. **Region Restoration**: Utilize the estimated homographies to overlay the patches onto the image, thus correcting the corrupted regions.

## Prerequisites

Before using this software, ensure the following prerequisites are met:

- C++ development environment
- OpenCV version 4.4 or higher

## Getting Started

1. **Clone the Repository**: Clone this repository to your local machine using Git. You can do this by running the following command in your terminal:
2. 
3. **Compile the Code**: Ensure you have OpenCV correctly installed in your C++ development environment. Compile the provided C++ code using the appropriate compilation commands.

4. **Run the Application**: Execute the compiled code, providing the path to the corrupted image you want to restore as input.

5. **Review the Restored Image**: After the execution, the application will restore the corrupted regions and display the corrected image.

## Methods and Implementation

In this project, we make extensive use of the Scale-Invariant Feature Transform (SIFT) for feature extraction, matching, and image restoration. The steps involved in the project include:

- Extracting SIFT features from both the input image and patches.
- Calculating and refining matches using the cv::BFMatcher class.
- Estimating the affine transformation using RANSAC.
- Overlaying the patches onto the image to correct corrupted regions.

The provided code in the repository demonstrates a working example of the complete workflow.

## Optional Steps

While the baseline assignment covers the fundamental tasks, you have the opportunity to explore additional features and enhancements:

1. **Simplified RANSAC**: Implement a simplified RANSAC and affine transform estimation, following the trace provided in the course slides.

2. **Custom Datasets**: Collect your own images, remove specific areas, and extract larger patches to allow for matching.

3. **Feature Descriptors**: Experiment with different feature descriptors from OpenCV or other libraries, such as ORB.

4. **Blending Techniques**: Investigate blending and mixing techniques to improve the quality of restored regions.

5. **Multiple Images and Patches**: Use multiple images and all the available patches together, then automatically determine which images are linked to which patches.

6. **Alternative Algorithms**: If you come up with alternative algorithms to tackle the task, feel free to propose and implement them.

7. **Matching Techniques**: Explore other matching techniques, such as template matching or machine learning-based approaches.

8. **Innovative Ideas**: Welcome any innovative ideas and creative solutions that can enhance the project's functionality.

## Contributions

This project encourages contributions from the open-source community. If you have suggestions, enhancements, or bug fixes, please don't hesitate to create pull requests. Collaborative efforts can significantly improve the accuracy and robustness of the restoration process.

## License

This project is licensed under the MIT License. You can find the full license details in the [LICENSE](LICENSE) file within the repository.

Feel free to tailor this README file to your specific project details and include additional information as needed. Remember to create a separate LICENSE file in your repository with the full license text.
