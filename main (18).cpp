#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void createAlphaMat(Mat &mat)
{
	for (int i = 0; i < mat.rows; ++i)
	{
		for (int j = 0; j < mat.cols; ++j)
		{
			Vec4b&rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j))) / ((float(mat.cols) * UCHAR_MAX));
			rgba[2] = saturate_cast<uchar>((float(mat.rows - i))) / ((float(mat.rows) * UCHAR_MAX));
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}


int main()
{
	// ������alphaͨ����Mat
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	vector<int> compression_params;
	// OpenCV3
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try{
		// bool imwrite(const string% filename, InputArray img, const vector<int>& params=vector<int>());
		// 1. ����JPEG��ʽ, params��ʾ0-100��ͼƬ����, Ĭ��Ϊ95
		// 2. ����PNG��ʽ, params��ʾ0-9��ѹ������, Ĭ��Ϊ3
		// 3. ����ppm,pgm,pbm, params��ʾ0��1�Ķ����Ƹ�ʽ��־, Ĭ��Ϊ1
		imwrite("͸��Alphaֵͼ.png", mat, compression_params);
		imshow("���ɵ�ͼ", mat);
		fprintf(stdout, "ͼƬ���ݱ������~~");
		waitKey(0);
	}
	catch (runtime_error& ex){
		fprintf(stderr, "ͼƬ���ݱ���ʧ��: %s", ex.what());
		return 1;
	}

	return 0;
}