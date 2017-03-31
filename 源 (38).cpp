#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*
	���ϲ���: pyrUp()
	void pyrUp(InputArray src, OutputArray dst, const Size& dstsize=Size(), int borderType=BORDER_DEFAULT);
		@dstsize: ���ͼ���С, Ĭ�������=(src.cols * 2, src.rows * 2)

	���²���: pyrDown()
	void pyrDown(InputArray src, OutputArray dst, const Size& dstsize=Size(), int borderType=BORDER_DEFAULT);
		@dstsize: ���ͼ���С, Ĭ�������=((src.cols+1) / 2, (src.rows+1) / 2)
*/

int main()
{
	//Load image
	Mat srcImage = imread("..\\..\\picture\\9.jpg");

	Mat tmpImage, dstImage;
	tmpImage = srcImage;

	// ���ϲ���
	pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));

	// Display
	imshow("SrcImage", srcImage);
	imshow("dstImage Up", dstImage);

	// ���²���
	pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));

	imshow("dstImage Down", dstImage);

	waitKey(0);

	return 0;
}