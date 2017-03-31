/*
	1. 绘制匹配点: drawMatches()
	版本1: void drawMatches(
	            const Mat& img1,
	            const vector<KeyPoint>& keypoints1,
				const Mat& img2,
				const vector<KeyPoint>& keypoints2,
				const vector<DMatch>& matches1to2,
				Mat& outImg,
				const Scalar& matchColor=Scalar::all(-1),
				const Scalar& singlePointColor=Scalar::all(-1),
				const vector<char>& matchesMask=vector<char>(),
				int flags=DrawMatchesFlags::DEFAULT
			)
	版本2: void drawMatches(
	            const Mat& img1,
				const vector<KeyPoint>& keypoints1,
				const Mat& img2,
				const vector<KeyPoint>& keypoints2,
				const vector<vector<DMatch> >& matches1to2,  // **
				Mat& outImg,
				const Scalar& matchColor=Scalar::all(-1),
				const Scalar& singlePointColor=Scalar::all(-1),
				const vector<vector<char> >& matchesMask=vector<vector<char> >(),  // **
				int flags=DrawMatchesFlags::DEFAULT
		   )
		   @param img1       : 第一幅源图
		   @param keypoints1 : 输出参数, 根据第一幅源图得到的特征点
		   @param img2       : 第二幅源图
		   @param keypoints2 : 输出参数, 根据第二幅源图得到的特征点
		   @param mathces1to2      : 第一幅图到第二幅图的匹配点(一一对应)
		   @param outImg           : 输出图像, 取决于flags
		   @param matchColor       : 匹配的输出颜色, 即线和关键点的颜色, 默认随机
		   @param singlePointColor : 单一特征点的颜色
		   @param matchesMask      : 确定哪些匹配是会绘制出来的掩膜, 为空表示全都进行绘制
		   @param flags            : 特征绘制标识符.

	2. BruteForceMatcher类用到最多的match(), 是从DescriptorMatcher类继承而来的
	   //  为各种描述符找到一个最佳的匹配(若掩膜为空)
	       CV_WRAP void match(
		       const Mat& queryDescriptors, 
		       const Mat& trainDescriptors, 
		       CV_OUT vector<DMatch>& matches, 
		       const Mat& mask=Mat() 
	       )const;
*/

// 使用DescriptorExtractor接口来寻找关键点对应的特征向量
// 使用SurfDescriptorExtractor以及它的函数compute()来完成特定的计算
// 使用BruteForceMatcher来匹配特征向量
// 使用drawMatches()来绘制检测到的匹配点

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	// 1. 加载图像
	Mat srcImage1 = imread("1.jpg", IMREAD_COLOR);
	Mat srcImage2 = imread("2.jpg", IMREAD_COLOR);
	if (!srcImage1.data || !srcImage2.data) return -1;

	// 2. 使用SURF算子检测关键点
	int minHessian = 700;   // hessian阈值
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> keyPoint1, keyPoint2;

	// 3. 调用detect()检测出SURF特征关键点, 保存在vector容器中
	detector.detect(srcImage1, keyPoint1);
	detector.detect(srcImage2, keyPoint2);

	// 4. 计算描述符(特征向量)
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(srcImage1, keyPoint1, descriptors1);
	extractor.compute(srcImage2, keyPoint2, descriptors2);

	// 5. 使用BruteForce进行匹配

	// 实例化一个匹配器
	BruteForceMatcher<L2<float> > matcher;
	vector<DMatch> matches;
	// 匹配两幅图中的描述子(Descriptor)
	matcher.match(descriptors1, descriptors2, matches);

	// 6. 绘制从两个图像中匹配出来的关键点
	Mat imgMatches;
	drawMatches(srcImage1, keyPoint1, srcImage2, keyPoint2, matches, imgMatches, Scalar::all(-1), Scalar(0, 0, 255));

	imshow("匹配图", imgMatches);

	waitKey(0);

	return 0;
}
