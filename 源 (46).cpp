#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

/*
	��˹ģ��: GaussianBlur()
	ԭ��: void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
	@sigmaY = 0, �� sigmaY = sigmaX. ��ʾ��˹�˺�����X/Y�����ϵı�׼ƫ��
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
	// boxFilter(image, out, -1, Size(5, 5));
	// blur(image, out, Size(7, 7));
	GaussianBlur(image, out, Size(6, 9), 0, 0);  // Size��������Ϊ����!
	/*OpenCV : (ksize.width > 0 && ksize.width % 2 == 1 && 
				ksize.height > 0 && ksize.height % 2 == 1) 
	in cv::createGaussianKernels */

	// Display
	imshow("SrcImage", image);
	imshow("Result", out);


	waitKey(0);

	return 0;
}