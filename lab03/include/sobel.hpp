#ifndef INCLUDE_SOBEL_HPP_
#define INCLUDE_SOBEL_HPP_

#include <opencv2/core.hpp>

/**
 * Sobel filter.
 * @param src Image to be processed.
 * @return Filtered image.
 */
cv::Mat sobelFilter(cv::Mat src);

#endif // INCLUDE_SOBEL_HPP_
