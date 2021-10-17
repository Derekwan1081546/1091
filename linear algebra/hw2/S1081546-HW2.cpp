#define _USE_MATH_DEFINES
#include<iostream>
#include<opencv2\opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

//calculate the slope
double getslope(Vec4i lines)
{
	/*double max = 0, temp;
	Vec4i longest;
	for (auto& l : lines)
	{
		temp = norm(Point(l[2], l[3]) - Point(l[0], l[1]));
		if (temp > max)
		{
			max = temp;
			longest = l;
		}
	}*/
	double k = (double)(lines[3] - lines[1]) / (double)(lines[2] - lines[0]);
	if (atan(k) > 0)
		return atan(k) * 180.0 / M_PI + 270;
	else
		return atan(k) * 180.0 / M_PI + 90;
}
Vec4i getlongestline(vector<Vec4i> lines)
{
	double max = 0, temp;
	Vec4i longest;
	for (int i = 0; i < lines.size(); i++)
	{
		temp = sqrt(pow(lines[i][2] - lines[i][0], 2.0) + pow(lines[i][3] - lines[i][1], 2.0));
		if (temp > max)
		{
			max = temp;
			longest = lines[i];
		}
	}
	return longest;
}

int main(int argc, char* argv[])
{
	/*if (argc < 3)
		return -1;*/
	Mat Img = imread("exp2.jpg", 1);
	//Mat Img = imread(argv[1], 1);
	/*if (Img.empty())
		return -1;*/
	Mat canny, Imgss;
	cvtColor(Img, Imgss, COLOR_BGR2GRAY);
	Canny(Imgss, canny, 500, 100);

	//get hough lines
	vector<Vec4i> Lines;
	HoughLinesP(canny, Lines, 1, CV_PI / 180, 250, 200, 10);

	auto slope = getslope(getlongestline(Lines));

	//get center and rotate matrix
	Size sz = Img.size();
	Point2f  center(sz.width / 2, sz.height / 2);
	Mat rotmat = getRotationMatrix2D(center, slope, 1.0);

	//rotate
	Mat output;
	warpAffine(Img, output, rotmat, sz);
	//imwrite(argv[2], output);
	imwrite("OUTPUT.jpg", output);
	return 0;
}

//#include<opencv2\imgproc\imgproc.hpp>  
//#include<opencv2\opencv.hpp>  
//#include<opencv2\highgui\highgui.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//double get_lines_arctan(double lines[4])
//{
//	double longest[4];
//	double k = (double)(longest[3] - longest[1]) / (double)(longest[2] - longest[0]);
//	return atan(k) * 180.0 / CV_PI + 90;
//}
//
//int main(int argc, char const* argv[])
//{
//	Mat Image = imread("exp.jpg");
//	Mat CannyImg;
//	Canny(Image, CannyImg, 500, 100, 3);
//	imshow("CannyImg", CannyImg);
//
//	Mat DstImg;
//	//cvtColor(Image, DstImg,);
//	vector<Vec4i> Lines;
//	HoughLinesP(CannyImg, Lines, 1, CV_PI / 180, 250, 200, 10);
//	/*for (size_t i = 0; i < Lines.size(); i++)
//	{
//		line(DstImg, Point(Lines[i][0], Lines[i][1]), Point(Lines[i][2], Lines[i][3]), Scalar(0, 0, 255), 2, 8);
//	}*/
//	/*imshow("HoughLines_Detect", DstImg);
//	imwrite("HoughLines_Detect.jpg", DstImg);*/
//	waitKey(0);
//
//	//double lines[4];
//	//double lines_arctan;//直線斜率的反正切值
//	//lines_arctan = get_lines_arctan(lines);
//	//Size size = Image.size();
//	//warpAffine(Image, CannyImg, DstImg, size);
//
//	return 0;
//}
