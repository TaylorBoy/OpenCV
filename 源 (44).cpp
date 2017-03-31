#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
	�������˲�: ��ֵ�˲� \ ˫���˲�
	��ֵ  ԭ��: void medianBlur(InputArray src, OutputArray dst, int ksize);
	@ksize: �׾������Գߴ�, ����ȡ����1������(3, 5, 7, ...)
	����˼��: �����ص�����Ҷ�ֵ����ֵ����������ص�ĻҶ�ֵ. ʱ�� = 5 * ��ֵ
*/

int main()
{
	Mat image = imread("..//..//picture//1.jpeg");
	if ( !image.data ) return -1;
	imshow("SrcImage", image);

	Mat out;
	
	// ��ֵ�˲�
	medianBlur(image, out, 5);

	imshow("Output", out);

	waitKey(0);

	return 0;
}