// ��SURF���йؼ��������������ȡ, Ȼ����FLANN����ƥ��

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace std;
using namespace cv;

int main()
{
	system("color 6F");

	// 1. ����ͼ��, תΪ�Ҷ�ͼ
	Mat trainImage = imread("1.jpg"), trainImage_gray;
	if (!trainImage.data) return -1;
	imshow("Src Image", trainImage);
	cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);

	// 2. ���Surf�ؼ��㡢��ȡѵ��ͼ��������
	vector<KeyPoint> train_keypoint;
	Mat trainDescriptor;
	SurfFeatureDetector featureDetector(80);
	featureDetector.detect(trainImage_gray, train_keypoint);
	SurfDescriptorExtractor featreExtractor;
	featreExtractor.compute(trainImage_gray, train_keypoint, trainDescriptor);

	// 3. ��������FLANN��������ƥ�����
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();

	// 4. ������Ƶ���󡢶���֡��
	VideoCapture cap(0);
	unsigned int frameCount = 0;  // ֡��

	// 5. While
	while ((char)waitKey(1) != 'q')
	{
		// <1> ��������
		int64 time0 = getTickCount();
		Mat testImage, testImage_gray;
		cap >> testImage;  // �ɼ���Ƶ��testImage��
		if (testImage.empty())
			continue;
		
		// <2> ת��ͼ�񵽻Ҷ�
		cvtColor(testImage, testImage_gray, CV_BGR2GRAY);

		// <3> ���S�ؼ��㡢��ȡ����ͼ��������
		vector<KeyPoint> test_keypoint;
		Mat testDescriptor;
		featureDetector.detect(testImage_gray, test_keypoint);
		featreExtractor.compute(testImage_gray, test_keypoint, testDescriptor);

		// <4> ƥ��ѵ���Ͳ���������
		vector<vector<DMatch> > matches;
		matcher.knnMatch(testDescriptor, matches, 2);

		// <5> ���������㷨(Lowe's algorithm), �õ������ƥ���
		vector<DMatch> goodMatches;
		for (unsigned int i = 0; i < matches.size(); ++i)
		{
			if (matches[i][0].distance < 0.6 * matches[i][1].distance)
				goodMatches.push_back(matches[i][0]);
		}

		// <6> ����ƥ��㲢��ʾ
		Mat dstImage;
		drawMatches(testImage, test_keypoint, trainImage, train_keypoint, goodMatches, dstImage);
		imshow("Dst Image", dstImage);

		// <7> ���֡����Ϣ
		cout << "��ǰ֡��Ϊ: " << getTickFrequency() / (getTickCount() - time0) << endl;
	}

	waitKey(0);
	return 0;
}