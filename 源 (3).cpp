// 用SURF进行关键点和描述符的提取, 然后用FLANN进行匹配

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace std;
using namespace cv;

int main()
{
	system("color 6F");

	// 1. 载入图像, 转为灰度图
	Mat trainImage = imread("1.jpg"), trainImage_gray;
	if (!trainImage.data) return -1;
	imshow("Src Image", trainImage);
	cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);

	// 2. 检测Surf关键点、提取训练图像描述符
	vector<KeyPoint> train_keypoint;
	Mat trainDescriptor;
	SurfFeatureDetector featureDetector(80);
	featureDetector.detect(trainImage_gray, train_keypoint);
	SurfDescriptorExtractor featreExtractor;
	featreExtractor.compute(trainImage_gray, train_keypoint, trainDescriptor);

	// 3. 创建基于FLANN的描述符匹配对象
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();

	// 4. 创建视频对象、定义帧率
	VideoCapture cap(0);
	unsigned int frameCount = 0;  // 帧数

	// 5. While
	while ((char)waitKey(1) != 'q')
	{
		// <1> 参数设置
		int64 time0 = getTickCount();
		Mat testImage, testImage_gray;
		cap >> testImage;  // 采集视频到testImage中
		if (testImage.empty())
			continue;
		
		// <2> 转化图像到灰度
		cvtColor(testImage, testImage_gray, CV_BGR2GRAY);

		// <3> 检测S关键点、提取测试图像描述符
		vector<KeyPoint> test_keypoint;
		Mat testDescriptor;
		featureDetector.detect(testImage_gray, test_keypoint);
		featreExtractor.compute(testImage_gray, test_keypoint, testDescriptor);

		// <4> 匹配训练和测试描述符
		vector<vector<DMatch> > matches;
		matcher.knnMatch(testDescriptor, matches, 2);

		// <5> 根据劳氏算法(Lowe's algorithm), 得到优秀的匹配点
		vector<DMatch> goodMatches;
		for (unsigned int i = 0; i < matches.size(); ++i)
		{
			if (matches[i][0].distance < 0.6 * matches[i][1].distance)
				goodMatches.push_back(matches[i][0]);
		}

		// <6> 绘制匹配点并显示
		Mat dstImage;
		drawMatches(testImage, test_keypoint, trainImage, train_keypoint, goodMatches, dstImage);
		imshow("Dst Image", dstImage);

		// <7> 输出帧率信息
		cout << "当前帧率为: " << getTickFrequency() / (getTickCount() - time0) << endl;
	}

	waitKey(0);
	return 0;
}