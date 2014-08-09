#include "CaptureImage.h"
#include "Labeling.h"

class HandDetecter
{
	private :
		CaptureImage captureImage;
		Mat image, smoothImage, hsvImage, skinImage, labelImage, outImage;
	public :
		HandDetecter();
		void Detect();
		void FleshDetect();
		void Labeling();
		void Show();
};