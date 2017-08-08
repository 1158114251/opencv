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


#include "cv.h"
#include<stdio.h> 
#include "highgui.h"
//using namespace cv;


IplImage *PingYi(IplImage *src, int h0, int w0);
int main(int argc, char** argv)
{

	IplImage* pImg; //����IplImageָ��
	IplImage* pImgAfterMove;
	pImg = cvLoadImage("6013202130.jpg");
	pImgAfterMove = cvCloneImage(pImg);
	cvSetZero(pImgAfterMove);
	pImgAfterMove = PingYi(pImg, 100, -100);

	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", pImg);
	cvNamedWindow("�ƶ���", CV_WINDOW_AUTOSIZE);
	cvShowImage("�ƶ���", pImgAfterMove);
	cvWaitKey(0); //�ȴ�����

	cvDestroyWindow("aa");//���ٴ���
	cvDestroyWindow("bb");
	cvReleaseImage(&pImg); //�ͷ�ͼ��
	cvReleaseImage(&pImgAfterMove);
	return 0;
}

//�ú����Ĺ�����ʵ��ͼ���ƽ��
//�涨���¡�����Ϊ����������
IplImage *PingYi(IplImage *src, int h0, int w0)
{
	int h = h0;
	int w = w0;
	int imageHeight = src->height;
	int imageWidth = src->width;
	int i, j;

	CvScalar sTemp;

	IplImage *dst = cvCloneImage(src);
	cvSetZero(dst);

	if (h >= 0 && w >= 0)
	{
		//
		for (i = 0; i<imageHeight - h; i++)
		{
			for (j = 0; j<imageWidth - w; j++)
			{
				sTemp = cvGet2D(src, i, j);
				cvSet2D(dst, i + h, j + w, sTemp);
			}
		}
	}
	else if (h<0 && w >= 0)
	{
		for (i = -h; i<imageHeight; i++)
		{
			for (j = 0; j<imageWidth - w; j++)
			{
				sTemp = cvGet2D(src, i, j);
				cvSet2D(dst, i + h, j + w, sTemp);
			}
		}
	}
	else if (h >= 0 && w<0)
	{
		//
		for (i = 0; i<imageHeight - h; i++)
		{
			for (j = -w; j<imageWidth; j++)
			{
				sTemp = cvGet2D(src, i, j);
				cvSet2D(dst, i + h, j + w, sTemp);
			}
		}
	}
	else if (h<0 && w<0)
	{
		//
		for (i = -h; i<imageHeight; i++)
		{
			for (j = -w; j<imageWidth; j++)
			{
				sTemp = cvGet2D(src, i, j);
				cvSet2D(dst, i + h, j + w, sTemp);
			}
		}
	}
	else
	{
		printf("�޷��ƶ�Ŷ��");
		dst = cvCloneImage(src);
	}
	return dst;
}