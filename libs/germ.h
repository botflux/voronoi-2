//
// Created by Victor MENDELE on 18/12/2020.
//

#ifndef VORONOI_3_GERM_H
#define VORONOI_3_GERM_H
#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Germ {
private:
    Vec3b color;
    Point point;
    int id;

public:
    Germ(Vec3b color, Point point): color(color), point (point), id(0) {}
    Germ(Vec3b color, Point point, int id): color(color), point(point), id(id) {}
    Vec3b getColor () {
        return color;
    }
    Point getPoint () {
        return point;
    }
    int getId () {
        return id;
    }
    bool isInMat (const Mat & mat) {
        return point.x >= 0 && point.y >= 0 && point.x < mat.cols && point.y < mat.rows;
    }
};

class GermFactory {
private:
    int lastGermId;

public:
    GermFactory(): lastGermId (0) {}
    vector<Germ> createRandomGerm (Mat & mat, int germCount) {
        vector<Germ> germs;

        for (int i = 0; i < germCount; ++i) {
            auto randomX = random() % (mat.cols - 1);
            auto randomY = random() % (mat.rows - 2);
            auto randomColor = Vec3b(random() % 255, random() % 255, random() % 255);

            germs.emplace_back(randomColor, Point(randomX, randomY), lastGermId);
            ++ lastGermId;
        }

        return germs;
    }
};

#endif //VORONOI_3_GERM_H
