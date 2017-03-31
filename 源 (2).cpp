#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace std;
using namespace cv;

int main()
{
	// 载入原图, 并转化为灰度
	Mat srcImage = imread("1.jpg");
	if (!srcImage.data) return -1;
	imshow("原图", srcImage);
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//--------------- 检测SIFT特征点并在图像中提取物体的描述符 --------------

	// 1. 参数定义
	OrbFeatureDetector featureDetector;
	vector<KeyPoint> keyPoints;
	Mat descriptors;

	// 2. 调用detect()检测出特征关键点, 保存在vector容器中
	featureDetector.detect(grayImage, keyPoints);

	// 3. 计算描述符(特征向量)
	OrbDescriptorExtractor featureExtractor;
	featureExtractor.compute(grayImage, keyPoints, descriptors);

	// 4. 基于FLANN的描述符对象匹配
	flann::Index flannIndex(descriptors, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);

	// 5. 初始化视频采集对象
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 360);    // 视频采集宽度
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 900);   // 视频采集高度

	unsigned int frameCount = 0;   // 帧数

	while (true)
	{
		double time0 = static_cast<double>(getTickCount());
		Mat captureImage, captureImage_gray;

		cap >> captureImage;	// 采集视频
		if (captureImage.empty()) continue;

		cvtColor(captureImage, captureImage_gray, CV_BGR2GRAY);

		// 7. 检测SIFT关键点并提取测试图中的描述符
		vector <KeyPoint> captureKeyPoints;
		Mat captureDescription;

		// 8. 调用detect函数检测出特征关键点, 保存到vector容器中
		featureDetector.detect(captureImage_gray, captureKeyPoints);

		// 9. 计算描述符
		featureExtractor.compute(captureImage_gray, captureKeyPoints, captureDescription);

		// 10. 匹配和测试描述符, 获取两个最邻近的描述符
		Mat matchIndex(captureDescription.rows, 2, CV_32SC1);
		Mat matchDistance(captureDescription.rows, 2, CV_32FC1);
		flannIndex.knnSearch(captureDescription, matchIndex, matchDistance, 2, flann::SearchParams());  // 调用K邻近算法

		// 11. 根据劳氏算法选出优秀匹配
		vector<DMatch> goodMatches;
		for (int i = 0; i < matchDistance.rows; ++i)
		{
			if (matchDistance.at<float>(i, 0) < 0.6 * matchDistance.at<float>(i, 1))
			{
				DMatch dmatches(i, matchIndex.at<int>(i, 0), matchDistance.at<float>(i, 0));
				goodMatches.push_back(dmatches);
			}
		}

		// 12. 绘制并显示匹配窗口
		Mat resultImage;
		drawMatches(captureImage, captureKeyPoints, srcImage, keyPoints, goodMatches, resultImage);
		imshow("匹配窗口", resultImage);

		// 13. 显示帧率
		cout << ">帧率 = " << getTickFrequency() / (getTickCount() - time0) << endl;

		// 程序退出
		if ((char)waitKey(1) == 27) break;
	}



	return 0;
}