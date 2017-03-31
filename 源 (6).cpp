/*
	1. 绘制关键点: drawKeyPoints()
	      void drawKeyPoints(
	          const Mat& images,                    // 输入图像
			  const vector<KeyPoint>& keypoints,    // 输出的特征点
			  Mat& outImage,                        // 输出图像, 取决于第五个参数flags
			  const Scalar& color=Scalar::all(-1),  // 关键点颜色
			  int flags=DrawMatchesFlags::DEFAULT   // 绘制关键点的特征标识符
	          );

	   特征标识符:
	          struct DrawMatchesFlags{
			      enum{
				      DEFAULT = 0,                  // 创建输出矩阵(使用Mat::create()). 使用现存的输出图像绘制匹配对和特征点, 且每一个关键点, 只绘制中间点
					  DRAW_OVER_OUTIMG = 1,         // 不创建输出图像矩阵, 而是在输出图像上绘制匹配对
					  ONT_DRAW_SINGLE_POINTS = 2,   // 单点特征点不被绘制
					  DRAW_RICH_KEYPOINTS = 4       // 对每一个关键点, 绘制带大小和方向的关键圆圈
				  };
			  };

	2. KeyPoint类:
	          class KeyPoint{
			      Point2f pt;        // 坐标
				  float size;        // 特征点邻域直径
				  float angle;       // 特征点的方向, 值为(0, 360), 负数表示不使用
				  float response;    
				  int octave;        // 特征点所在的图像金字塔的组
				  int class_id;      // 用于聚类的id
			  };
*/
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <iostream>

using namespace cv;

int main()
{
	system("color 2f");

	Mat srcImage1 = imread("1.jpg");
	Mat srcImage2 = imread("2.jpg");
	if (!srcImage1.data || !srcImage2.data) return -1;

	// 定义需要用到的变量和类
	int minHessian = 400;   // 定义SURF中的Hessian阈值特征点检测算子
	SurfFeatureDetector detector(minHessian);  // 定义一个SURF特征检测对象
	std::vector<KeyPoint> keypoint_1, keypoint_2;  // vector模板类是能够存放任意类型的动态数组, 能够增加和压缩数据

	// 调用detect函数检测出SURF特征关键点, 保存在vector中
	// CV_WRAP void detect(const Mat& image, CV_OUT vector<KeyPoint>& keypoints, const Mat& mask=Mat()) const;
	// void detect(const vector<Mat>& image, vector<vector<KeyPoint> >& keypoints, const vector<Mat> mask=vector<Mat>())const;
	detector.detect(srcImage1, keypoint_1);
	detector.detect(srcImage2, keypoint_2);

	// 绘制关键点
	Mat img_keypoint_1; Mat img_keypoint_2;
	drawKeypoints(srcImage1, keypoint_1, img_keypoint_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcImage2, keypoint_2, img_keypoint_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	// Display
	imshow("特征点检测效果1", img_keypoint_1);
	imshow("特征点检测效果2", img_keypoint_2);

	waitKey(0);

	return 0;
}

