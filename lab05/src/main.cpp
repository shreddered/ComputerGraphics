#include "fill.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

struct Params {
    cv::Mat image;
    std::vector<cv::Point> vertices;
    bool isDrawn;
}; // struct Params

void mouseCallback(int event, int x, int y, int flags, void* params) {
    Params* tmp = reinterpret_cast<Params*>(params);
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            if (!tmp->isDrawn)
                tmp->vertices.emplace_back(x, y);
            break;
        case cv::EVENT_MOUSEMOVE:
            if (!tmp->vertices.empty() && !tmp->isDrawn) {
                tmp->image = cv::Scalar(255);
                polygon(tmp->image, tmp->vertices, tmp->isDrawn, 0);
                cv::Point from = tmp->vertices.back();
                line(tmp->image, from, cv::Point(x, y), 0);
                cv::imshow("lab05", tmp->image);
            }
            break;
        case cv::EVENT_MBUTTONDOWN:
            if (!tmp->vertices.empty()) {
                tmp->isDrawn = true;
                tmp->image = cv::Scalar(255);
                polygon(tmp->image, tmp->vertices, tmp->isDrawn, 0);
                fillPolygon(tmp->image, tmp->vertices, 0);
                cv::imshow("lab05", tmp->image);
            }
            break;
        default:
            break;
    }
}

int main() {
    Params params = { cv::Mat(500, 500, CV_8UC1, cv::Scalar(255)),
                      std::vector<cv::Point>(),
                      false
                    };
    cv::namedWindow("lab05");
    cv::imshow("lab05", params.image);
    cv::setMouseCallback("lab05", mouseCallback, &params);
    cv::waitKey(0);
    return 0;
}
