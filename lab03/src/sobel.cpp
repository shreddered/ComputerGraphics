#include "sobel.hpp"

#include <opencv2/core.hpp>

#include <algorithm>
#include <cmath>

cv::Mat sobelFilter(cv::Mat src) {
    cv::Mat res;
    src.copyTo(res);
    int kx[3][3] = {-1, 0 , 1, -2, 0, 2, -1, 0, 1};
    int ky[3][3] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    for(int y = 1; y < src.size().height - 1; ++y){
        for(int x = 1; x < src.size().width - 1; ++x){
            cv::Rect roi(x - 1, y - 1, 3, 3);
            cv::Mat tmp = src(roi);
            cv::Mat matrix(3, 3, CV_32FC1);
            std::transform(tmp.begin<cv::Vec3b>(), tmp.end<cv::Vec3b>(),
                           matrix.begin<float>(),
                           [](cv::Vec3b vec) { return vec[0] / 3. + vec[1] / 3. + vec[2]/ 3.; });

            float sumx = 0;
            float sumy = 0;

            for(int s = 0; s < 3; ++s){
                for(int t = 0; t < 3; ++t){
                    sumx = sumx + matrix.at<float>(s, t) * kx[s][t];
                    sumy = sumy + matrix.at<float>(s, t) * ky[s][t];
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
