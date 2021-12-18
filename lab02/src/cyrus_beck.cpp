#include "cyrus_beck.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>

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

void polygon(cv::Mat image, std::vector<cv::Point> const& vertices, bool flag, uint8_t color) {
    for (std::size_t i = 0; i < vertices.size() - 1; ++i) {
        line(image, vertices[i], vertices[i + 1], color);
    }
    if (flag)
        line(image, vertices.back(), vertices.front(), color);
}

float max(float a, float b) {
    return (a < b) ? b : a;
}

float min(float a, float b) {
    return (a < b) ? a : b;
}

std::pair<cv::Point, cv::Point> cyrusBeck(std::vector<cv::Point> const& vertices,
                                          cv::Point from,
                                          cv::Point to) {
    std::vector<cv::Point> normal(vertices.size());
    for (std::size_t i = 0; i <  vertices.size(); ++i) {
        normal[i].y = vertices[(i + 1) % vertices.size()].x - vertices[i].x;
        normal[i].x = vertices[i].y - vertices[(i + 1) % vertices.size()].y;
    }
    cv::Point diff = to - from;
    std::vector<cv::Point> P0_PEi(vertices.size());
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        P0_PEi[i] = vertices[i] - from;
    }
    std::vector<int> numerator(vertices.size()), denominator(vertices.size());
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        numerator[i] = normal[i].dot(P0_PEi[i]);
        denominator[i] = normal[i].dot(diff);
    }
    std::vector<float> tE, tL;
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        float t = float(numerator[i]) / float(denominator[i]);
        if (denominator[i] > 0)
            tE.push_back(t);
        else
            tL.push_back(t);
    }
    float tmp[2];
    tmp[0] = std::accumulate(tE.begin(), tE.end(), 0.0f, max);
    tmp[1] = std::accumulate(tL.begin(), tL.end(), 1.0f, min);
    if (tmp[0] > tmp[1])
        return std::make_pair(cv::Point(-1, -1), cv::Point(-1, -1));
    std::pair<cv::Point, cv::Point> res;
    res.first = cv::Point(float(from.x) + float(diff.x) * tmp[0], 
                          float(from.y) + float(diff.y) * tmp[0]);
    res.second = cv::Point(float(from.x) + float(diff.x) * tmp[1],
                           float(from.y) + float(diff.y) * tmp[1]);
    return res;
}
