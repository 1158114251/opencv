/**********************************************************************************************************
 *  opencv 学习 ： 2016年3月15日20:10:06

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
 ***********************************************************************************************************/

/**********************************************************************************************************
*  opencv 学习 ： 2016年3月15日20:10:06

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
***********************************************************************************************************/

#include <cxcore.h>
#include <cv.h>
#include <highgui.h>
void cvDcT(CvArr * src_arr, CvArr * dst_arr)
{
	CvMat * tmp;
	CvMat q1stub, q2stub;
	CvMat q3stub, q4stub;
	CvMat d1stub, d2stub;
	CvMat d3stub, d4stub;
	CvMat * q1, *q2, *q3, *q4;
	CvMat * d1, *d2, *d3, *d4;

	CvSize size = cvGetSize(src_arr);
	CvSize dst_size = cvGetSize(dst_arr);
	int cx, cy;

	if (dst_size.width != size.width ||
		dst_size.height != size.height){
		cvError(CV_StsUnmatchedSizes, "cvShiftDFT", "Source and Destination arrays must have equal sizes", __FILE__, __LINE__);
	}

	if (src_arr == dst_arr){
		tmp = cvCreateMat(size.height / 2, size.width / 2, cvGetElemType(src_arr));
	}

	cx = size.width / 2;
	cy = size.height / 2;

	q1 = cvGetSubRect(src_arr, &q1stub, cvRect(0, 0, cx, cy));
	q2 = cvGetSubRect(src_arr, &q2stub, cvRect(cx, 0, cx, cy));
	q3 = cvGetSubRect(src_arr, &q3stub, cvRect(cx, cy, cx, cy));
	q4 = cvGetSubRect(src_arr, &q4stub, cvRect(0, cy, cx, cy));
	d1 = cvGetSubRect(dst_arr, &d1stub, cvRect(0, 0, cx, cy));
	d2 = cvGetSubRect(dst_arr, &d2stub, cvRect(cx, 0, cx, cy));
	d3 = cvGetSubRect(dst_arr, &d3stub, cvRect(cx, cy, cx, cy));
	d4 = cvGetSubRect(dst_arr, &d4stub, cvRect(0, cy, cx, cy));

	if (src_arr != dst_arr){
		if (!CV_ARE_TYPES_EQ(q1, d1)){
			cvError(CV_StsUnmatchedFormats, "cvShiftDFT", "Source and Destination arrays must have the same format", __FILE__, __LINE__);
		}
		cvCopy(q3, d1, 0);
		cvCopy(q4, d2, 0);
		cvCopy(q1, d3, 0);
		cvCopy(q2, d4, 0);
	}
	else{
		cvCopy(q3, tmp, 0);
		cvCopy(q1, q3, 0);
		cvCopy(tmp, q1, 0);
		cvCopy(q4, tmp, 0);
		cvCopy(q2, q4, 0);
		cvCopy(tmp, q2, 0);
	}
}

int main(int argc, char ** argv)
{
	const char* filename = argc >= 2 ? argv[1] : "2.bmp";
	IplImage * im;

	IplImage * realInput;
	IplImage * imaginaryInput;
	IplImage * complexInput;
	int dft_M, dft_N;
	CvMat* dft_A, tmp;
	IplImage * image_Re;
	IplImage * image_Im;
	double m, M;

	im = cvLoadImage("6013202130.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	if (!im)
		return -1;

	realInput = cvCreateImage(cvGetSize(im), IPL_DEPTH_64F, 1);
	imaginaryInput = cvCreateImage(cvGetSize(im), IPL_DEPTH_64F, 1);
	complexInput = cvCreateImage(cvGetSize(im), IPL_DEPTH_64F, 2);

	cvScale(im, realInput, 1.0, 0.0);
	cvZero(imaginaryInput);
	cvMerge(realInput, imaginaryInput, NULL, NULL, complexInput);

	dft_M = cvGetOptimalDFTSize(im->height - 1);
	dft_N = cvGetOptimalDFTSize(im->width - 1);

	dft_A = cvCreateMat(dft_M, dft_N, CV_64FC2);
	image_Re = cvCreateImage(cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);
	image_Im = cvCreateImage(cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);

	// copy A to dft_A and pad dft_A with zeros
	cvGetSubRect(dft_A, &tmp, cvRect(0, 0, im->width, im->height));
	cvCopy(complexInput, &tmp, NULL);
	if (dft_A->cols > im->width)
	{
		cvGetSubRect(dft_A, &tmp, cvRect(im->width, 0, dft_A->cols - im->width, im->height));
		cvZero(&tmp);
	}



	cvDFT(dft_A, dft_A, CV_DXT_FORWARD, complexInput->height);

	cvNamedWindow("win", 0);
	cvNamedWindow("magnitude", 0);
	cvShowImage("win", im);


	cvSplit(dft_A, image_Re, image_Im, 0, 0);


	cvPow(image_Re, image_Re, 2.0);
	cvPow(image_Im, image_Im, 2.0);
	cvAdd(image_Re, image_Im, image_Re, NULL);
	cvPow(image_Re, image_Re, 0.5);


	cvAddS(image_Re, cvScalarAll(1.0), image_Re, NULL);
	cvLog(image_Re, image_Re);

	cvDcT(image_Re, image_Re);

	cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);
	cvScale(image_Re, image_Re, 1.0 / (M - m), 1.0*(-m) / (M - m));
	cvShowImage("magnitude", image_Re);

	cvWaitKey(-1);
	return 0;
}