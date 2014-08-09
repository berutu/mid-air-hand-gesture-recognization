#include "OpenCV.h"

class CaptureImage
{
	private :
		CvCapture *videoCapture;
		IplImage *iplimage;
		Mat image;
		char* windowName;

	public:
		CaptureImage();
		void Capture();
		void Show();
		Mat getImage();
		void ConvertHSV();
		~CaptureImage();

	/*static void Mouse(int event, int x, int y, int flags, void *){
	switch(event){
		case CV_EVENT_LBUTTONDOWN:
			cout << x << ", " << y << endl;
			break;
		default:
			break;
		}
	}*/
};