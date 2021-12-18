#include "bresenham.hpp"

#include <opencv2/highgui.hpp>

#include <cmath>
#include <chrono>
#include <thread>

int main() {
    cv::Mat image = cv::Mat(500, 500, CV_8UC1);
    
    double a = 0.0;
    const cv::Point center(250, 250);
    const int radius = 100;

    while (true) {
        image = cv::Scalar(255);
        circle(image, center, radius, 0);
        line(image,
             center,
             cv::Point(center.x + radius * std::cos(a), center.y + radius * std::sin(a)),
             0
        );
        cv::imshow("lab01", image);
        auto key = cv::waitKey(1000);
        if (key == 27)
            break;
        a += M_PI / 30;
    }
    return 0;
}
