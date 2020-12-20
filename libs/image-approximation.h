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

void brutImageApproximation (Mat & input, Mat & voronoi, Mat & output, vector<Germ> & germs, map<int, vector<Point>> & regions) {
    // Classify point by germ.

    // For each pixel
    // We search the associated germ
    // We update the sum map
    // We apply all the means

    for (auto & region : regions) {
        int sum = 0;

        for (auto & point : region.second) {
            sum += input.at<uchar> (point);
        }

        int mean = sum / region.second.size();

        for (auto & point : region.second) {
            output.at<uchar> (point) = (uchar) mean;
        }
    }

}

#endif //VORONOI_3_IMAGE_APPROXIMATION_H
