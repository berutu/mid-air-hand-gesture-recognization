#include "OpenCV.h"

class Camera
{
	private :
		CvCapture *videoCapture;
		IplImage *iplimage;
		Mat image;
		char* windowName;

	public:
		Camera();
		~Camera();
		void Capture();
		void Show();
		Mat getImage();
		void ConvertHSV();
		void FileWrite();
		

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