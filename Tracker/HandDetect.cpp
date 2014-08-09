#include "HandDetect.h"

HandDetecter::HandDetecter(){
}

void HandDetecter::Detect(){
	captureImage.Capture();
	image = captureImage.getImage();
	resize(image, image, Size(), 0.5, 0.5);
	FleshDetect();
	Labeling();
	Show();
	captureImage.Show();
}

void HandDetecter::FleshDetect(){
	Mat smoothImage(Size(image.cols, image.rows), CV_8UC3);
	Mat hsvImage(Size(image.cols, image.rows), CV_8UC3);

	skinImage = Mat(Size(image.cols, image.rows), CV_8UC1);
	
	medianBlur(image, smoothImage, 7);
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
	Mat allLabelImage(image.size(), CV_16SC1);
	Mat grayLabelImage(image.size(), CV_8UC1);

	labeling.Exec(skinImage.data, (short*)allLabelImage.data, skinImage.cols, skinImage.rows, true, 0);
	compare(allLabelImage, 1, grayLabelImage, CV_CMP_EQ);

	labelImage = Mat(image.size(), CV_8UC3);

	for(int i = 0; i < image.rows; i++)
		for(int j = 0; j < image.cols; j++){
			if(grayLabelImage.at<unsigned char>(i, j) == 255)
				labelImage.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);
			else
				labelImage.at<Vec3b>(i, j) = (0, 0, 0);
		}

	Outline(&grayLabelImage);

	resize(grayLabelImage, grayLabelImage, Size(), 2, 2);
	resize(labelImage, labelImage, Size(), 2, 2);
	
}

void HandDetecter::Outline(Mat* grayImage){
	CvMemStorage *storage = cvCreateMemStorage (0);
	CvSeq *contours = NULL;
	
	cvFindContours(grayImage, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	if(contours != NULL){
		IplImage iplImage = labelImage;
		DrawOutline(&iplImage, contours);
	}
}

void HandDetecter::DrawOutline(IplImage* iplImage, CvSeq* contours){
	CvScalar ContoursColor = CV_RGB(255, 0, 0);
	
	cvDrawContours(&iplImage, contours, ContoursColor, ContoursColor, 0, 2);

	if(contours->h_next != NULL)
		DrawOutline(iplImage, contours->h_next);
	else
		labelImage = cvarrToMat(iplImage);
}

void HandDetecter::Show(){
	imshow("skin", skinImage);
	imshow("out", labelImage);
}