#include "sobel.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image>\n";
        return -1;
    }
    cv::Mat img = cv::imread(argv[1]);
    cv::Mat res = sobelFilter(img);
    cv::imshow("lab03", res);
    cv::waitKey();
    return 0;
}
