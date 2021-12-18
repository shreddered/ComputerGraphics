#include "cyrus_beck.hpp"

#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

struct Params {
    cv::Mat image;
    std::vector<cv::Point> vertices;
    cv::Point from, to;
    bool isDrawn;
}; // struct Params

void mouseCallback(int event, int x, int y, int flags, void* params) {
    Params* tmp = reinterpret_cast<Params*>(params);
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            if (!tmp->isDrawn) {
                tmp->vertices.emplace_back(x, y);
            } else if (tmp->from == cv::Point(-1, -1)) {
                tmp->from = cv::Point(x, y);
            } else if (tmp->to == cv::Point(-1, -1)) {
                tmp->to = cv::Point(x, y);
                tmp->image = cv::Scalar(255);
                polygon(tmp->image, tmp->vertices, tmp->isDrawn, 0);
                auto [from, to] = cyrusBeck(tmp->vertices, tmp->from, tmp->to);
                if (from != cv::Point(-1, -1) && to != cv::Point(-1, -1))
                    line(tmp->image, from, to, 0);
                tmp->from = cv::Point(-1, -1);
                tmp->to = cv::Point(-1, -1);
                cv::imshow("lab02", tmp->image);
            }
            break;
        case cv::EVENT_MOUSEMOVE:
            if (!tmp->vertices.empty() && !tmp->isDrawn) {
                tmp->image = cv::Scalar(255);
                polygon(tmp->image, tmp->vertices, tmp->isDrawn, 0);
                cv::Point from = tmp->vertices.back();
                line(tmp->image, from, cv::Point(x, y), 0);
                cv::imshow("lab02", tmp->image);
            } else if (tmp->isDrawn && tmp->from != cv::Point(-1, -1) 
                    && tmp->to == cv::Point(-1, -1)) {
                tmp->image = cv::Scalar(255);
                polygon(tmp->image, tmp->vertices, tmp->isDrawn, 0);
                line(tmp->image, tmp->from, cv::Point(x, y), 0);
                cv::imshow("lab02", tmp->image);
            }
            break;
        case cv::EVENT_MBUTTONDOWN:
            if (!tmp->vertices.empty()) {
                tmp->isDrawn = true;
                tmp->image = cv::Scalar(255);
                // tmp->vertices.emplace_back(tmp->vertices.front());
                polygon(tmp->image, tmp->vertices, tmp->isDrawn, 0);
                cv::imshow("lab02", tmp->image);
            }
            break;
        default:
            break;
    }
}

int main() {
    Params params = { cv::Mat(500, 500, CV_8UC1, cv::Scalar(255)),
                      std::vector<cv::Point>(),
                      cv::Point(-1, -1),
                      cv::Point(-1, -1),
                      false
                    };
    cv::namedWindow("lab02");
    cv::imshow("lab02", params.image);
    cv::setMouseCallback("lab02", mouseCallback, &params);
    cv::waitKey(0);
    return 0;
}
