#include "Main.h"

Mat image;

int main(){
	Camera camera;
	HandDetecter handDetector;
	/*
	setMouseCallback("Camera", onMouse, 0);
	DispHSV(&camera);
	*/
	while(cvWaitKey(1) == -1){
		camera.Capture();
		handDetector.Detect(&camera.getImage());
		//camera.Show();
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

void DispHSV(Camera* camera){
	while(cvWaitKey(1) == -1){
		camera->Capture();
		camera->ConvertHSV();
		image = camera->getImage();
		camera->Show();
	}
}