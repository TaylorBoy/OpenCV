#include <opencv2/opencv.hpp>
#include <String>
using namespace cv;
// ROI: region of interest ����Ȥ������

int main()
{
	std::string mp4 = "F:\\ɵ����\\QT\\01\\QT0718\\1.����.wmv";

	// ��ȡ��Ƶ�ļ�
	VideoCapture capture;	// capture: ����
	// VideoCapture capture("��Ƶ��ַ"); ��Ƶ��ַΪ0���������ͷ
	
	capture.open(0);

	while (1)
	{
		Mat frame;	// ����һ��Mat����, ���ڴ洢ÿһ֡ͼ��
		capture >> frame;
		imshow("001�Һ�Python�ĵ�һ�����ܽӴ�.mp4", frame);
		if (27 == waitKey(30))	// 30ms
			break;
	}


	waitKey(0);

	return 0;
}