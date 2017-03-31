/*
	<< �ߴ����: resize() >>
	void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpolation=INTER_LINEAR);
	@fx: ˮƽ������ϵ��, Ĭ��0ʱ, fx=(double)dsize.width/src.cols
	@fy: ��ֱ������ϵ��, Ĭ��0ʱ, fy=(double)dsize.height/src.rows
	@interpolation: ����, ָ����ֵ��ʽ
		0 INTER_NEAREST -- ����ڲ�ֵ
		1 INTER_LINEAR  -- ���Բ�ֵ(Ĭ��)
		2 INTER_CUBIC   -- ����������ֵ(����4x4���������ڵ�˫���β�ֵ)
		3 INTER_AREA	-- �����ֵ(�������������ϵ���ز�����ֵ)
		4 INTER_LANCZOS4   -- Lanczos��ֵ(����8x8���������Lanczos��ֵ)
		�� ��С: �Ƽ� CV_INTER_AREA
		�� �Ŵ�: �Ƽ� CV_INTER_LINEAR,  Ч�ʸ�, �ٶȿ�
				 ���Ƽ� CV_INTER_CUBIC, Ч�ʵ�, �ٶ���

*/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	// Load image
	Mat srcImage = imread("..\\..\\picture\\9.jpg");
	Mat tmpImage, dstImage1, dstImage2;
	tmpImage = srcImage; 

	// ���гߴ����
	resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0.0), (0.0), CV_INTER_AREA);
	resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0.0), (0.0), CV_INTER_LINEAR);

	// Display
	imshow("Src Image", srcImage);
	imshow("dstImage 1", dstImage1);
	imshow("dstImage 2", dstImage2);

	waitKey(0);

	return 0;
}