#include "Main.h"
#include <Windows.h>
#include <mmsystem.h>

Mat image;

int main(){
	Camera camera;
	HandDetecter handDetector;
	DWORD startTime, endTime, passTime;
	/*
	setMouseCallback("Camera", onMouse, 0);
	DispHSV(&camera);
	*/
	while(cvWaitKey(1) == -1){
		startTime = timeGetTime();
		camera.Capture();
		handDetector.Detect(&camera.getImage());
		endTime = timeGetTime();
		passTime = endTime - startTime;
		cout << (float)1000 / passTime << endl;
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

