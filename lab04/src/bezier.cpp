#include "bezier.hpp"

void line(cv::Mat image, cv::Point from, cv::Point to, uint8_t color) {
    const int dx = std::abs(from.x - to.x), dy = std::abs(from.y - to.y);
    const int signX = from.x < to.x ? 1 : -1,
              signY = from.y < to.y ? 1 : -1;
    int error = dx - dy;
    image.at<uint8_t>(to) = color;
    cv::Point p = from;
    while (p.x != to.x || p.y != to.y) {
        image.at<uint8_t>(p) = color;
        int error2 = error << 1;
        if (error2 > -dy) {
            error -= dy;
            p.x += signX;
        }
        if (error2 < dx) {
            error += dx;
            p.y += signY;
        }
    }
}

double distance(cv::Point p0, cv::Point p1, cv::Point p2) {
    double k = double(p2.y - p0.y) / (p2.x - p0.x);
    double b = -k * p0.x + p0.y;
    return std::abs(-k * p1.x + p1.y - b)/std::sqrt(k * k + 1);
}

void bezier(cv::Mat image, cv::Point p0, cv::Point p1, cv::Point p2, uint8_t color) {
    if (distance(p0, p1, p2) > 1) {
        cv::Point p0_1 = (p0 + p1) / 2,
                  p1_1 = (p1 + p2) / 2,
                  p0_2 = (p0_1 / 2 + p1_1 / 2);
        bezier(image, p0, p0_1, p0_2, color);
        bezier(image, p0_2, p1_1, p2, color);
    } else {
        line(image, p0, p2, color);
    }
}
