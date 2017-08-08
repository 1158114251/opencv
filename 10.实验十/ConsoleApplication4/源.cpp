/**********************************************************************************************************
 *  opencv ѧϰ �� 2016��3��15��20:10:06

1. ͼ�����뺯��
����cvLoadImage����ָ��ͼ���ļ���������ָ����ļ���IplImageָ�롣����֧��bmp��jpg�� png�� tiff�ȸ�ʽ��ͼ���亯��ԭ�����£�
IplImage* cvLoadImage( const char* filename, int iscolor);
���У�filename �Ǵ�����ͼ������ƣ�����ͼ�����չ����iscolor��һ�������������ѡ��������͸�������ֵ��������ʾ��Ϊ��ͨ��ͼ�����룬���ʾ��ͼ����Ϊ��ͨ��ͼ�񣬸�����ʾ����ͼ���ͨ������ͼ���ļ����������
2. ���ڶ��庯��
����cvNamedWindow����һ�����ڣ�������ʾͼ���亯��ԭ�����£�
int cvNamedWindow( const char* name, unsigned long flags );
���У�name�Ǵ�������flags�Ǵ�������ָ��ֵ������ѡ��CV_WINDOW_AUTOSIZE��0����ֵ��CV_WINDOW_AUTOSIZE��ʾ���ڳߴ���ͼ��ԭʼ�ߴ���ͬ��0��ʾ�Թ̶��Ĵ��ڳߴ���ʾͼ��
3. ͼ����ʾ����
����cvShowImage����ָ���Ĵ�������ʾͼ���亯��ԭ�����£�
void cvShowImage( const char* name, const CvArr* image );
���У�name�Ǵ������ƣ�image��ͼ������ָ�룬һ����IplImageָ�롣
4. ͼ�񱣴溯��
����cvSaveImage��ָ�����ļ�������IplImage���͵�ָ��������亯��ԭ�����£�
int cvSaveImage( const char* filename, const CvArr* image );
���У�filename��ͼ�񱣴�·�������ƣ�image��IplImageָ�������
5. ͼ�����ٺ���
����cvReleaseImage�����Ѷ����IplImageָ��������ͷ�ռ���ڴ�ռ䡣�亯��ԭ�����£�
void cvReleaseImage( IplImage** image );
���У�imageΪ�Ѷ����IplImageָ�롣
6. ͼ��ת������
cvGetImage( const CvArr* arr, IplImage* image_header )
7.����һ�����ڡ�
void cvDestroyWindow( const char* name );
 ***********************************************************************************************************/


#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat g_srcImage;     // ȫ�ֵ�Դͼ��
// �ֱ��Ӧȫ�ֵķ����˲�����ֵ�˲�����˹�˲�����ֵ�˲���˫���˲������ͼ���Լ��ں�ֵ/����ֵ
Mat g_dstImgBox, g_dstImgBlur, g_dstImgGaussian, g_dstImgMedian, g_dstImgBilateral;
int g_BoxFilterVal = 5;
int g_BlurVal = 12;
int g_GaussianBlurVal = 5;
int g_MedianBlurVal = 12;
int g_BilateralFilterVal = 12;

static void on_BoxFilter(int, void *);
static void on_Blur(int, void *);
static void on_GaussianBlur(int, void *);
static void on_MedianBlur(int, void *);
static void on_BilateralFilter(int, void*);

int main()
{
	// ��ȡͼ��g_srcImage
	g_srcImage = imread("6013202130.jpg");
	if (!g_srcImage.data) {
		printf("��ȡ��ͼƬ�����ڡ��� \n");
		return false;
	}

	// �ֱ��¡ԭͼ��5���˲������ͼ���У���ΪMat����
	g_dstImgBox = g_srcImage.clone();
	g_dstImgBlur = g_srcImage.clone();
	g_dstImgGaussian = g_srcImage.clone();
	g_dstImgMedian = g_srcImage.clone();
	g_dstImgBilateral = g_srcImage.clone();

	// ��ʾԭͼ
	namedWindow("��ԭͼ��", 1);
	imshow("��ԭͼ��", g_srcImage);

	
	namedWindow("����ֵ�˲���", 1);
	createTrackbar("�ں�ֵ", "����ֵ�˲���", &g_BlurVal, 30, on_Blur);
	on_Blur(g_BlurVal, 0);

	namedWindow("����˹�˲���", 1);
	createTrackbar("�ں�ֵ", "����˹�˲���", &g_GaussianBlurVal, 30, on_GaussianBlur);
	on_GaussianBlur(g_GaussianBlurVal, 0);

	namedWindow("����ֵ�˲���", 1);
	createTrackbar("�ں�ֵ", "����ֵ�˲���", &g_MedianBlurVal, 30, on_MedianBlur);
	on_MedianBlur(g_MedianBlurVal, 0);

	

	cout << "���¡�q����ʱ�������˳�����\n";
	while (char(waitKey(1)) != 'q') {}

	return 0;
}



static void on_Blur(int, void *)
{
	blur(g_srcImage, g_dstImgBlur, Size(g_BlurVal + 1, g_BlurVal + 1),
		Point(-1, -1));
	imshow("����ֵ�˲���", g_dstImgBlur);
}

static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_dstImgGaussian, Size(g_GaussianBlurVal * 2 + 1,
		g_GaussianBlurVal * 2 + 1), 0, 0);
	imshow("����˹�˲���", g_dstImgGaussian);
}

static void on_MedianBlur(int, void *)
{
	medianBlur(g_srcImage, g_dstImgMedian, g_MedianBlurVal * 2 + 1);
	imshow("����ֵ�˲���", g_dstImgMedian);
}

