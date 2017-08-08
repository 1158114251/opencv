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


#include <cv.h>
#include <highgui.h> //ͼ����Ƶ���/����ͷ�ļ�
using namespace std;
int main()
{
	IplImage * test,*test_1;
	test = cvLoadImage("6013202130.jpg",0);//ͼƬ·���� ConsoleApplication4 �ļ����ͬʱʵ��Ҫ��תΪ�Ҷ�ͼƬ
	test_1 = cvCreateImage(cvSize((test->width)/2, (test->height)/2), IPL_DEPTH_8U, 1); //����ͼ�񣬸�ָ�븳ֵ
	cvResize(test, test_1, CV_INTER_LINEAR);
	cvNamedWindow("zhang_fei_1", CV_WINDOW_AUTOSIZE);
	cvShowImage("zhangfeio", test_1);
	cvNamedWindow("zhang_fei_2", CV_WINDOW_AUTOSIZE);
	cvShowImage("zhangfei", test);
	cvWaitKey(0);//�ȴ�����
	cvDestroyWindow("zhang_fei_1");
	cvDestroyWindow("zhang_fei_2");
	cvReleaseImage(&test);//�ͷ��ڴ档 
	cvReleaseImage(&test_1);
	return 0;
}
