#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/*
	�����˲�: boxFilter()
	ԭ��: void boxFilter(InputArray src, OutputArray dst, int ddepth, Size ksize, Point anchor=Point(-1,-1), bool normalize=true, int borderType=BORDER_DEFAULT);
	@ddepth: ����ͼ�����, -1��ʾʹ��ԭͼ���src.depth()
	@ksize: �ں˴�С, Size(width, height)
	@anchor: ê��--ƽ����, Ĭ��ֵ��ʾ�˵�����
	@normalize: �Ƿ��������һ��, 

	��ֵ�˲� = ��һ���� �����˲�.
*/

int main()
{
	// Load image
	Mat image = imread("..\\..\\picture\\1.jpeg");

	// ��������
	namedWindow("SrcImage");
	namedWindow("Result");

	// �˲�
	Mat out;
	boxFilter(image, out, -1, Size(6, 6));

	// Display
	imshow("SrcImage", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}