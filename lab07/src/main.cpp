#include "render.hpp"

#include <opencv2/highgui.hpp>

int main() {
    cv::Mat image(800, 800, CV_8UC3, cv::Scalar(255, 255, 255));
    renderDiamond(image);
    cv::namedWindow("lab07");
    cv::imshow("lab07", image);
    cv::waitKey();
    return 0;
}
