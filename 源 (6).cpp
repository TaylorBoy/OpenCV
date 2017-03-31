/*
	1. ���ƹؼ���: drawKeyPoints()
	      void drawKeyPoints(
	          const Mat& images,                    // ����ͼ��
			  const vector<KeyPoint>& keypoints,    // �����������
			  Mat& outImage,                        // ���ͼ��, ȡ���ڵ��������flags
			  const Scalar& color=Scalar::all(-1),  // �ؼ�����ɫ
			  int flags=DrawMatchesFlags::DEFAULT   // ���ƹؼ����������ʶ��
	          );

	   ������ʶ��:
	          struct DrawMatchesFlags{
			      enum{
				      DEFAULT = 0,                  // �����������(ʹ��Mat::create()). ʹ���ִ�����ͼ�����ƥ��Ժ�������, ��ÿһ���ؼ���, ֻ�����м��
					  DRAW_OVER_OUTIMG = 1,         // ���������ͼ�����, ���������ͼ���ϻ���ƥ���
					  ONT_DRAW_SINGLE_POINTS = 2,   // ���������㲻������
					  DRAW_RICH_KEYPOINTS = 4       // ��ÿһ���ؼ���, ���ƴ���С�ͷ���Ĺؼ�ԲȦ
				  };
			  };

	2. KeyPoint��:
	          class KeyPoint{
			      Point2f pt;        // ����
				  float size;        // ����������ֱ��
				  float angle;       // ������ķ���, ֵΪ(0, 360), ������ʾ��ʹ��
				  float response;    
				  int octave;        // ���������ڵ�ͼ�����������
				  int class_id;      // ���ھ����id
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

	// ������Ҫ�õ��ı�������
	int minHessian = 400;   // ����SURF�е�Hessian��ֵ������������
	SurfFeatureDetector detector(minHessian);  // ����һ��SURF����������
	std::vector<KeyPoint> keypoint_1, keypoint_2;  // vectorģ�������ܹ�����������͵Ķ�̬����, �ܹ����Ӻ�ѹ������

	// ����detect��������SURF�����ؼ���, ������vector��
	// CV_WRAP void detect(const Mat& image, CV_OUT vector<KeyPoint>& keypoints, const Mat& mask=Mat()) const;
	// void detect(const vector<Mat>& image, vector<vector<KeyPoint> >& keypoints, const vector<Mat> mask=vector<Mat>())const;
	detector.detect(srcImage1, keypoint_1);
	detector.detect(srcImage2, keypoint_2);

	// ���ƹؼ���
	Mat img_keypoint_1; Mat img_keypoint_2;
	drawKeypoints(srcImage1, keypoint_1, img_keypoint_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcImage2, keypoint_2, img_keypoint_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	// Display
	imshow("��������Ч��1", img_keypoint_1);
	imshow("��������Ч��2", img_keypoint_2);

	waitKey(0);

	return 0;
}

