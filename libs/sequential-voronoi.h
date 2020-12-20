//
// Created by Victor MENDELE on 18/12/2020.
//

#ifndef VORONOI_3_SEQUENTIAL_VORONOI_H
#define VORONOI_3_SEQUENTIAL_VORONOI_H
#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "germ.h"

using namespace cv;
using namespace std;
using namespace chrono;

vector<tuple<Point, int>> getFrontMask () {
    vector<tuple<Point, int>> points;

    points.emplace_back(Point(-1, -1), 1);
    points.emplace_back(Point(-1, 0), 1);
    points.emplace_back(Point(1, -1), 1);
    points.emplace_back(Point(0, -1), 1);
    points.emplace_back(Point(0, 0), 0);

    return points;
}

vector<tuple<Point, int>> getBackMask () {
    vector<tuple<Point, int>> points;

    points.emplace_back(Point(0, 1), 1);
    points.emplace_back(Point(1, 1), 1);
    points.emplace_back(Point(1, 0), 1);
    points.emplace_back(Point(-1, 1), 1);
    points.emplace_back(Point(0, 0), 0);

    return points;
}

bool isInMat (const Mat & mat, const Point & point) {
    return point.x >= 0 && point.y >= 0 && point.x < mat.rows && point.y < mat.cols;
}

const short FAKE_INFINITY = 256;

short add (short a, short b) {
    if (a == FAKE_INFINITY || b == FAKE_INFINITY) return FAKE_INFINITY;

    return a + b;
}

tuple<unsigned long, unsigned long> sequentialVoronoi (Mat & source, vector<Germ> germs) {
    unsigned long iterationCount = 0;
    auto start = high_resolution_clock::now();

    Mat distances(source.rows, source.cols, CV_16UC1);
    distances = Scalar::all(FAKE_INFINITY);

    for (int i = 0; i < source.cols; ++i) {
        for (int j = 0; j < source.rows; ++j) {
            source.at<ushort>(j, i) = 0;
            iterationCount ++;
        }
    }

    for(auto & germ : germs) {
        distances.at<ushort>(germ.getPoint()) = 0;
        source.at<ushort>(germ.getPoint()) = (ushort)germ.getId();
        iterationCount ++;
    }

    auto frontMask = getFrontMask();

    for (int j = 0; j < distances.rows; ++j) {
        for (int i = 0; i < distances.cols; ++i) {
            short minFound = FAKE_INFINITY;
            Point minFoundPoint = Point(-1, -1);

            for (auto & maskElement : frontMask) {
                auto maskPoint = get<0>(maskElement);
                auto absolutePoint = Point(maskPoint.x + i, maskPoint.y + j);

                if (!isInMat(distances, absolutePoint)) {
                    continue;
                }

                auto distanceInMask = distances.at<ushort> (absolutePoint);
                auto currentWeight = add(distanceInMask, get<1>(maskElement));

                iterationCount ++;

                if (currentWeight <= minFound) {
                    minFound = currentWeight;
                    minFoundPoint = absolutePoint;
                }
            }

            source.at<ushort>(j, i) = source.at<ushort>(minFoundPoint);
            distances.at<ushort>(j, i) = minFound;
        }
    }

    auto backMask = getBackMask();

    for (int j = distances.rows - 1; j >= 0; --j) {
        for (int i = distances.cols - 1; i >= 0; --i) {
            short minFound = FAKE_INFINITY;
            Point minFoundPoint = Point(-1, -1);


            for (auto maskElement : backMask) {
                auto maskPoint = get<0>(maskElement);
                auto absolutePoint = Point(maskPoint.x + i, maskPoint.y + j);

                if (!isInMat(distances, absolutePoint)) continue;

                auto weight = distances.at<ushort> (absolutePoint);
                auto currentWeight = add(weight, get<1>(maskElement));

                ++iterationCount;

                if (currentWeight <= minFound) {
                    minFound = currentWeight;
                    minFoundPoint = absolutePoint;
                }
            }
            source.at<ushort> (j , i) = source.at<ushort> (minFoundPoint);
            distances.at<short> (j, i) = minFound;
        }
    }

    auto end = high_resolution_clock::now();
    return tuple<unsigned long, unsigned long> (iterationCount, duration_cast<seconds>(end - start).count());
}

#endif //VORONOI_3_SEQUENTIAL_VORONOI_H
