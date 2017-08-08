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

#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>


/**************************************************************************
//傅里叶变换
//src IPL_DEPTH_8U
//dst IPL_DEPTH_64F
/**************************************************************************/


void fft2(IplImage *src, IplImage *dst)
{
	IplImage *image_Re = 0, *image_Im = 0, *Fourier = 0; //实部、虚部


	image_Re = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);  //实部


	image_Im = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);  //虚部


	Fourier = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 2);//2 channels (image_Re, image_Im)


	cvConvertScale(src, image_Re, 1, 0);// Real part conversion from u8 to 64f (double)


	cvZero(image_Im);// Imaginary part (zeros)


	cvMerge(image_Re, image_Im, 0, 0, Fourier);// Join real and imaginary parts and stock them in Fourier image


	cvDFT(Fourier, dst, CV_DXT_FORWARD);// Application of the forward Fourier transform


	cvReleaseImage(&image_Re);
	cvReleaseImage(&image_Im);
	cvReleaseImage(&Fourier);
}


/**************************************************************************
//中心化
//src IPL_DEPTH_64F
//dst IPL_DEPTH_8U
**************************************************************************/
void fft2shift(IplImage *src, IplImage *dst)
{
	IplImage *image_Re = 0, *image_Im = 0;
	int nRow, nCol, i, j, cy, cx;
	double scale, shift, tmp13, tmp24;


	image_Re = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);


	image_Im = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);
	cvSplit(src, image_Re, image_Im, 0, 0);


	//具体原理见冈萨雷斯数字图像处理p123
	// Compute the magnitude of the spectrum Mag = sqrt(Re^2 + Im^2)
	//计算傅里叶谱
	cvPow(image_Re, image_Re, 2.0);
	cvPow(image_Im, image_Im, 2.0);
	cvAdd(image_Re, image_Im, image_Re);
	cvPow(image_Re, image_Re, 0.5);


	//对数变换以增强灰度级细节(这种变换使以窄带低灰度输入图像值映射一宽带输出值，具体可见冈萨雷斯数字图像处理p62)
	// Compute log(1 + Mag);
	cvAddS(image_Re, cvScalar(1.0), image_Re); // 1 + Mag
	cvLog(image_Re, image_Re); // log(1 + Mag)


	//Rearrange the quadrants of Fourier image so that the origin is at the image center
	nRow = src->height; nCol = src->width;
	cx = nCol / 2; cy = nRow / 2; // image center


	//CV_IMAGE_ELEM为OpenCV定义的宏，用来读取图像的像素值，这一部分就是进行中心变换
	for (j = 0; j < cy; j++){
		for (i = 0; i < cx; i++){
			//中心化，将整体份成四块进行对角交换
			tmp13 = CV_IMAGE_ELEM(image_Re, double, j, i);
			CV_IMAGE_ELEM(image_Re, double, j, i) = CV_IMAGE_ELEM(image_Re, double, j + cy, i + cx);
			CV_IMAGE_ELEM(image_Re, double, j + cy, i + cx) = tmp13;


			tmp24 = CV_IMAGE_ELEM(image_Re, double, j, i + cx);
			CV_IMAGE_ELEM(image_Re, double, j, i + cx) = CV_IMAGE_ELEM(image_Re, double, j + cy, i);
			CV_IMAGE_ELEM(image_Re, double, j + cy, i) = tmp24;
		}
	}
	//归一化处理将矩阵的元素值归一为[0,255]
	//[(f(x,y)-minVal)/(maxVal-minVal)]*255
	double minVal = 0, maxVal = 0;
	// Localize minimum and maximum values
	cvMinMaxLoc(image_Re, &minVal, &maxVal);
	// Normalize image (0 - 255) to be observed as an u8 image
	scale = 255 / (maxVal - minVal);
	shift = -minVal * scale;
	cvConvertScale(image_Re, dst, scale, shift);
	cvReleaseImage(&image_Re);
	cvReleaseImage(&image_Im);


}


/***********************************************************************/
int main()
{
	IplImage *src;          //源图像
	IplImage *Fourier;   //傅里叶系数
	IplImage *dst;


	IplImage *ImageRe;
	IplImage *ImageIm;


	IplImage *Image;
	IplImage *ImageDst;


	double m, M;
	double scale;
	double shift;
	src = cvLoadImage("6013202130.bmp", 0);   //加载源图像，第二个参数表示将输入的图片转为单信道 
	Fourier = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 2);
	dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 2);
	ImageRe = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);
	ImageIm = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);
	Image = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	ImageDst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	fft2(src, Fourier);                  //傅里叶变换
	fft2shift(Fourier, Image);          //中心化
	cvDFT(Fourier, dst, CV_DXT_INV_SCALE);//实现傅里叶逆变换，并对结果进行缩放
	cvSplit(dst, ImageRe, ImageIm, 0, 0);


	cvNamedWindow("源图像", 0);
	cvShowImage("源图像", src);
	//对数组每个元素平方并存储在第二个参数中
	cvPow(ImageRe, ImageRe, 2);
	cvPow(ImageIm, ImageIm, 2);
	cvAdd(ImageRe, ImageIm, ImageRe, NULL);
	cvPow(ImageRe, ImageRe, 0.5);
	cvMinMaxLoc(ImageRe, &m, &M, NULL, NULL);
	scale = 255 / (M - m);
	shift = -m * scale;
	//将shift加在ImageRe各元素按比例缩放的结果上，存储为ImageDst
	cvConvertScale(ImageRe, ImageDst, scale, shift);


	cvNamedWindow("傅里叶谱", 0);
	cvShowImage("傅里叶谱", Image);
	cvNamedWindow("傅里叶逆变换", 0);
	cvShowImage("傅里叶逆变换", ImageDst);


	cvWaitKey(0);


	cvReleaseImage(&src);
	cvReleaseImage(&Image);
	cvReleaseImage(&ImageIm);
	cvReleaseImage(&ImageRe);
	cvReleaseImage(&Fourier);
	cvReleaseImage(&dst);
	cvReleaseImage(&ImageDst);
	cvDestroyAllWindows();
	return 0;
}