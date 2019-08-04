//
// Created by janos on 04.08.19.
//

#include "sudoku.h"

#include <fmt/core.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>


int main(int argc, char** argv)
{

    if(argc != 2)
    {
        fmt::print("Ich will genau ein(en Pfad zu einem) Sudoku!\n");
        return 1;
    }

    std::string path(argv[1]);

    fmt::print("{}\n", path);

    cv::Mat image = cv::imread(path), edges, closed, opened;

    cv::Canny(image, edges, 100, 120);

    auto kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));

    cv::morphologyEx(edges, closed, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(edges, opened, cv::MORPH_OPEN, kernel);


    cv::imshow("display", closed);
    cv::waitKey(0);


    Sudoku sudoku
            {{
                     0, 1, 2,    7, 0, 0,    0, 0, 0,
                     0, 7, 0,    6, 0, 8,    0, 0, 0,
                     0, 0, 0,    0, 0, 0,    8, 3, 0,

                     0, 0, 8,    0, 0, 7,    0, 0, 0,
                     0, 0, 0,    0, 0, 0,    3, 5, 0,
                     0, 0, 6,    0, 0, 4,    0, 0, 0,

                     2, 4, 0,    0, 0, 0,    0, 0, 0,
                     0, 0, 0,    0, 5, 0,    0, 1, 6,
                     1, 0, 0,    0, 8, 0,    9, 0, 0
             }};



}