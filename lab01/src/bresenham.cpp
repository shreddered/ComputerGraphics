#include "bresenham.hpp"

#include <cmath>
#include <cstdint>

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

void circle(cv::Mat image, cv::Point center, int radius, uint8_t color) {
    int x = 0, y = radius;
    int delta = 1 - (radius << 1);
    int error = 0;
    while (y >= 0) {
        image.at<uint8_t>(center.y + y, center.x + x) = color;
        image.at<uint8_t>(center.y - y, center.x + x) = color;
        image.at<uint8_t>(center.y + y, center.x - x) = color;
        image.at<uint8_t>(center.y - y, center.x - x) = color;
        error = ((delta + y) << 1) - 1;
        if (delta < 0 &&  error <= 0) {
            ++x;
            delta += (x << 1) + 1;
            continue;
        }
        error = ((delta - x) << 1) - 1;
        if (delta > 0 && error > 0) {
            --y;
            delta += 1 - (y << 1);
            continue;
        }
        ++x;
        delta += (x - y) << 1;
        --y;
    }
}
