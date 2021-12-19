#include "render.hpp"

#include <algorithm>
#include <numeric>
#include <iostream>

void line(cv::Mat image, cv::Point from, cv::Point to, cv::Vec3b color) {
    const int dx = std::abs(from.x - to.x), dy = std::abs(from.y - to.y);
    const int signX = from.x < to.x ? 1 : -1,
              signY = from.y < to.y ? 1 : -1;
    int error = dx - dy;
    image.at<cv::Vec3b>(to) = color;
    cv::Point p = from;
    while (p.x != to.x || p.y != to.y) {
        image.at<cv::Vec3b>(p) = color;
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

void polygon(cv::Mat image, std::vector<cv::Point> const& vertices, bool flag, cv::Vec3b color) {
    for (std::size_t i = 0; i < vertices.size() - 1; ++i) {
        line(image, vertices[i], vertices[i + 1], color);
    }
    if (flag)
        line(image, vertices.back(), vertices.front(), color);
}

void fillPolygon(cv::Mat image, std::vector<cv::Point> const& vertices, cv::Vec3b color) {
    int maxy = std::accumulate(std::next(vertices.begin()), vertices.end(),
            vertices.front(),
            [](cv::Point p1, cv::Point p2) { return p1.y > p2.y ? p1 : p2; }).y;
    int miny = std::accumulate(std::next(vertices.begin()), vertices.end(),
            vertices.front(),
            [](cv::Point p1, cv::Point p2) { return p1.y > p2.y ? p2 : p1; }).y;
    std::vector<std::vector<double>> yarr(maxy);
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

        double k = double(vertices[up].y - vertices[down].y) / (vertices[up].x - vertices[down].x);
        for (std::size_t j = vertices[down].y; j < vertices[up].y; ++j) {
            yarr[j].push_back((j - vertices[down].y)/k + vertices[down].x);
        }
        for (std::size_t y = miny; y < maxy; ++y) {
            auto xarr = yarr[y];
            std::sort(xarr.begin(), xarr.end());
            for (std::size_t j = 0; j < xarr.size() / 2; ++j) {
                for (auto x = xarr[j << 1]; x < xarr[(j << 1) + 1]; ++x) {
                    image.at<cv::Vec3b>(y, std::floor(x)) = color;
                }
            }
        }
    }
}

float cosine(cv::Vec3f a, cv::Vec3f b) {
    return a.dot(b) / (std::sqrt(std::pow(a[0], 2) + std::pow(a[1], 2) + std::pow(a[2], 2))
            * std::sqrt(std::pow(b[0], 2) + std::pow(b[1], 2) + std::pow(b[2], 2)));
}

void renderDiamond(cv::Mat image) {
    int x0 = 250, y0 = 200, z0 = -200;
    std::vector<cv::Vec3f> diamondVertices = {
        cv::Vec3f(x0 + 0, y0 + 0, z0 + 78),
        cv::Vec3f(x0 + 45, y0 + 45, z0 + 0),
        cv::Vec3f(x0 + 45, y0 + -45, z0 + 0),
        cv::Vec3f(x0 - 45, y0 + -45, z0 + 0),
        cv::Vec3f(x0 - 45, y0 + 45, z0 + 0),
        cv::Vec3f(x0 + 0, y0 + 0, z0 - 78)
    };
    float alphax = M_PI / 2, alphay = M_PI / 6;

    float datax[] = { 1,                0,                 0, 0,
                      0, std::cos(alphax), -std::sin(alphax), 0,
                      0, std::sin(alphax),  std::cos(alphax), 0,
                      0,                0,                 0, 1 };

    float datay[] = { std::sin(alphay), 0,  std::cos(alphay), 0,
                                     0, 1,                 0, 0,
                      std::cos(alphay), 0, -std::sin(alphay), 0,
                                     0, 0,                 0, 1 };
    cv::Mat mx(4, 4, CV_32FC1, datax);
    cv::Mat my(4, 4, CV_32FC1, datay);
    for (auto& elem : diamondVertices) {
        cv::Mat rotated = mx * cv::Vec4f(elem[0], elem[1], elem[2], 1);
        rotated = my * rotated;
        elem = cv::Vec3f(rotated.at<float>(0, 0), rotated.at<float>(0, 1),
                rotated.at<float>(0, 2));
    }
    std::vector<std::vector<size_t>> diamondFacets = {
        { 0, 1, 2 },
        { 0, 2, 3 },
        { 0, 3, 4 },
        { 0, 4, 1 },
        { 5, 4, 3 },
        { 5, 3, 2 },
        { 5, 2, 1 },
        { 5, 1, 4 }
    };
    float I_fon = 20, I_p = 235, K_p = 0.4;
    cv::Vec3f lamp(50, 20, 5);
    for (const auto& elem : diamondFacets) {
        auto p0 = diamondVertices[elem[0]], p1 = diamondVertices[elem[1]],
             p2 = diamondVertices[elem[2]];
        auto center12 = (p1 + p2) / 2;
        auto center = (center12 + p0) / 2;
        auto light = lamp - center;
        cv::Vec3f normal(
                (p1[1] - p0[1]) * (p2[2] - p0[2]) - (p2[1] - p0[1]) * (p1[2] - p0[2]),
                (p2[0] - p0[0]) * (p1[2] - p0[2]) - (p1[0] - p0[0]) * (p2[2] - p0[2]),
                (p1[0] - p0[0]) * (p2[1] - p0[1]) - (p2[0] - p0[0]) * (p1[1] - p0[1]));
        cv::Vec3f observer(0, 0, -1);
        if (cosine(normal, observer) >= 0) {
            float cosphi = cosine(light, normal);
            float I = I_fon + K_p * I_p * cosphi;
            cv::Point p0_ = cv::Point(p0[0], p0[1]),
                      p1_ = cv::Point(p1[0], p1[1]),
                      p2_ = cv::Point(p2[0], p2[1]);
            fillPolygon(image, { p0_, p1_, p2_ }, cv::Vec3b(0, 0, I));
            line(image, p0_, p1_, cv::Vec3b(0, 0, I));
            line(image, p0_, p2_, cv::Vec3b(0, 0, I));
            line(image, p2_, p1_, cv::Vec3b(0, 0, I));
        }
    }
}
