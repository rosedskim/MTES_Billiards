//////////////////////////////////////////////////////////////////////////
//
// 이 화일은 함수 등록시 자동으로 생성된 프로젝트입니다.
//
// 사용자가 임으로 만든 경우, Project의 Setting...의 설정이 필요하므로,
//
// 이는 도움말의 '함수 작성법'을 참조 바랍니다.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "userPointSave.h"
#include <opencv2/core/core.hpp>	
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <KScOpenCvUtils.h>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;
using namespace cv;

struct item {
	int y;	//행
	int x;	//열
	int radius;	//반지름
};

vector<item> v;
//그 좌표의 값이 원의 범위 안에 있는지
double dist(int point_y, int point_x, int center_y, int center_x)
{
	int dist_y = (point_y - center_y);
	int dist_x = (point_x - center_x);
	return sqrt(dist_y*dist_y + dist_x*dist_x);
}
bool checkInRange(int y, int x, int radius, int index)
{
	int center_y = v[index].y;
	int center_x = v[index].x;
	//중심점과 좌표값의 거리가 radius보다 작거나 같은경우 == 범위안에 있는경우
	if (dist(y, x, center_y, center_x) <= radius)
	{
		return true;
	}
	//범위 안에 없는경우
	else
	{
		return false;
	}
}

// DLL을 만들기 위한 부분
BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: break;
	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	case DLL_PROCESS_DETACH: break;
	}

	return TRUE;
}

// 함수의 정의 부분
int CDECL userPointSave(int* point_y, int* point_x, KScRgbImage2d* input)
{
	int dx = input->GetXSize();
	int dy = input->GetYSize();

	Mat src, gray;
	src = KScRgbImage2dToMat(input);
	if (!src.data)
	{
		cout << "error" << "\n";
		return -1;
	}

	cvtColor(src, gray, CV_BGR2GRAY);

	GaussianBlur(gray, gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;	//원 정보
	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 20, 200, 20, 5, 50);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		item it;
		it.radius = radius;
		it.y = circles[i][1];
		it.x = circles[i][0];
		v.push_back(it);
		//circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//circle(src, center, radius, Scalar(0, 0, 255), 2, 8, 0);
	}
	MatToKScRgbImage2d(src, input);

	//input 이미지에 대한 R,G,B 색상
	KScScalarImage2dUint8 *input_red = new KScScalarImage2dUint8;
	input_red->Free();
	input_red->Alloc(dx, dy);
	KScScalarImage2dUint8 *input_green = new KScScalarImage2dUint8;
	input_green->Free();
	input_green->Alloc(dx, dy);
	KScScalarImage2dUint8 *input_blue = new KScScalarImage2dUint8;
	input_blue->Free();
	input_blue->Alloc(dx, dy);

	input->SplitAllPlane(input_red, input_green, input_blue);
	KSdUint8 **inputRedArray = input_red->Get2dArray();
	KSdUint8 **inputGreenArray = input_green->Get2dArray();
	KSdUint8 **inputBlueArray = input_blue->Get2dArray();
	int red_cnt = 1;
	for (int i = 0; i < v.size(); i++)
	{
		//원 그려진거에서 색깔로 구분하기
		item temp = v[i];
		int min_y = temp.y - temp.radius;
		int max_y = temp.y + temp.radius;
		int min_x = temp.x - temp.radius;
		int max_x = temp.x + temp.radius;

		vector<pair<int, int>> point;	//범위안에 있는 좌표

		int range_cnt = 0;	//전체 좌표의 개수
							//범위안에 있는 좌표만 point vector에 저장하기
		for (int j = min_y; j <= max_y; j++)
		{
			for (int k = min_x; k <= max_x; k++)
			{
				//이미지 크기 안에 있어야한다.
				if (0 < j && j < dy && 0 < k && k < dx)
				{
					//범위 안에 있는경우
					if (checkInRange(j, k, temp.radius, i))
					{
						range_cnt++;
						point.push_back({ j,k });
					}
				}
			}
		}
		int yellow_color_cnt = 0;	//색깔 알맞은 좌표의 개수	
		int red_color_cnt = 0;
		int white_color_cnt = 0;
		//전체 좌표중 색깔 맞는 좌표의 개수만 구하기
		for (int j = 0; j < point.size(); j++)
		{
			int y = point[j].first;
			int x = point[j].second;

			if (170 <= inputRedArray[y][x] && 170 <= inputGreenArray[y][x] && inputBlueArray[y][x] <= 170)
			{
				yellow_color_cnt++;
			}
			if (180 <= inputRedArray[y][x] && 40 <= inputGreenArray[y][x] && inputGreenArray[y][x] <= 70 && 100 <= inputBlueArray[y][x] && inputBlueArray[y][x] <= 150)
			{
				red_color_cnt++;
			}
			if (240 <= inputRedArray[y][x] && 240 <= inputGreenArray[y][x] && 240 <= inputBlueArray[y][x])
			{
				white_color_cnt++;
			}
		}
		double yellow_possible = (double)yellow_color_cnt / (double)range_cnt;
		double red_possible = (double)red_color_cnt / (double)range_cnt;
		double white_possible = (double)white_color_cnt / (double)range_cnt;
		if (yellow_possible >= 0.5)
		{
			ofstream outFile;
			//불러올때 \\두개해줘야함
			outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::app);
			outFile << "yellow" << " " << *point_y << " " << *point_x << " " << temp.y << " " << temp.x << " " << temp.radius << "\n";
			outFile.close();
		}
		if (red_possible >= 0.3)
		{
			ofstream outFile;
			//불러올때 \\두개해줘야함
			outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::app);
			outFile << "red"+to_string(red_cnt) << " " << temp.y << " " << temp.x << " " << temp.y << " " << temp.x << " " << temp.radius << "\n";
			red_cnt++;
			outFile.close();
		}
		if (white_possible >= 0.5)
		{
			ofstream outFile;
			//불러올때 \\두개해줘야함
			outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::app);
			outFile << "white" << " " << temp.y << " " << temp.x << " " << temp.y << " " << temp.x << " " << temp.radius << "\n";
			outFile.close();
		}
	}
	delete input_red;
	delete input_green;
	delete input_blue;
	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


