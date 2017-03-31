/*
	Sobel����: ��ϸ�˹ƽ����΢����, ��������ͼ��ĻҶȺ����ͽ����ݶ�
	���� ԭ��: void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3,
			              double scale=1, double delta=0, int borderType=BORDER_DEFAULT);
			   @ddept: ���ͼ�����
			   @dx,dy: x/y�����ϵĲ�ֽ���
			   @ksize: Sobel�˵Ĵ�С(1, 3, 5, 7)
			   @scale: ���㵹��ʱ�Ŀ�ѡ����
			   @delta: �������dst֮ǰ�Ŀ�ѡ��deltaֵ
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 1. ����grad_x��grad_y����
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	//  2. Load image
	Mat src = imread("..\\..\\picture\\19.jpg");
	if (!src.data) return -1;
	imshow("Src Image", src);

	// 3.��X�����ݶ�
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X�����Sobel", abs_grad_x);

	// 4. ��Y�����ݶ�
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y�����Sobel", abs_grad_y);

	// 5. �ϲ��ݶ�(����)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	imshow("���巽���Sobel", dst);

	waitKey(0);

	return (0);
}