#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
	�������˲�: ��ֵ�˲� \ ˫���˲�
	˫��  ԭ��: void bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT);
	@d: �ڹ��˹�����ÿ�����������ֱ��, ��dΪ������, ������sigmaSpace�����
	@sigmaColor: ��ɫ�ռ��˲�����sigmaֵ, ֵԽ��, ��������������Խ������ɫ�ᱻ���, �����ϴ�İ������ɫ����
	@sigmaSpace: ����ռ����˲�����sigmaֵ, ֵԽ��, ԽԶ�����ػ��໥Ӱ��. d>0 ����dΪ׼.
*/

int main()
{
	// Load image
	Mat image = imread("..\\..\\picture\\1.jpeg");

	// Create Window
	namedWindow("Src Image");
	namedWindow("Result");

	// ˫���˲�
	Mat out;
	bilateralFilter(image, out, 25, 25 * 2, 25 / 2);

	// Display
	imshow("Src Image", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}