#include <C:\opencv\build\include\opencv2\opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <C:\opencv\build\include\opencv2\highgui\highgui.hpp>
#include <C:\opencv\build\include\opencv2\imgproc\imgproc.hpp>
#include <stdlib.h>
#include <math.h>

#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;


#ifdef _DEBUG
    //Debug���[�h�̏ꍇ
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_core244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_imgproc244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_highgui244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_objdetect244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_contrib244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_features2d244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_flann244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_gpu244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_legacy244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_ts244d.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_video244d.lib")
	#pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_calib3d244d.lib")
	#pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_nonfree244d.lib")
#else
    //Release���[�h�̏ꍇ
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_core244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_imgproc244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_highgui244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_objdetect244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_contrib244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_features2d244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_flann244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_gpu244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_legacy244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_ts244.lib")
    #pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_video244.lib")
	#pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_calib3d244.lib")
	#pragma comment(lib,"C:\\opencv\\build\\x64\\vc10\\lib\\opencv_nonfree244.lib")
#endif
