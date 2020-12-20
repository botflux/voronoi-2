//
// Created by Victor MENDELE on 18/12/2020.
//

#ifndef VORONOI_3_IMAGE_APPROXIMATION_H
#define VORONOI_3_IMAGE_APPROXIMATION_H
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "germ.h"

using namespace std;
using namespace cv;

void brutImageApproximation (Mat & input, Mat & voronoi, Mat & output, vector<Germ> & germs) {
    // Classify point by germ.

    // For each germ
    // We iterate through each point
    // We sum the color
    // We set the mean color to every point of the germ.

    auto comparator = [](const Vec3b & a, const Vec3b & b) -> bool {
        auto aVal = a.val;
        auto bVal = b.val;
        return aVal[0] < bVal[0] && aVal[1] < bVal[1] && aVal[2] < bVal[2];
    };

    map<Vec3b, vector<Point>, decltype(comparator)> pointsByGerm(comparator);

    for (int j = 0; j < voronoi.rows; ++j) {
        for (int i = 0; i < voronoi.cols; ++i) {
            auto color = voronoi.at<Vec3b>(j, i);
            bool hasColor = pointsByGerm.count(color) != 0;

            if (! hasColor) {
                pointsByGerm[color] = vector<Point>();
            }

            pointsByGerm[color].emplace_back(i, j);
        }
    }

    for (auto & germ : germs) {
        auto keyValuePair = pointsByGerm.find(germ.getColor());
        auto points = keyValuePair->second;

        int sum = 0;

        for (auto & point : points) {
            sum += input.at<uchar> (point);
        }

        int meanColor = floor(sum / points.size());

        for(auto & point : points) {
            output.at<uchar>(point) = meanColor;
        }
    }
}

#endif //VORONOI_3_IMAGE_APPROXIMATION_H
