#include "Camera.h"

Camera::Camera(){
	videoCapture = cvCreateCameraCapture(1);
	windowName = "CameraImage";
	if(videoCapture == NULL)
		exit(1);
	// ウィンドウを作成する
	//cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE );

	//setMouseCallback(windowName, Mouse, 0);
}

Camera::~Camera(){
	 // ビデオキャプチャを解放する
    cvReleaseCapture( &videoCapture );

    // ウィンドウを破棄する
    cvDestroyWindow( windowName );
}

void Camera::Capture(){
	iplimage = cvQueryFrame( videoCapture );
	image = cvarrToMat(iplimage);
	//cout << image.rows << image.cols << endl;
}


void Camera::Show(){
	imshow(windowName, image);
}

Mat Camera::getImage(){
	return image;
}

void Camera::ConvertHSV(){
	cvtColor(image, image,  CV_BGR2HSV);
}