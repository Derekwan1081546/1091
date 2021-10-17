#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>

using namespace std;
using namespace cv;

int main(int argc,char* argv[])
{
	Mat image = imread("ex1.jpg", 1);
	//Mat image = imread(argv[1], 1);
	Mat canny, Imgss;
	cvtColor(image, Imgss, COLOR_BGR2GRAY);
	GaussianBlur(Imgss, Imgss, Size(5, 5), 0);
	Canny(Imgss, canny, 35, 125);
	vector<vector<Point>> contours;
	findContours(canny, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
	vector<Point> contours_poly;

	double tmp = 0;
	int c = 0;
	vector<Point>f;
	for (int i = 0; i < contours.size(); i++)
	{
		double x = contourArea(contours[i]);
		if (x > tmp)
		{
			tmp = x;
			f = contours[i];
		}		
	}
	approxPolyDP(f, contours_poly, 3, true);
	RotatedRect resultRect = minAreaRect(contours_poly);
	Point2f pt[4];
	resultRect.points(pt);
	
	double parameter, ref,a;
	a = sqrt(pow(pt[0].x - pt[3].x, 2) + pow((pt[0].y - pt[3].y), 2));
	parameter = 210 * 3752.24 / a;
	cout << parameter;
	return 0;
}

