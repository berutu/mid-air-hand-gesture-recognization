#include "CaptureImage.h"

CaptureImage::CaptureImage(){
	videoCapture = cvCreateCameraCapture(1);
	windowName = "CameraImage";
	if(videoCapture == NULL)
		exit(1);
	// ウィンドウを作成する
	cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE );

	//setMouseCallback(windowName, Mouse, 0);
}

CaptureImage::~CaptureImage(){
	 // ビデオキャプチャを解放する
    cvReleaseCapture( &videoCapture );

    // ウィンドウを破棄する
    cvDestroyWindow( windowName );
}

void CaptureImage::Capture(){
	iplimage = cvQueryFrame( videoCapture );
	image = cvarrToMat(iplimage);
	resize(image, image, Size(), 0.5, 0.5);
	//cout << image.rows << image.cols << endl;
}


void CaptureImage::Show(){
	imshow(windowName, image);
}

Mat CaptureImage::getImage(){
	return image;
}

void CaptureImage::ConvertHSV(){
	cvtColor(image, image,  CV_BGR2HSV);
}