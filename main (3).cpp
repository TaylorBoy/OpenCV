#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;

int main()
{
	// �ı�console������ɫ
	system("color 6F");

	// 1. ��ʼ��
	FileStorage fs("test.yaml", FileStorage::READ);

	// 2.1 ����һ: ��FileNode����
	int frameCount = (int)fs["frameCount"];

	// 2.2 ������: ʹ��FileNode����� >>
	std::string date;
	fs["calibratoinDate"] >> date;

	Mat cameraMatrix, distCoeffs;
	fs["cameraMatrix"] >> cameraMatrix;
	fs["distCoeffs"] >> distCoeffs;

	cout << "frameCount: " << frameCount << endl;
	cout << "Calibration date: " << date << endl;
	cout << "cameraMatrix: " << cameraMatrix << endl;
	cout << "distCoeffs: " << distCoeffs << endl;


	// �ر��ļ�
	fs.release();

	waitKey(0);

	return 0;
}