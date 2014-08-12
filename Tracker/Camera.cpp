#include "Camera.h"

Camera::Camera(){
	videoCapture = cvCreateCameraCapture(1);
	windowName = "CameraImage";
	if(videoCapture == NULL)
		exit(1);
	// �E�B���h�E���쐬����
	//cvNamedWindow( windowName, CV_WINDOW_AUTOSIZE );

	//setMouseCallback(windowName, Mouse, 0);
}

Camera::~Camera(){
	 // �r�f�I�L���v�`�����������
    cvReleaseCapture( &videoCapture );

    // �E�B���h�E��j������
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