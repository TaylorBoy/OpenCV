#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/*------------ ��ͨ�����ʵ�ֺ��� -------------*/
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


/*------------ ��ͨ�����ʵ�ֺ��� -------------*/
bool MulitChannelBlengding(int channel)
{
	// ��������, ����ɫͨ��0Ϊ��
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat imageBlueChannel;

	// 1. Load image
	srcImage = imread("..\\..\\picture\\14.jpg");
	logoImage = imread("..\\..\\picture\\sound.jpg", 0);  // ע: �Ҷ�, IMREAD_GRAYSCALSE
	if (!srcImage.data | !logoImage.data)  return false;

	// 2. ��3ͨ��תΪ3����ͨ��
	split(srcImage, channels);  // �����ɫͨ��

	// 3. ���÷���ͨ��, ע: ���÷��� 
	imageBlueChannel = channels.at(channel);  /* ���������ͨ����channel���� */

	// 4. ��ϲ���: src1��src2��������ͬ�ߴ����ͬͨ����
	addWeighted(imageBlueChannel(Rect(10, 10, logoImage.cols, logoImage.rows)), 1,
		logoImage, 0.5, 0.0, imageBlueChannel(Rect(10, 10, logoImage.cols, logoImage.rows)));

	// 5. ���ºϲ�����ͨ��
	merge(channels, srcImage);

	// 6. ��ʾЧ��ͼ
	imshow("<1>��ɫͨ��", srcImage);

	return true;
}