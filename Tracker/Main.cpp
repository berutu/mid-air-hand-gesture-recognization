#include "Main.h"

Mat image;

int main(){
	HandDetecter handDetector;
	/*CaptureImage captureImage;
	setMouseCallback("CameraImage", onMouse, 0);
	DispHSV(&captureImage);
	*/
	while(cvWaitKey(1) == -1){
		handDetector.Detect();
	}
}

void onMouse(int event, int x, int y, int flags, void *){
	switch(event){
	case CV_EVENT_LBUTTONDOWN:
		cout << x << ", " << y << endl;
		cout << image.at<Vec3b>(y, x) << endl;
		break;
	default:
		break;
	}
}

void DispHSV(CaptureImage* captureImage){
	while(cvWaitKey(1) == -1){
		captureImage->Capture();
		captureImage->ConvertHSV();
		image = captureImage->getImage();
		captureImage->Show();
	}
}