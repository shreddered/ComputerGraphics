#ifndef INCLUDE_RENDER_HPP_
#define INCLUDE_RENDER_HPP_

#include <opencv2/core.hpp>

#include <cstdint>
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
void polygon(cv::Mat image, std::vector<cv::Point> const& vertices, bool flag, cv::Vec3b color);

/**
 * Fill a polygon.
 *
 * @param image Image with a polygon.
 * @param vertices Polygon's vertices
 * @param color Filling color.
 */
void fillPolygon(cv::Mat image, std::vector<cv::Point> const& vertices, cv::Vec3b color);

void renderDiamond(cv::Mat image);

#endif // INCLUDE_RENDER_HPP_
