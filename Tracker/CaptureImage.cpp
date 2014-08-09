#include "CaptureImage.h"

CaptureImage::CaptureImage(){
	videoCapture = cvCreateCameraCapture(1);
	windowName = "CameraImage";
	if(videoCapture == NULL)
		exit(1);
	// �E�B���h�E���쐬����
	cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE );

	//setMouseCallback(windowName, Mouse, 0);
}

CaptureImage::~CaptureImage(){
	 // �r�f�I�L���v�`�����������
    cvReleaseCapture( &videoCapture );

    // �E�B���h�E��j������
    cvDestroyWindow( windowName );
}

void CaptureImage::Capture(){
	iplimage = cvQueryFrame( videoCapture );
	image = cvarrToMat(iplimage);
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