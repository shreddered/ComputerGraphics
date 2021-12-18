#include "bezier.hpp"
#include <opencv2/core/matx.hpp>

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

void bezierRotateX(cv::Mat image, cv::Point _p0, cv::Point _p1, cv::Point _p2, uint8_t color) {
    cv::Vec3f p0(_p0.x, _p0.y, 0), p1(_p1.x, _p1.y, 0), p2(_p2.x, _p2.y, 0);
    cv::Vec3f p0_ = p0, p2_ = p2;
    for (std::size_t a = 0; a < 360; a += 10) {
        float alpha = a * M_PI / 180;
        p0_ -= p1;
        p2_ -= p1;
        float data[] = { 1,               0,                0, 0,
                         0, std::cos(alpha), -std::sin(alpha), 0,
                         0, std::sin(alpha),  std::cos(alpha), 0,
                         0,               0,                0, 1 };
        cv::Mat mx(4, 4, CV_32FC1, data);
        cv::Mat out = mx * cv::Vec4f(p0_[0], p0_[1], p0_[2], 1);
        cv::Point p0__(out.at<float>(0, 0) + p1[0], out.at<float>(0, 1) + p1[1]);
        out = mx * cv::Vec4f(p2_[0], p2_[1], p2_[2], 1);
        cv::Point p2__(out.at<float>(0, 0) + p1[0], out.at<float>(0, 1) + p1[1]);
        bezier(image, p0__, _p1, p2__, color);

        p0_ = p0;
        p2_ = p2;
    }
}

void bezierRotateY(cv::Mat image, cv::Point _p0, cv::Point _p1, cv::Point _p2, uint8_t color) {
    cv::Vec3f p0(_p0.x, _p0.y, 0), p1(_p1.x, _p1.y, 0), p2(_p2.x, _p2.y, 0);
    cv::Vec3f p0_ = p0, p2_ = p2;
    for (std::size_t a = 0; a < 360; a += 10) {
        float alpha = a * M_PI / 180;
        p0_ -= p1;
        p2_ -= p1;
        float data[] = { std::sin(alpha), 0,  std::cos(alpha), 0,
                                       0, 1,                0, 0,
                         std::cos(alpha), 0, -std::sin(alpha), 0,
                                       0, 0,                0, 1 };
        cv::Mat mx(4, 4, CV_32FC1, data);
        cv::Mat out = mx * cv::Vec4f(p0_[0], p0_[1], p0_[2], 1);
        cv::Point p0__(out.at<float>(0, 0) + p1[0], out.at<float>(0, 1) + p1[1]);
        out = mx * cv::Vec4f(p2_[0], p2_[1], p2_[2], 1);
        cv::Point p2__(out.at<float>(0, 0) + p1[0], out.at<float>(0, 1) + p1[1]);
        bezier(image, p0__, _p1, p2__, color);

        p0_ = p0;
        p2_ = p2;
    }
}

void bezierRotateZ(cv::Mat image, cv::Point _p0, cv::Point _p1, cv::Point _p2, uint8_t color) {
    cv::Vec3f p0(_p0.x, _p0.y, 0), p1(_p1.x, _p1.y, 0), p2(_p2.x, _p2.y, 0);
    cv::Vec3f p0_ = p0, p2_ = p2;
    for (std::size_t a = 0; a < 360; a += 10) {
        float alpha = a * M_PI / 180;
        p0_ -= p1;
        p2_ -= p1;
        float data[] = { std::cos(alpha), -std::sin(alpha), 0, 0,
                         std::sin(alpha),  std::cos(alpha), 0, 0,
                                       0,                0, 0, 0,
                                       0,                0, 0, 1 };
        cv::Mat mx(4, 4, CV_32FC1, data);
        cv::Mat out = mx * cv::Vec4f(p0_[0], p0_[1], p0_[2], 1);
        cv::Point p0__(out.at<float>(0, 0) + p1[0], out.at<float>(0, 1) + p1[1]);
        out = mx * cv::Vec4f(p2_[0], p2_[1], p2_[2], 1);
        cv::Point p2__(out.at<float>(0, 0) + p1[0], out.at<float>(0, 1) + p1[1]);
        bezier(image, p0__, _p1, p2__, color);

        p0_ = p0;
        p2_ = p2;
    }
}
