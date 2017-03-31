/*
	使用FLANN进行特征点匹配: FlannBasedMatcher
	找到最佳匹配: DescriptorMatcher::match
	版本一: void DescriptorMatcher::match(
			     const Mat& queryDescriptors,  // 查询描述符集
				 const Mat& trainDescriptors,  // 训练描述符集
				 vector<DMatch>& matches,      // 得到的匹配
				 const Mat& mask=Mat()         // 指定输入查询和训练描述符允许匹配的掩膜
			);
	
	版本二: void DescriptorMatcher::match(
	             const Mat& queryDescriptors,            // 查询描述符集
				 vector<DMatch>& matches,                // 得到的匹配
				 const vector<Mat>& masks=vector<Mat>()  // 一组掩膜, 每个masks[i]从第i个图像trainDescCollection[i]指定输入查询和训练描述符允许撇皮的掩膜
	        );
*/

#include <opencv2/core/core.hpp>	
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>	
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	// 1. 载入图像
	Mat img_1 = imread("1.jpg");
	Mat img_2 = imread("2.jpg");
	if (!img_1.data || !img_2.data) return -1;

	// 2. 利用SURF检测关键点
	int minHessian = 300;
	SURF detector(minHessian);
	vector<KeyPoint> keypoint_1, keypoint_2;
	detector.detect(img_1, keypoint_1);
	detector.detect(img_2, keypoint_2);

	// 3. 计算描述符(特征向量)
	SURF extractor;
	Mat descriptors_1, descriptors_2;
	extractor.compute(img_1, keypoint_1, descriptors_1);
	extractor.compute(img_2, keypoint_2, descriptors_2);

	// 4. 采用FLANN算法检测描述符向量
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	// 5. 快速计算关键点之间的最大和最小距离
	double max_dist = 0; double min_dist = 100;
	
	for (int i = 0; i < descriptors_1.rows; ++i)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	// 输出距离信息
	printf("> 最大距离: %f\n", max_dist);
	printf("> 最小距离: %f\n", min_dist);

	// 6. 存下符合条件的匹配结果(即距离小于2*min_dist的), 使用radiusMatch同样可行
	vector<DMatch> good_matches;
	for (int i = 0; i < descriptors_1.rows; ++i)
	{
		if (matches[i].distance < 2 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	// 7. 检测出符合条件的匹配点
	Mat img_matches;
	drawMatches(img_1, keypoint_1, img_2, keypoint_2, good_matches, img_matches, 
		Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	// 8. 输出相关匹配点信息
	for (int i = 0; i < good_matches.size(); ++i)
	{
		printf("> 符合条件匹配点[%d]  特征点1: %d -- 特征点2: %d \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);
	}

	imshow("Dst Image", img_matches);

	waitKey(0);
	return 0;
}
