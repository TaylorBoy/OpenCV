#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/*------------ 多通道混合实现函数 -------------*/
bool MulitChannelBlengding(int channel);

///////////////////////////////////////////
int main()
{
	system("color 9F");

	if (MulitChannelBlengding(1))
	{
		cout << endl << "Run successfully! " << endl;
	}
//	saturate_cast<uchar>(8);
//	template inline uchar saturate_cast<uchar>(int v)          
//	{ return (uchar)((unsigned)v <= UCHAR_MAX ? v : v > 0 ? UCHAR_MAX : 0); }

	waitKey(0);
	return 0;
}


/*------------ 多通道混合实现函数 -------------*/
bool MulitChannelBlengding(int channel)
{
	// 参数设置, 以蓝色通道0为例
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat imageBlueChannel;

	// 1. Load image
	srcImage = imread("..\\..\\picture\\14.jpg");
	logoImage = imread("..\\..\\picture\\sound.jpg", 0);  // 注: 灰度, IMREAD_GRAYSCALSE
	if (!srcImage.data | !logoImage.data)  return false;

	// 2. 把3通道转为3个单通道
	split(srcImage, channels);  // 分离彩色通道

	// 3. 引用返回通道, 注: 引用返回 
	imageBlueChannel = channels.at(channel);  /* 在这里更改通道数channel即可 */

	// 4. 混合操作: src1与src2必须有相同尺寸和相同通道数
	addWeighted(imageBlueChannel(Rect(10, 10, logoImage.cols, logoImage.rows)), 1,
		logoImage, 0.5, 0.0, imageBlueChannel(Rect(10, 10, logoImage.cols, logoImage.rows)));

	// 5. 重新合并三个通道
	merge(channels, srcImage);

	// 6. 显示效果图
	imshow("<1>蓝色通道", srcImage);

	return true;
}