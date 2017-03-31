/*
	Scharr�˲���: ��Ҫ���Sobel������������ڵ�.
	void Scharr(
		InputArray src,  // Դͼ
		OutputArray dst, // Ŀ��ͼ
		int ddepth,      // ͼ�����
		int dx,          // x�����ϵĲ�ֽ���
		int dy,          // y�����ϵĲ�ֽ���
		double scale=1,  // ��������
		double delta=0,  // deltaֵ
		int borderType=BORDER_DEFAULT // �߽�ģʽ
	)
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 0. ����grad_x��grad_y����
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	// 1. Load Image
	Mat src = imread("..\\..\\picture\\16.jpg");
	imshow("Src Image", src);

	// 2.1 ��x�����ݶ�
	Scharr(src, grad_x, CV_16S, 1, 0, 1, 0);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X Scharr", abs_grad_x);

	// 2.2 ��y�����ݶ�
	Scharr(src, grad_y, CV_16S, 0, 1, 1, 0);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y Scharr", abs_grad_y);

	// 3. �ϲ��ݶ�(����)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	// Display
	imshow("Scharr", dst);

	waitKey(0);

	return 0;
}