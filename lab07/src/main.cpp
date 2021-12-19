#include "render.hpp"

#include <opencv2/highgui.hpp>

int main() {
    cv::Mat image(800, 800, CV_8UC3, cv::Scalar(0, 0, 0));
    renderDiamond(image);
    cv::namedWindow("lab07");
    cv::imshow("lab07", image);
    cv::waitKey();
    return 0;
}
