#include "fill.hpp"

#include <algorithm>
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

void fillPolygon(cv::Mat image, std::vector<cv::Point> const& vertices, uint8_t color) {
    int maxy = std::accumulate(std::next(vertices.begin()), vertices.end(),
            vertices.front(),
            [](cv::Point p1, cv::Point p2) { return p1.y > p2.y ? p1 : p2; }).y;
    int miny = std::accumulate(std::next(vertices.begin()), vertices.end(),
            vertices.front(),
            [](cv::Point p1, cv::Point p2) { return p1.y > p2.y ? p2 : p1; }).y;
    std::vector<std::vector<float>> yarr(maxy);
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        std::size_t next = 0;
        if (i != vertices.size() - 1)
            next = i + 1;
        std::size_t up = 0, down = 0;
        if (vertices[i].y > vertices[next].y) {
            up = i;
            down = next;
        } else if (vertices[i].y < vertices[next].y) {
            up = next;
            down = i;
        } else {
            continue;
        }

        float k = static_cast<float>(vertices[up].y - vertices[down].y) / static_cast<float>(vertices[up].x - vertices[down].x);
        for (int j = vertices[down].y; j < vertices[up].y; ++j) {
            yarr[j].push_back((j - vertices[down].y)/k + vertices[down].x);
        }
        for (int y = miny; y < maxy; ++y) {
            auto xarr = yarr[y];
            std::sort(xarr.begin(), xarr.end());
            for (std::size_t j = 0; j < xarr.size(); j += 2) {
                uint8_t* row = image.ptr(y);
                for (float x = xarr[j]; x < xarr[j + 1]; x += 1.0f)
                    row[static_cast<int>(std::floor(x))] = color;
            }
        }
    }
}
