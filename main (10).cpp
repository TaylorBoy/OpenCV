#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/*------------ 颜色空间缩减函数 -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div);

/////////////////////////////////////////////
int main(int argc, char** argv)
{
	// 1. 载入原图
	Mat srcImage = imread("..\\..\\picture\\11.jpg");
	imshow("srcImage", srcImage);

	// 2. 按原图参数规格创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());  // 大小 类型 

	// 3. 记录起始时间
	double time0 = static_cast<double>(getTickCount());

	// 4. 调用颜色空间缩减函数
	colorReduce(srcImage, dstImage, 32);

	// 5. 计算运行时间输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "Run Time: " << time0 << "seconds" << endl;

	// 6. 显示效果图
	imshow("dstImage", dstImage);

	waitKey(0);

	return 0;
}

#if (0)
/*------------- (1)指针访问像素 -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// 参数准备
	outputImage = inputImage.clone();   // 复制实参到临时变量
	int rowNumber = outputImage.rows;	// 行数
	int colNumber = outputImage.cols * outputImage.channels();   // 列数x通道数 = 每行元素的个数

	// 双重循环, 遍历所有的像素值
	for (int i = 0; i < rowNumber; ++i)
	{
		uchar* data = outputImage.ptr<uchar>(i);  // 获取第i行的首地址, ptr: 函数模板
		for (int j = 0; j < colNumber; ++j)
		{
			// 处理每个像素
			// data[j] = data[j] / div * div + div / 2;
			*data++ = *data / div * div + div / 2;
		}
	}
}
#endif

#if (0)
/*------------- (2)迭代器访问像素 -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// 参数准备
	outputImage = inputImage.clone();
	// 获取迭代器
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();   // typedef Vec<uchar, 3> Vec3b;
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();

	// 存取彩色图像像素
	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}
#endif

#if (1)
/*------------- (3)动态地址计算访问像素 -------------*/
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	// 参数准备
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;

	// 存取彩色图像像素
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

