//
// Created by Victor MENDELE on 18/12/2020.
//

#ifndef VORONOI_3_BRUT_VORONOI_H
#define VORONOI_3_BRUT_VORONOI_H
#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <cmath>
#include "germ.h"

using namespace std;
using namespace cv;
using namespace chrono;

class DistanceCalculator {
public:
    virtual double getDistance (const Point & a, const Point & b) = 0;
};

class DeDistanceCalculator : public DistanceCalculator {
public:
    double getDistance (const Point & a, const Point & b) override {
        double distanceX = a.x - b.x;
        double distanceY = a.y - b.y;
        double distanceSquared = pow(distanceX, 2) + pow(distanceY, 2);

        return sqrt(distanceSquared);
    }
};

class DiDistanceCalculator : public DistanceCalculator {
public:
    double getDistance (const Point & a, const Point & b) override {

        double distanceX = abs(a.x - b.x);
        double distanceY = abs(a.y - b.y);

        return distanceX > distanceY
               ? distanceX
               : distanceY;
    }
};

tuple<unsigned long, unsigned long> brutVoronoi (Mat & source, vector<Germ> germs, DistanceCalculator & distanceCalculator) {
    unsigned long iterationCount = 0;
    auto start = high_resolution_clock::now();

    for (int j = 0; j < source.rows; ++j) {
        for (int i = 0; i < source.cols; ++i) {
            Point currentPoint (i, j);
            double lowestDistance = numeric_limits<double>::max();
            Germ foundGerm(Vec3b(0,0,0), Point(-1, -1));

            for (auto & germ : germs) {
                auto currentDistance = distanceCalculator.getDistance(germ.getPoint(), currentPoint);
                ++ iterationCount;

                if (currentDistance <= lowestDistance) {
                    lowestDistance = currentDistance;
                    foundGerm = germ;
                }
            }

            source.at<ushort>(currentPoint) = (ushort) foundGerm.getId();
        }
    }

    auto end = high_resolution_clock::now();
    auto deltaTime = duration_cast<seconds>(end - start);

    return tuple<unsigned long, unsigned long>(iterationCount, deltaTime.count());
}

#endif //VORONOI_3_BRUT_VORONOI_H
