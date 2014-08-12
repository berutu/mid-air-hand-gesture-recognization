#include "Camera.h"
#include "Labeling.h"

class HandDetecter
{
	private :
		Mat image, reduceImage, skinImage, labelImage;
		CvSeq *contours;
	public :
		HandDetecter();
		void Detect(Mat*);
		void FleshDetect();
		void Labeling();
		void Outline(Mat*);
		void DrawOutline(IplImage*);
		void DrawPoint(IplImage*);
		void CalculateAngle(IplImage*);
		void Show();
};