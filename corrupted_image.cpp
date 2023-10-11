#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    Mat image_to_complete = imread("C:/Users/sina tavakoli/source/repos/corrupted_image/images/starwars/image_to_complete.jpg");
    vector<Mat> t_patches;
    string patchDirectory = "C:/Users/sina tavakoli/source/repos/corrupted_image/images/starwars";
    for (int i = 0; i < 4; ++i)
    {
        stringstream ss;
        ss << patchDirectory << "/patch_t_" << i << ".jpg";
        Mat normal_patch = imread(ss.str());
        t_patches.push_back(normal_patch);
    }



    Ptr<Feature2D> sift = SIFT::create();
    vector<KeyPoint> keypoints_image_to_complete;
    Mat image_to_complete_details;
    sift->detectAndCompute(image_to_complete, noArray(), keypoints_image_to_complete, image_to_complete_details);



    vector<vector<KeyPoint>> sum_t_patches_keypoints;
    vector<Mat> t_patches_details;
    for (const auto& patch : t_patches)
    {
        vector<KeyPoint> keypoints_patches;
        Mat descriptors;
        sift->detectAndCompute(patch, noArray(), keypoints_patches, descriptors);
        t_patches_details.push_back(descriptors);
        sum_t_patches_keypoints.push_back(keypoints_patches);
    }



    vector<vector<vector<DMatch>>> allMatches;
    for (const auto& descriptors : t_patches_details)
    {
        BFMatcher matcher(NORM_L2);
        vector<vector<DMatch>> matches;
        matcher.knnMatch(descriptors, image_to_complete_details, matches, 2);
        allMatches.push_back(matches);
    }



    float ratio = 0.7;
    vector<vector<DMatch>> sum_better_matches;
    for (const auto& matches : allMatches)
    {
        vector<DMatch> better_matches;
        for (int i = 0; i < matches.size(); ++i)
        {
            if (matches[i][0].distance < ratio * matches[i][1].distance)
            {
                better_matches.push_back(matches[i][0]);
            }
        }
        sum_better_matches.push_back(better_matches);
    }
    Mat image_with_keypoints;
    drawKeypoints(image_to_complete, keypoints_image_to_complete, image_with_keypoints);
    imshow("image_to_complete_keypoints", image_with_keypoints);
    waitKey(0);



    Mat corrected_image_with_circles = image_to_complete.clone();
    for (size_t i = 0; i < t_patches.size(); ++i)
    {
        vector<Point2f> t_patches_points;
        vector<Point2f> image_to_complete_points;
        for (const auto& match : sum_better_matches[i])
        {
            t_patches_points.push_back(sum_t_patches_keypoints[i][match.queryIdx].pt);
            image_to_complete_points.push_back(keypoints_image_to_complete[match.trainIdx].pt);
        }
        Mat homography = findHomography(t_patches_points, image_to_complete_points, RANSAC);



        Mat warped_patch;
        if (i == 2 || i == 3) {
            warpAffine(t_patches[i], warped_patch, homography.rowRange(0, 2), corrected_image_with_circles.size());
        }
        else {
            warpPerspective(t_patches[i], warped_patch, homography, corrected_image_with_circles.size());
        }
        warped_patch.copyTo(corrected_image_with_circles, warped_patch != 0);



        vector<Point2f> corners;
        corners.push_back(Point2f(0, 0));
        corners.push_back(Point2f(0, t_patches[i].rows));
        corners.push_back(Point2f(t_patches[i].cols, t_patches[i].rows));
        corners.push_back(Point2f(t_patches[i].cols, 0));
        vector<Point2f> transformed_corners;
        perspectiveTransform(corners, transformed_corners, homography);
        Point center;
        float sum_x = 0, sum_y = 0;
        for (const auto& corner : transformed_corners)
        {
            sum_x += corner.x;
            sum_y += corner.y;
        }
        center.x = sum_x / 4;
        center.y = sum_y / 4;
        int radius = static_cast<int>(max(t_patches[i].cols, t_patches[i].rows) * 0.3);
        circle(corrected_image_with_circles, center, radius, Scalar(0, 255, 0), 3);
    }
    imshow("Patches Recognition with Circles", corrected_image_with_circles);
    waitKey(0);



    Mat corrected_image_without_circles = image_to_complete.clone();
    for (size_t i = 0; i < t_patches.size(); ++i)
    {
        vector<Point2f> t_patches_points;
        vector<Point2f> image_to_complete_points;
        for (const auto& match : sum_better_matches[i])
        {
            t_patches_points.push_back(sum_t_patches_keypoints[i][match.queryIdx].pt);
            image_to_complete_points.push_back(keypoints_image_to_complete[match.trainIdx].pt);
        }
        Mat homography = findHomography(t_patches_points, image_to_complete_points, RANSAC);
        Mat warped_patch;
        if (i == 2 || i == 3) {
            warpAffine(t_patches[i], warped_patch, homography.rowRange(0, 2), corrected_image_without_circles.size());
        }
        else {
            warpPerspective(t_patches[i], warped_patch, homography, corrected_image_without_circles.size());
        }
        warped_patch.copyTo(corrected_image_without_circles, warped_patch != 0);
    }
    imshow("Patches Recognition without Circles", corrected_image_without_circles);
    waitKey(0);
    return 0;
}
