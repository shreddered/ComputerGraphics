#ifndef INCLUDE_BEZIER_HPP_
#define INCLUDE_BEZIER_HPP_

#include <opencv2/core.hpp>

#include <opencv2/core/types.hpp>
#include <vector>

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
 * Draw bezier line.
 *
 * @param image Image where bezier will be drawn.
 * @param p0, p1, p2 First, second and third point respectively.
 * @param color Color of a line.
 */
void bezier(cv::Mat image, cv::Point p0, cv::Point p1, cv::Point p2, uint8_t color);

/**
 * Rotate bezier line around X axis.
 *
 * @param image Image where bezier will be drawn.
 * @param p0, p1, p2 First, second and third point respectively.
 * @param color Color of a line.
 */
void bezierRotateX(cv::Mat image, cv::Point p0, cv::Point p1, cv::Point p2, uint8_t color);

/**
 * Rotate bezier line around Y axis.
 *
 * @param image Image where bezier will be drawn.
 * @param p0, p1, p2 First, second and third point respectively.
 * @param color Color of a line.
 */
void bezierRotateY(cv::Mat image, cv::Point p0, cv::Point p1, cv::Point p2, uint8_t color);

/**
 * Rotate bezier line around Z axis.
 *
 * @param image Image where bezier will be drawn.
 * @param p0, p1, p2 First, second and third point respectively.
 * @param color Color of a line.
 */
void bezierRotateZ(cv::Mat image, cv::Point p0, cv::Point p1, cv::Point p2, uint8_t color);

#endif // INCLUDE_BEZIER_HPP_
