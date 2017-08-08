/**********************************************************************************************************
*  opencv 学习 ： 2016年3月24日18:30:08

1. 图像载入函数
函数cvLoadImage载入指定图像文件，并返回指向该文件的IplImage指针。函数支持bmp、jpg、 png、 tiff等格式的图像。其函数原型如下：
IplImage* cvLoadImage( const char* filename, int iscolor);
其中，filename 是待载入图像的名称，包括图像的扩展名；iscolor是一个辅助参数项，可选正数、零和负数三种值，正数表示作为三通道图像载入，零表示该图像作为单通道图像，负数表示载入图像的通道数由图像文件自身决定。
2. 窗口定义函数
函数cvNamedWindow定义一个窗口，用于显示图像。其函数原型如下：
int cvNamedWindow( const char* name, unsigned long flags );
其中，name是窗口名，flags是窗口属性指标值，可以选择CV_WINDOW_AUTOSIZE和0两种值。CV_WINDOW_AUTOSIZE表示窗口尺寸与图像原始尺寸相同，0表示以固定的窗口尺寸显示图像。
3. 图像显示函数
函数cvShowImage是在指定的窗口中显示图像，其函数原型如下：
void cvShowImage( const char* name, const CvArr* image );
其中，name是窗口名称，image是图像类型指针，一般是IplImage指针。
4. 图像保存函数
函数cvSaveImage以指定的文件名保存IplImage类型的指针变量，其函数原型如下：
int cvSaveImage( const char* filename, const CvArr* image );
其中，filename是图像保存路径和名称，image是IplImage指针变量。
5. 图像销毁函数
函数cvReleaseImage销毁已定义的IplImage指针变量，释放占用内存空间。其函数原型如下：
void cvReleaseImage( IplImage** image );
其中，image为已定义的IplImage指针。
6. 图像转换函数
cvGetImage( const CvArr* arr, IplImage* image_header )
7.销毁一个窗口。
void cvDestroyWindow( const char* name );

8.cvCvtPixToPlane是openCV里面的一个函数
#define cvCvtPixToPlane cvSplit
void cvSplit( const CvArr* oo, CvArr* dst0, CvArr* dst1,CvArr* dst2, CvArr* dst3 );
作用是：分割多通道数组成几个单通道数组或者从数组中提取一个通道
一般用法是cvCvtPixToPlane（IplImage * src,IplImage * dst1,IplImage *dst2,IplImage * dst3,IplImage *dst4)
第一个参数是源图像，后面是分离出来每个通道的目标图像，如果原图像是3通道的，可以把最后一个参数设置为空。例如cvCvtPixToPlane（IplImage * src,IplImage * dst1,IplImage *dst2,IplImage * dst3,NULL)，NULL也可以写为0.
使用该函数须包含#include<cv.h>头文件

9.CvSetImageCOI是设置图像的COI（感兴趣通道， of interesting）的函数。
功能：
设置图像的COI（感兴趣通道， of interesting）
格式：
void cvSetImageCOI（IplImage* image,int coi）；
参数
image 图像头,待处理图像
coi为0时表示选择所有通道，1表示第一个通道，2表示第二个等等

10.cvCreateImage( CvSize size, int depth, int s );
创建首地址并分配存储空间,返回的是地址。


***********************************************************************************************************/


#include "cv.h"
#include<stdio.h> 
#include "highgui.h"
//using namespace cv;


IplImage *PingYi(IplImage *src, int h0, int w0);
int main(int argc, char** argv)
{

	IplImage* pImg; //声明IplImage指针
	IplImage* pImgAfterMove;
	pImg = cvLoadImage("6013202130.jpg");
	pImgAfterMove = cvCloneImage(pImg);
	cvSetZero(pImgAfterMove);
	pImgAfterMove = PingYi(pImg, 100, -100);

	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvShowImage("原图", pImg);
	cvNamedWindow("移动后", CV_WINDOW_AUTOSIZE);
	cvShowImage("移动后", pImgAfterMove);
	cvWaitKey(0); //等待按键

	cvDestroyWindow("aa");//销毁窗口
	cvDestroyWindow("bb");
	cvReleaseImage(&pImg); //释放图像
	cvReleaseImage(&pImgAfterMove);
	return 0;
}

//该函数的功能是实现图像的平移
//规定向下、向右为（正，正）
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
		printf("无法移动哦！");
		dst = cvCloneImage(src);
	}
	return dst;
}