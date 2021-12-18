#ifndef INCLUDE_BRESENHAM_HPP_
#define INCLUDE_BRESENHAM_HPP_

#include <opencv2/core.hpp>

/**
 * Draw a line.
 *
 * @param image Grayscale image where a line will be drawn.
 * @param from Start point.
 * @param to End point.
 * @param color Color of a line.
 */
void line(cv::Mat image, cv::Point from, cv::Point to, uint8_t color);

/**
 * Draw a circle.
 *
 * @param image Grayscale image where a circle will be drawn.
 * @param center Center of a circle.
 * @param radius Radius of a circle.
 * @paral color Line color.
 */
void circle(cv::Mat image, cv::Point center, int radius, uint8_t color);

#endif // INCLUDE_BRESENHAM_HPP_
