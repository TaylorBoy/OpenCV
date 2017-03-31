/*
	����: warpAffine(), һ�����Ա任 + һ��ƽ��.(* һ������ + һ������)
	ԭ��: void warpAffine(InputArray src, OutputArray dst, InputArray M, Size dsize; int flags=INTER_LINEAR, int borderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())
	@param M : 2x3�ı任����
	@param dsize : ���ͼ��ĳߴ�
	@param flags : ��ֵ��ʽ

	�����ά��ת�任����: getRotationMatrix2D()
	ԭ��: void getRatationMatrix2D(Point2f center, double angle, double scale);
	@param center : ��ת����
	@param angle  : ��ת�Ƕ�, ��ʱ��Ϊ��
	@param scale  : ����ϵ��
*/

//------------------ ͷ�ļ� ---------------------
#include <opencv2/highgui/highgui.hpp>	
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//------------------ �궨�� ---------------------
#define WINDOW_NAME1 "ԭʼͼ����"
#define WINDOW_NAME2 "����Warp���ͼ��"
#define WINDOW_NAME3 "����Warp��Rotate���ͼ��"

//------------------ ������ ---------------------
int main()
{
	system("color 1A");

	// 1. ����׼��
	
	// 1.1 ���������, ��������������
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	
	// 1.2 ����Mat����
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	// 2. Load src image
	srcImage = imread("..\\..\\picture\\9.jpg");
	if (!srcImage.data) return -1;

	//    ����Ŀ��ͼ��Ĵ�С��������ԭͼ��һֱ
	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	// 3. ����ԭͼ���Ŀ��ͼ���ϵ�������Լ������任
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols * 0.0), static_cast<float>(srcImage.rows * 0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols * 0.65), static_cast<float>(srcImage.rows * 0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols * 0.15), static_cast<float>(srcImage.rows * 0.6));

	// 4. ��÷���任
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	// 5. ��Դͼ��Ӧ�øյõ��ķ���任warpMat
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

	// 6.  ��ͼ���������, ����ת
	// 6.1 ������ͼ���е�˳ʱ����ת50����������Ϊ0.6����ת����
	Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
	double angle = -30.0;
	double scale = 0.8;
	// 6.2 ����ת����
	rotMat = getRotationMatrix2D(center, angle, scale);
	// 6.3 ��ת�����ŵ�ͼ��
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());

	// Display
	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, dstImage_warp);
	imshow(WINDOW_NAME3, dstImage_warp_rotate);

	waitKey(0);

	return 0;
}

//---------------------------------------