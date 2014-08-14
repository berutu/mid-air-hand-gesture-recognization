#include "Camera.h"
#include "Labeling.h"
#include <list>

class HandDetecter
{
	private :
		Mat image, reduceImage, skinImage, labelImage;
		float centerX, centerY;
		list<Point> fingers;
		list<Point> hands;
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
		void Draw();
		void Show();
};