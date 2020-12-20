#include <opencv2/opencv.hpp>
#include <iostream>
#include "libs/brut-voronoi.h"
#include "deps/argparse.h"
#include "libs/image-approximation.h"
#include "libs/germ.h"

using namespace cv;
using namespace std;

int main (int argc, char * argv []) {
        argparse::ArgumentParser program("RunBrutVoronoi");

    program.add_argument("-i", "--input")
            .help("input image")
            .required();

    program.add_argument("-g", "--germs")
            .help("germ count")
            .action([](const string & value) { return stoi(value); })
            .required();

    program.add_argument("-o", "--output")
            .help("output file path");

    program.add_argument("-p", "--preview-image")
            .help("Preview the result image")
            .default_value(false)
            .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    } catch (const runtime_error& err) {
        cout << err.what() << endl;
        cout << program;
        exit(0);
    }

    auto inputFilePath = program.get<string>("--input");
    auto germCount = program.get<int>("--germs");

    Mat sourceImage = imread(inputFilePath, IMREAD_GRAYSCALE);
    Mat voronoi(sourceImage.rows, sourceImage.cols, CV_16UC1);
    auto germFactory = GermFactory();
    auto germs = germFactory.createRandomGerms(voronoi, germCount);
    DeDistanceCalculator distanceCalculator;
    map<int, vector<Point>> regions;
    brutVoronoi(voronoi, germs, distanceCalculator, regions);
    Mat outputImage(voronoi.rows, voronoi.cols, CV_8UC1);

    brutImageApproximation(sourceImage, voronoi, outputImage, germs, regions);


    if (program["--preview-image"] == true) {
        namedWindow("result", WINDOW_AUTOSIZE);
        imshow("result", outputImage);
        waitKey(0);
    }

    if (program.present("--output")) {
        imwrite(program.get<string>("--output"), outputImage);
    }

    return 0;
}