/*
	����Բ�任: HuoghCircles()
	����: ����Ҫ��ֵͼ��.
	����ԭ��: void HoughCircles(InputArray image, OutputArray circles, int method, double dp, 
	               double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0);
			  @image   : 8λ �Ҷ� ��ͨ��
	          @circles : Բ�����ʸ��, ÿ��ʸ������3������ʸ��(x,y,radius)
			  @method  : ��ⷽ��, HOUGH_GADIENT (OpenCV2: CV_HOUGH_GRADIENT)
			  @dp      : ���Բ�ĵ��ۼ���ͼ��ķֱ���������ͼ��֮�ȵĵ���, ������һ��������ͼ��ֱ��ʵ͵��ۼ���
			  @minDist : Բ��Բ��֮�����С����, �����ֲ�ͬԲ֮�����С����
			  @param1  : method���ü�ⷽ����Ӧ�Ĳ���(���ݸ�Canny�ĸ���ֵ, ����ֵΪ����ֵ��һ��)
			  @param2  : method��Ӧ����, ��ʾ�ڼ��׶�Բ�ĵ��ۼ�����ֵ. Ӱ��Բ�ļ��, ԽСԽ�ܼ�����Բ, Խ��Բ���ӽ�����Բ��
			  @minRadius : ��С�뾶 
			  @maxRadius : ���뾶
*/

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	// Load image
	Mat srcImage = imread("..\\..\\picture\\24.jpg");
	Mat midImage, dstImage;

	srcImage.copyTo(dstImage);
	dstImage = Scalar::all(0);

	imshow("Src Image", srcImage);

	// ת�Ҷ�ͼ �� ͼ��ƽ��
	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);

	imshow("mid Image", midImage);

	// ���л���Բ�任
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 100, 10, 0, 10);

	cout << "Circles' size is : " << circles.size() << endl;

	// ���λ���
	for (size_t i = 0; i < circles.size(); ++i)
	{
		// Բ��
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		// �뾶
		int radius = cvRound(circles[i][2]);
		// ����Բ��
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����
		circle(srcImage, center, radius, Scalar(155, 20, 255), 3, 8, 0);
		//cout << "i = " << i << endl;
	}

	imshow("Dst Image", srcImage);

	waitKey(0);

	return 0;
}