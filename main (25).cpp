#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImg = imread("..\\1.jpg");

	if (!srcImg.empty())
		imshow("[ԭͼ]", srcImg);

	// ���о�ֵ�˲�����
	Mat dstImage;
	blur(srcImg, dstImage, Size(7, 7)); // blur: ʹģ������,��ģ��

	imshow("[Ч��ͼ]", dstImage);

	waitKey(0);

	return 0;
}