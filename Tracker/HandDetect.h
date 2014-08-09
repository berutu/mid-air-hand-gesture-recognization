#include "CaptureImage.h"
#include "Labeling.h"

class HandDetecter
{
	private :
		CaptureImage captureImage;
		Mat image, skinImage, labelImage;
	public :
		HandDetecter();
		void Detect();
		void FleshDetect();
		void Labeling();
		void Outline(Mat*);
		void DrawOutline(IplImage*, CvSeq*);
		void Show();
};