#ifndef INCLUDE_BRESENHAM_HPP_
#define INCLUDE_BRESENHAM_HPP_

#include <opencv2/core.hpp>

void line(cv::Mat image, cv::Point from, cv::Point to, uint8_t color);

void circle(cv::Mat image, cv::Point center, int radius, uint8_t color);

#endif // INCLUDE_BRESENHAM_HPP_
