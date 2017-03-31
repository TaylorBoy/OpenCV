#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  // OpenCV ͼ����ͷ�ļ�
using namespace cv;

int main()
{
	// ����ԭͼ
	Mat srcImage = imread("..\\1.jpg");
	// ��ʾԭͼ
	if (!srcImage.empty())
		imshow("SRC_photo", srcImage);
	
	// ���и�ʴ����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat desImage;
	erode(srcImage, desImage, element);  // erode: ��ʴ

	// ��ʾЧ��ͼ
	imshow("DES_photo", desImage);



	waitKey(0);

	return 0;

}