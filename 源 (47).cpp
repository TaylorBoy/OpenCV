#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/*
	��ֵ�˲�: blur()
	ԭ��: void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT);
	@ksize: ���Ĵ�С
	@anchor: ê��

	== ��һ����ķ����˲�: boxFilter(src, dst, depth, Size(w, h), anchor, TRUE, border);
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
	//boxFilter(image, out, -1, Size(5, 5));
	blur(image, out, Size(8, 8));

	// Display
	imshow("SrcImage", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}