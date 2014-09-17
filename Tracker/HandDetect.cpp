#include "HandDetect.h"

HandDetecter::HandDetecter(){
}

void HandDetecter::Hist(){
	int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
	int channels[] = {0, 1};
	float hranges[] = { 0, 180 };
    // 彩度の範囲は 0 （黒-灰色-白）から
    // 255 （純粋なスペクトルカラー）までです．
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
	Mat skin = imread("./Capture.png");
	calcHist(&skin, 1, channels, Mat(), hist, 2, histSize, ranges, true, false);
}

void HandDetecter::Detect(Mat* image){
	this->image = *image;
	/*resize(this->image, reduceImage, Size(), 0.5, 0.5);
	FleshDetect();
	Labeling();
	Draw();
	Show();*/
	Find();
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
			if(((hsvImage.data[a] >= 0 && hsvImage.data[a] <= 50) || (hsvImage.data[a] >= 150 && hsvImage.data[a] <= 180)) && hsvImage.data[a+1] <= 150 && hsvImage.data[a+2] >= 80)
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

void HandDetecter::Find(){
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	vector<Point> handContours;

	Mat hsv;
	cvtColor(image, hsv, CV_RGB2HSV);

	Mat backProject(hsv.size(), CV_8UC1);

	float hranges[] = { 0, 179 };
	float sranges[] = { 0, 255 };
	const float* ranges[] = { hranges, sranges };
	int channels[] = {0, 1};

	//resize(skinImage, skinImage, Size(), 2, 2);

	calcBackProject(&hsv, 1, channels, hist, backProject, ranges, 1, true);
	threshold(backProject, backProject, 30, 255, CV_THRESH_BINARY);
	medianBlur(backProject, backProject, 9);

	findContours(backProject, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

	if(!contours.empty()){
	double maxArea = 0.0F;
	int maxContour = 0;
	for(int i = 0; i < contours.size(); i++){
		double area = contourArea(contours[i]);
		if(area > maxArea){
			maxArea = area;
			maxContour = i;
		}
	}

	Moments m = moments(contours[maxContour], true);
	Point2i p = Point2i(m.m10/m.m00, m.m01/m.m00);

	drawContours(image, contours, maxContour, Scalar(255, 0, 0), 3);
	circle(image, p, 3, Scalar(0, 255, 0), 3);
	imshow("image", image);
	//imshow("skinImage", skinImage);
	imshow("backProject", backProject);
	}
}

void HandDetecter::Show(){
	//imshow("Image", this->image);
	//imshow("skin", skinImage);
	//imshow("out", labelImage);
}