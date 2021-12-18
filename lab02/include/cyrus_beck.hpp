#ifndef INCLUDE_CYRUS_BECK_HPP_
#define INCLUDE_CYRUS_BECK_HPP_

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
 * Draw a polygon.
 *
 * @param image Grayscale image where a line will be drawn.
 * @param vertices Polygon's vertices.
 * @param flag Draw a line between last and first vertices?
 * @param color Color of a line.
 */
void polygon(cv::Mat image, std::vector<cv::Point> const& vertices, bool flag, uint8_t color);

/**
 * Cut a line that is inside of a given polygon.
 *
 * @param vertices Polygon's vertices.
 * @param from Line's start point.
 * @param to Line's end point.
 * @return Pair (start, end) for the line that is inside of the polygon.
 */
std::pair<cv::Point, cv::Point> cyrusBeck(std::vector<cv::Point> const& vertices,
                                          cv::Point from,
                                          cv::Point to);

#endif // INCLUDE_CYRUS_BECK_HPP_
