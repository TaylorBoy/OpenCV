#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace std;
using namespace cv;

int main()
{
	// ����ԭͼ, ��ת��Ϊ�Ҷ�
	Mat srcImage = imread("1.jpg");
	if (!srcImage.data) return -1;
	imshow("ԭͼ", srcImage);
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//--------------- ���SIFT�����㲢��ͼ������ȡ����������� --------------

	// 1. ��������
	OrbFeatureDetector featureDetector;
	vector<KeyPoint> keyPoints;
	Mat descriptors;

	// 2. ����detect()���������ؼ���, ������vector������
	featureDetector.detect(grayImage, keyPoints);

	// 3. ����������(��������)
	OrbDescriptorExtractor featureExtractor;
	featureExtractor.compute(grayImage, keyPoints, descriptors);

	// 4. ����FLANN������������ƥ��
	flann::Index flannIndex(descriptors, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);

	// 5. ��ʼ����Ƶ�ɼ�����
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 360);    // ��Ƶ�ɼ����
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 900);   // ��Ƶ�ɼ��߶�

	unsigned int frameCount = 0;   // ֡��

	while (true)
	{
		double time0 = static_cast<double>(getTickCount());
		Mat captureImage, captureImage_gray;

		cap >> captureImage;	// �ɼ���Ƶ
		if (captureImage.empty()) continue;

		cvtColor(captureImage, captureImage_gray, CV_BGR2GRAY);

		// 7. ���SIFT�ؼ��㲢��ȡ����ͼ�е�������
		vector <KeyPoint> captureKeyPoints;
		Mat captureDescription;

		// 8. ����detect�������������ؼ���, ���浽vector������
		featureDetector.detect(captureImage_gray, captureKeyPoints);

		// 9. ����������
		featureExtractor.compute(captureImage_gray, captureKeyPoints, captureDescription);

		// 10. ƥ��Ͳ���������, ��ȡ�������ڽ���������
		Mat matchIndex(captureDescription.rows, 2, CV_32SC1);
		Mat matchDistance(captureDescription.rows, 2, CV_32FC1);
		flannIndex.knnSearch(captureDescription, matchIndex, matchDistance, 2, flann::SearchParams());  // ����K�ڽ��㷨

		// 11. ���������㷨ѡ������ƥ��
		vector<DMatch> goodMatches;
		for (int i = 0; i < matchDistance.rows; ++i)
		{
			if (matchDistance.at<float>(i, 0) < 0.6 * matchDistance.at<float>(i, 1))
			{
				DMatch dmatches(i, matchIndex.at<int>(i, 0), matchDistance.at<float>(i, 0));
				goodMatches.push_back(dmatches);
			}
		}

		// 12. ���Ʋ���ʾƥ�䴰��
		Mat resultImage;
		drawMatches(captureImage, captureKeyPoints, srcImage, keyPoints, goodMatches, resultImage);
		imshow("ƥ�䴰��", resultImage);

		// 13. ��ʾ֡��
		cout << ">֡�� = " << getTickFrequency() / (getTickCount() - time0) << endl;

		// �����˳�
		if ((char)waitKey(1) == 27) break;
	}



	return 0;
}