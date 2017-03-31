#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*------------ ��ɫ�ռ��������� -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div);

/////////////////////////////////////////////
int main(int argc, char** argv)
{
	// 1. ����ԭͼ
	Mat srcImage = imread("..\\..\\picture\\11.jpg");
	imshow("srcImage", srcImage);

	// 2. ��ԭͼ������񴴽�Ч��ͼ
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());  // ��С ���� 

	// 3. ��¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());

	// 4. ������ɫ�ռ���������
	colorReduce(srcImage, dstImage, 32);

	// 5. ��������ʱ�����
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "Run Time: " << time0 << "seconds" << endl;

	// 6. ��ʾЧ��ͼ
	imshow("dstImage", dstImage);

	waitKey(0);

	return 0;
}

#if (0)
/*------------- (1)ָ��������� -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// ����׼��
	outputImage = inputImage.clone();   // ����ʵ�ε���ʱ����
	int rowNumber = outputImage.rows;	// ����
	int colNumber = outputImage.cols * outputImage.channels();   // ����xͨ���� = ÿ��Ԫ�صĸ���

	// ˫��ѭ��, �������е�����ֵ
	for (int i = 0; i < rowNumber; ++i)
	{
		uchar* data = outputImage.ptr<uchar>(i);  // ��ȡ��i�е��׵�ַ, ptr: ����ģ��
		for (int j = 0; j < colNumber; ++j)
		{
			// ����ÿ������
			// data[j] = data[j] / div * div + div / 2;
			*data++ = *data / div * div + div / 2;
		}
	}
}
#endif

#if (0)
/*------------- (2)�������������� -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// ����׼��
	outputImage = inputImage.clone();
	// ��ȡ������
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();   // typedef Vec<uchar, 3> Vec3b;
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();

	// ��ȡ��ɫͼ������
	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}
#endif

#if (1)
/*------------- (3)��̬��ַ����������� -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// ����׼��
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;

	// ��ȡ��ɫͼ������
	for (int i = 0; i < rowNumber; ++i)
	{
		for (int j = 0; j < colNumber; ++j)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  // Blue
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  // Green
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  // Red
		}
	}
}
#endif

