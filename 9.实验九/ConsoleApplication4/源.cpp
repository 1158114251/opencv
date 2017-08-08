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


#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <cv.h>
//using namespace std;
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//��ɫͼ���ֱ��ͼ���⻯
IplImage* TO_junhenghua(IplImage *pImage);
int main(int argc, char** argv)
{
	

	// ���ļ��м���ԭͼ
	IplImage *test = cvLoadImage("6013202130.jpg", CV_LOAD_IMAGE_UNCHANGED);
	IplImage *test_1 = TO_junhenghua(test);

	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("ֱ��ͼ���⻯��", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", test);
	cvShowImage("ֱ��ͼ���⻯��", test_1);


	cvWaitKey(0);

	cvDestroyWindow("ԭͼ");
	cvDestroyWindow("ֱ��ͼ���⻯��");
	cvReleaseImage(&test);
	cvReleaseImage(&test_1);
	return 0;
}

IplImage* TO_junhenghua(IplImage *pImage)
{
	IplImage *pEquaImage = cvCreateImage(cvGetSize(pImage), pImage->depth, 3);

	// ԭͼ��ֳɸ�ͨ�����پ��⻯,���ϲ�����ɫͼ���ֱ��ͼ���⻯
	const int MAX_CHANNEL = 4;
	IplImage *im_linshi[MAX_CHANNEL] = { NULL };

	int i;
	for (i = 0; i < pImage->nChannels; i++)
		im_linshi[i] = cvCreateImage(cvGetSize(pImage), pImage->depth, 1);

	cvSplit(pImage, im_linshi[0], im_linshi[1], im_linshi[2], im_linshi[3]);

	for (i = 0; i < pImage->nChannels; i++)
		cvEqualizeHist(im_linshi[i], im_linshi[i]);

	cvMerge(im_linshi[0], im_linshi[1], im_linshi[2], im_linshi[3], pEquaImage);

	for (i = 0; i < pImage->nChannels; i++)
		cvReleaseImage(&im_linshi[i]);

	return pEquaImage;
}