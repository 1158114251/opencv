/**********************************************************************************************************
 *  opencv ѧϰ �� 2016��3��24��18:30:08

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

8.cvCvtPixToPlane��openCV�����һ������
#define cvCvtPixToPlane cvSplit
void cvSplit( const CvArr* oo, CvArr* dst0, CvArr* dst1,CvArr* dst2, CvArr* dst3 );
�����ǣ��ָ��ͨ������ɼ�����ͨ��������ߴ���������ȡһ��ͨ��
һ���÷���cvCvtPixToPlane��IplImage * src,IplImage * dst1,IplImage *dst2,IplImage * dst3,IplImage *dst4)
��һ��������Դͼ�񣬺����Ƿ������ÿ��ͨ����Ŀ��ͼ�����ԭͼ����3ͨ���ģ����԰����һ����������Ϊ�ա�����cvCvtPixToPlane��IplImage * src,IplImage * dst1,IplImage *dst2,IplImage * dst3,NULL)��NULLҲ����дΪ0.
ʹ�øú��������#include<cv.h>ͷ�ļ�

9.CvSetImageCOI������ͼ���COI������Ȥͨ���� of interesting���ĺ�����
���ܣ�
����ͼ���COI������Ȥͨ���� of interesting��
��ʽ��
void cvSetImageCOI��IplImage* image,int coi����
����
image ͼ��ͷ,������ͼ��
coiΪ0ʱ��ʾѡ������ͨ����1��ʾ��һ��ͨ����2��ʾ�ڶ����ȵ�

10.cvCreateImage( CvSize size, int depth, int s );
�����׵�ַ������洢�ռ�,���ص��ǵ�ַ��


 ***********************************************************************************************************/


#include <cv.h>
#include <highgui.h> 

int main(void)
{
	IplImage* oo = cvLoadImage("6013202130.jpg", 1);
	IplImage * Red = cvCreateImage(cvGetSize(oo), 8, 1);
	IplImage * Green = cvCreateImage(cvGetSize(oo), 8, 1);
	IplImage * Blue = cvCreateImage(cvGetSize(oo), 8, 1);
	cvSetImageCOI(oo, 1);       //ͨ��1 ����ɫ
	cvCopy(oo, Blue);   //���Ƶ�Blue
	cvSetImageCOI(oo, 2);       //ͨ��2 ����ɫ
	cvCopy(oo, Green); 
	cvSetImageCOI(oo, 3);       //ͨ��3 ����ɫ
	cvCopy(oo, Red); 
	cvNamedWindow("Red", 1);
	cvNamedWindow("Green", 1);
	cvNamedWindow("Blue", 1);
	cvNamedWindow("oo", 1);
	cvShowImage("ԭͼ", oo);
	cvShowImage("Red", Red);
	cvShowImage("Green", Green);
	cvShowImage("Blue", Blue);
	cvWaitKey(0);
	cvReleaseImage(&Red);
	cvReleaseImage(&Green);
	cvReleaseImage(&Blue);
	cvReleaseImage(&oo);
	return 0;
}














