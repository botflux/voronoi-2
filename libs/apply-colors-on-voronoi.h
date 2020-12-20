//
// Created by Victor MENDELE on 20/12/2020.
//

#ifndef VORONOI_3_APPLY_COLORS_ON_VORONOI_H
#define VORONOI_3_APPLY_COLORS_ON_VORONOI_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "germ.h"

using namespace std;
using namespace cv;

void applyColorsOnVoronoi (Mat & voronoi, Mat & output, vector<Germ> germs) {
    for (int j = 0; j < voronoi.rows; ++j) {
        for (int i = 0; i < voronoi.cols; ++i) {
            auto id = voronoi.at<ushort>(j, i);

            for(auto & germ : germs) {
                if ((int)id == germ.getId()) {
                    output.at<Vec3b>(j, i) = germ.getColor();
                }
            }
        }
    }
}

#endif //VORONOI_3_APPLY_COLORS_ON_VORONOI_H
