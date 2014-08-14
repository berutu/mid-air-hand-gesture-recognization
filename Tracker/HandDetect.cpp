#include "HandDetect.h"

HandDetecter::HandDetecter(){
}

void HandDetecter::Detect(Mat* image){
	this->image = *image;
	resize(this->image, reduceImage, Size(), 0.5, 0.5);
	FleshDetect();
	Labeling();
	Draw();
	Show();
}

void HandDetecter::FleshDetect(){
	Mat smoothImage(Size(reduceImage.cols, reduceImage.rows), CV_8UC3);
	Mat hsvImage(Size(reduceImage.cols, reduceImage.rows), CV_8UC3);

	skinImage = Mat(Size(reduceImage.cols, reduceImage.rows), CV_8UC1);
	
	medianBlur(reduceImage, smoothImage, 5);
	cvtColor(smoothImage, hsvImage, CV_BGR2HSV);

	for(int i = 0; i < hsvImage.rows;i++)
		for(int j = 0; j < hsvImage.cols; j++){
			int a = hsvImage.step * i + (j * 3);
			if((hsvImage.data[a] >= 0 || hsvImage.data[a] <= 5) && hsvImage.data[a+1] >= 110 && hsvImage.data[a+2] >= 50)
			{
				skinImage.at<unsigned char>(i, j) = 255;
			}else{
				skinImage.at<unsigned char>(i, j) = 0;
			}
		}

}

void HandDetecter::Labeling(){
	RNG rnd(1192);
	LabelingBS labeling;
	RegionInfoBS *ri;
	Mat allLabelImage(reduceImage.size(), CV_16SC1);
	Mat grayLabelImage(reduceImage.size(), CV_8UC1);

	labeling.Exec(skinImage.data, (short*)allLabelImage.data, skinImage.cols, skinImage.rows, true, 0);
	
	if(labeling.GetNumOfRegions() != 0)	{
		ri = labeling.GetResultRegionInfo(0);
		ri->GetCenterOfGravity(centerX, centerY);
		centerX *= 2;
		centerY *= 2;
	}
	compare(allLabelImage, 1, grayLabelImage, CV_CMP_EQ);
	resize(grayLabelImage, grayLabelImage, Size(), 2, 2);
	imshow("gray", grayLabelImage);
	labelImage = Mat(image.size(), CV_8UC3);
	for(int i = 0; i < image.rows; i++)
		for(int j = 0; j < image.cols; j++){
			if(grayLabelImage.at<unsigned char>(i, j) == 255)
				labelImage.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);
			else
				labelImage.at<Vec3b>(i, j) = (0, 0, 0);
		}
	Outline(&grayLabelImage);
}

void HandDetecter::Outline(Mat* grayImage){
	CvMemStorage *storage = cvCreateMemStorage(0);
	contours = NULL;
	IplImage iplgray = *grayImage;
	//cvShowImage("gray", &iplgray);
	
	cvFindContours(&iplgray, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	if(contours != NULL){
		IplImage iplImage = labelImage;
		DrawOutline(&iplImage);
		//DrawPoint(&iplImage);
		CalculateAngle(&iplImage);
	}
}

void HandDetecter::DrawOutline(IplImage* iplImage){
	CvScalar ContoursColor = CV_RGB(255, 0, 0);
	cvDrawContours(iplImage, contours, ContoursColor, ContoursColor, 0, 2);
	//cvShowImage("image", iplImage);

}

void HandDetecter::DrawPoint(IplImage* iplImage){
	CvPoint* point;
	for(int i = 0; i < contours->total; i = i+25){
		point = (CvPoint*)cvGetSeqElem(contours, i);
		cvCircle(iplImage, *point, 6, CV_RGB(0, 255, 0), 2);
	}
	//cvShowImage("Pointimage", iplImage);
}

void HandDetecter::CalculateAngle(IplImage* iplImage){
	list<CvPoint> points;
	CvPoint *point1, *point2, *point3;
	float angle = 0;
	for(int i= 20; i < contours->total - 20; i = i+20){
		point1 = (CvPoint*)cvGetSeqElem(contours, i-20);
		point2 = (CvPoint*)cvGetSeqElem(contours, i);
		point3 = (CvPoint*)cvGetSeqElem(contours, i+20);
		angle = fastAtan2(point3->y - point2->y, point3->x - point2->x)
			- fastAtan2(point1->y - point2->y, point1->x - point2->x);
		if(angle < 0)
			angle += 360;
		
		if(angle > 200 && angle < 300){
			hands.push_back(*point2);
		}

		if(angle > 0 && angle < 160){
			points.push_back(*point2);
		}else if(!points.empty()){
			list<CvPoint>::iterator it = points.begin();
			Point fingerpoint = (0, 0);
			while(it != points.end()){
				fingerpoint.x += it->x;
				fingerpoint.y += it->y;
				++it;
			}
			fingerpoint.x /= points.size();
			fingerpoint.y /= points.size();

			fingers.push_back(fingerpoint);

			//cvCircle(iplImage, fingerpoint, 6, CV_RGB(255, 0, 0), 2);

			points.clear();
		}
		//cvShowImage("image", iplImage);
	}
}

void HandDetecter::Draw(){
	Mat showImage = image;
	Point farPoint;
	circle(showImage, Point(centerX, centerY), 20, CV_RGB(0, 0, 255), 2);
	
	list<Point>::iterator it = fingers.begin();
	
	while(it != fingers.end()){
		circle(showImage, Point(it->x, it->y), 6, CV_RGB(255, 0, 0), 2);
		++it;
	}
	
	fingers.clear();
	
	imshow("Image", showImage);
}

void HandDetecter::Show(){
	//imshow("Image", this->image);
	//imshow("skin", skinImage);
	//imshow("out", labelImage);
}