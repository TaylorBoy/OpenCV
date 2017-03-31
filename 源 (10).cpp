/*
	����ͶӰ: calcBackProject()
	void calcBackProject(
		const Mat* images,       // ���ΪCV_8U/CV_32F
		int nimages,             // �����������
		const int* channels,     // ͨ����
		InputArray hist,         // �����ֱ��ͼ
		OutputArray backProject, // �������ͶӰ����
		const float** ranges,    // ÿһά�������ȡֵ��Χ
		double scale=1,          // ��������
		bool uniform=true        // �Ƿ����
	);

	ͨ������: mixChannels()
	void mixChannels(
		const Mat* src,          // ��������
		size_t nsrcs,            // ��������src�ľ�����
		Mat* dst,                // �������
		size_t ndsts,            // �������dst�ľ�����
		const int* fromTo,       // ��ָ����ͨ�����и��Ƶ���������
		size_t npairs            // ��5������fromTo��������
	);

	void mixChannels(
		const vector<Mat>& src,
		vector<Mat>& dst,
		const int* fromTo,
		size_t npairs
	);
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>	
#include <iostream>
using namespace cv;

#define WINDOW_NAME "SRC IMAGE"

Mat g_srcImage, g_hsvImage, g_hueImage;
int g_bins = 30;  // ֱ��ͼ���

void on_BinChange(int, void *);

int main()
{
	// 1. ��ȡԭͼ, ��ת����HSV�ռ�
	g_srcImage = imread("..\\..\\picture\\32.jpg");
	if (!g_srcImage.data) return -1;

	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);
	9
	// 2. ����hueɫ��ͨ��
	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0, 0 };
	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	// 3. �齱Trackbar������bin����Ŀ
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("ɫ�����", WINDOW_NAME, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);

	// 4. ��ʾЧ��ͼ
	imshow(WINDOW_NAME, g_srcImage);

	while ((char)waitKey(0) != 'q'){}

	waitKey(0);

	return 0;
}

void on_BinChange(int, void *)
{
	// 1. ����׼��
	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	// 2. ����ֱ��ͼ����һ��
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	// 3. ���㷴��ͶӰ
	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	// 4. ��ʾ����ͶӰ
	imshow("Back Project", backproj);

	// 5. ����ֱ��ͼ����׼��
	int w = 400, h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	// 6. ����ֱ��ͼ
	for (int i = 0; i < g_bins; ++i)
	{
		rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)), Scalar(100, 123, 255), -1);
	}

	// 7. ��ʾֱ��ͼ
	imshow("ֱ��ͼ", histImg);
}

