#include "HandDetect.h"

HandDetecter::HandDetecter(){
}

void HandDetecter::Detect(){
	captureImage.Capture();
	image = captureImage.getImage();
	FleshDetect();
	Labeling();
	Show();
	captureImage.Show();
}

void HandDetecter::FleshDetect(){
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
	labelImage = Mat(image.size(), CV_16SC1);
	labeling.Exec(skinImage.data, (short*)labelImage.data, skinImage.cols, skinImage.rows, true, 0);

	outImage = Mat(image.size(), CV_8UC1);
	compare(labelImage, 1, outImage, CV_CMP_EQ);

	resize(outImage, outImage, Size(), 2, 2);
	
}

void HandDetecter::Show(){
	imshow("skin", skinImage);
	imshow("out", outImage);
}