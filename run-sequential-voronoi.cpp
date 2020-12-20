#include <opencv2/opencv.hpp>
#include <iostream>
#include "deps/argparse.h"
#include "libs/sequential-voronoi.h"
#include "libs/germ.h"

using namespace cv;
using namespace std;

int main (int argc, char * argv[]) {
    argparse::ArgumentParser program("RunSequentialVoronoi");

    program.add_argument("-w", "--width")
            .help("width of the generated image")
            .action([](const string & value) { return stoi(value); })
            .required();

    program.add_argument("-h", "--height")
            .help("height of the generated image")
            .action([](const string & value) { return stoi(value); })
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

    auto width = program.get<int>("--width");
    auto height = program.get<int>("--height");
    auto germCount = program.get<int>("--germs");

    Mat mat (height, width, CV_8UC3);
    auto germFactory = GermFactory();
    auto germs = germFactory.createRandomGerm(mat, germCount);
    auto report = sequentialVoronoi(mat, germs);

    if (program["--preview-image"] == true) {
        namedWindow("result");
        imshow("result", mat);
        waitKey(0);
    }

    if (program.present("--output")) {
        imwrite(program.get<string>("--output"), mat);
    }

    cout << to_string(get<0>(report)) << " iterations in " << to_string(get<1>(report)) << "s";

    return 0;
}