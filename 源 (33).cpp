/*
	������˹�任: Laplacian(), ��Ҫ����Sobel����
	����ԭ��: void Laplacian(InputArray src, OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT);
	          @ddepth: Ŀ��ͼƬ�����
			  @ksize : ���ڼ�����׵����˲����Ŀռ�ߴ�, ��С����Ϊ������
			  @scale : ����������˹�Ŀ�ѡ��������
			  @delta : ��ʾ�ڽ������Ŀ��dst֮ǰ�Ŀ�ѡdeltaֵ
	Note: ��һ��ͼ��ȥ����Laplacian���ӿ���ǿ�Աȶ�.
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// 0. ��������
	Mat src, src_gray, dst, abs_dst;

	// 1. Load Image
	src = imread("..\\..\\picture\\12.jpg");
	imshow("Src Image", src);

	// 2. ʹ�ø�˹�˲���������
	GaussianBlur(src, src, Size(3, 3), 0, 0);

	// 3. ת��Ϊ�Ҷ�ͼ
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	// 4. ʹ��Laplacian()
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0);

	// 5. �������ֵ, �������ת��Ϊ8λ
	convertScaleAbs(dst, abs_dst);

	// 6. ��ʾ���
	imshow("Laplacian", abs_dst);

	waitKey(0);

	return 0;
}