#include <iostream>
#include "deps/argparse.h"
#include <opencv2/opencv.hpp>
#include "libs/germ.h"

using namespace std;
using namespace cv;

int main (int argc, char * argv []) {
    argparse::ArgumentParser program("RunBrutVoronoi");

    program.add_argument("-i", "--input")
            .help("input image")
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
    auto image = imread(inputFilePath, IMREAD_GRAYSCALE);
    auto pixelsCount = image.cols * image.rows;
    auto germsCount = round(0.02 * pixelsCount);
    auto germFactory = GermFactory();
    auto germs = germFactory.createRandomGerms(image, germsCount);

    cout << "Hello world" << endl;
    return 0;
}