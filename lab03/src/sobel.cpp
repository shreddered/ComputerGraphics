#include "sobel.hpp"

#include <cmath>
#include <opencv2/core/matx.hpp>

cv::Mat sobelFilter(cv::Mat src) {
    cv::Mat res;
    src.copyTo(res);
    int kx[3][3] = {-1, 0 , 1, -2, 0, 2, -1, 0, 1};
    int ky[3][3] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    for(int y = 1; y < src.size().height - 1; ++y){
        for(int x = 1; x < src.size().width - 1; ++x){
            int a = src.at<cv::Vec3b>(y - 1, x - 1).dot(cv::Vec3i::all(1)) / 3;
            int b = src.at<cv::Vec3b>(y, x - 1).dot(cv::Vec3i::all(1)) / 3;
            int c = src.at<cv::Vec3b>(y + 1, x - 1).dot(cv::Vec3i::all(1)) / 3;
            int d = src.at<cv::Vec3b>(y - 1, x).dot(cv::Vec3i::all(1)) / 3;
            int e = src.at<cv::Vec3b>(y, x).dot(cv::Vec3i::all(1)) / 3;
            int f = src.at<cv::Vec3b>(y + 1, x).dot(cv::Vec3i::all(1)) / 3;
            int g = src.at<cv::Vec3b>(y - 1, x + 1).dot(cv::Vec3i::all(1)) / 3;
            int h = src.at<cv::Vec3b>(y, x + 1).dot(cv::Vec3i::all(1)) / 3;
            int i = src.at<cv::Vec3b>(y + 1, x + 1).dot(cv::Vec3i::all(1)) / 3;

            int matrix[3][3] = {a,b,c,d,e,f,g,h,i};

            int sumx = 0;
            int sumy = 0;

            for(int s = 0; s < 3; ++s){
                for(int t = 0; t < 3; ++t){
                    sumx = sumx + (matrix[s][t] * kx[s][t]);
                    sumy = sumy + (matrix[s][t] * ky[s][t]);
                }
            }

            int newValue = std::sqrt(std::pow(sumx, 2) + std::pow(sumy, 2));

            if(newValue < 0){
                newValue = 0;
            }
            if(newValue > 255){
                newValue = 255;
            }
            res.at<cv::Vec3b>(y, x) = cv::Vec3b::all(newValue);
        }
    }

    return res;
}
