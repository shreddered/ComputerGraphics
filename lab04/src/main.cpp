#include "bezier.hpp" 

#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

struct Params {
    cv::Mat image;
    cv::Point first, second, third;
}; // struct Params

void mouseCallback(int event, int x, int y, int flags, void* params) {
    Params* tmp = reinterpret_cast<Params*>(params);
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            if (tmp->first == cv::Point(-1, -1)) {
                tmp->first = cv::Point(x, y);
            } else if (tmp->second == cv::Point(-1, -1)) {
                tmp->second = cv::Point(x, y);
            } else if (tmp->third == cv::Point(-1, -1)) {
                tmp->third = cv::Point(x, y);
                // draw bezier
                tmp->image = cv::Scalar(255);
                bezier(tmp->image, tmp->first, tmp->second, tmp->third, 0);
                cv::imshow("lab04", tmp->image);
            }
            break;
        case cv::EVENT_MOUSEMOVE:
            if (tmp->first != cv::Point(-1, -1) && tmp->second != cv::Point(-1, -1)
                    && tmp->third == cv::Point(-1, -1)) {
                // draw bezier for floating third point
                cv::Point third(x, y);
                tmp->image = cv::Scalar(255);
                bezier(tmp->image, tmp->first, tmp->second, third, 0);
                cv::imshow("lab04", tmp->image);
            }
            break;
        default:
            break;
    }
}

int main() {
    Params params = { cv::Mat(500, 500, CV_8UC1, cv::Scalar(255)),
                      cv::Point(-1, -1),
                      cv::Point(-1, -1),
                      cv::Point(-1, -1)
                    };
    cv::namedWindow("lab04");
    cv::imshow("lab04", params.image);
    cv::setMouseCallback("lab04", mouseCallback, &params);
    cv::waitKey(0);
    return 0;
}
