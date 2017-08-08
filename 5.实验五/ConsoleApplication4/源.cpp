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



/*
      2016年4月13日21:07:50编写opencv读取每个像素点的rgb值，并通过公式转换成hsi然后输出新图像
	  编写了一个子函数rgb转换为hsi的公式。


*/

#include <cv.h>
#include <highgui.h> 
# include <math.h>
#define M_PI 3.1415
void RGB_to_HSI(IplImage *src, IplImage *dst);
int main(void)
{
	IplImage * oo  = cvLoadImage   ("6013202130.jpg", 1);
	IplImage * xx  = cvCreateImage  (cvGetSize(oo), 8, 1);
	RGB_to_HSI(oo, xx);
	cvNamedWindow("原图", 1);
	cvNamedWindow("HSI", 1);
	cvShowImage("原图", oo);
	cvShowImage("HSI" , xx);
	cvWaitKey(0);
	cvReleaseImage(&xx);
	cvReleaseImage(&oo);
	return 0;
}

void RGB_to_HSI(IplImage *src, IplImage *dst)
{
	int i, j;
	double b, g, r, numm, den, min, theta, H, S, I;
	CvScalar s0;
	for (i = 0; i<src->height; i++)
	for (j = 0; j<src->width; j++)
	{

		s0 = cvGet2D(src, i, j);
		b = s0.val[0] / 255;//rgb归一化
		g = s0.val[1] / 255;
		r = s0.val[2] / 255;
		//几何推导法转换
		numm = 0.5*((r - g) + (r - b));
		den = sqrt((r - g)*(r - g) + (r - b)*(g - b));
		if (den == 0)
			H = 0;
		else
		{
			theta = acos(numm / den);
			if (b>g)
				H = (2 * M_PI - theta) / (2 * M_PI);
			else
				H = theta / (2 * M_PI);
		}
		min = (b>g) ? g : b;
		min = (min>r) ? r : min;
		den = r + g + b;
		if (den == 0)
			S = 0;
		else
			S = 1 - 3 * min / den;
		I = (r + g + b) / 3;
		cvSet2D(dst, i, j, cvScalar(H * 180, S * 255, I * 255));
	}
}

















