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
#include "userPrintRoute.h"
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <KScOpenCvUtils.h>
using namespace cv;
using namespace std;
// DLL을 만들기 위한 부분
BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
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
int CDECL userPrintRoute(KScRgbImage2d* input,KScRgbImage2d* output)
{
	int dx = input->GetXSize();
	int dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	vector<pair<int, int>> route;

	ifstream inFile;	//std 해줘야됨
	inFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\point.txt");
	if (!inFile.is_open())
	{
		cout << "error" << "\n";
		return -1;
	}
	while (!inFile.eof())
	{
		int y, x;
		inFile >> y >> x;
		route.push_back({ y,x });
	}
	inFile.close();


	//input 이미지에 대한 R,G,B 색상
	KScScalarImage2dUint8 *input_red = new KScScalarImage2dUint8;
	input_red->Alloc(dx, dy);
	KScScalarImage2dUint8 *input_green = new KScScalarImage2dUint8;
	input_green->Alloc(dx, dy);
	KScScalarImage2dUint8 *input_blue = new KScScalarImage2dUint8;
	input_blue->Alloc(dx, dy);

	input->SplitAllPlane(input_red, input_green, input_blue);
	KSdUint8 **inputRedArray = input_red->Get2dArray();
	KSdUint8 **inputGreenArray = input_green->Get2dArray();
	KSdUint8 **inputBlueArray = input_blue->Get2dArray();

	/*
	//output 관련
	//RGB 분리
	KScScalarImage2dUint8 *outputRed = new KScScalarImage2dUint8;
	KScScalarImage2dUint8 *outputGreen = new KScScalarImage2dUint8;
	KScScalarImage2dUint8 *outputBlue = new KScScalarImage2dUint8;
	outputRed->Alloc(dx, dy);
	outputGreen->Alloc(dx, dy);
	outputBlue->Alloc(dx, dy);
	output->SplitAllPlane(outputRed, outputGreen, outputBlue);
	//RGB 값 배열
	KSdUint8 **outputRedArray = outputRed->Get2dArray();
	KSdUint8 **outputGreenArray = outputGreen->Get2dArray();
	KSdUint8 **outputBlueArray = outputBlue->Get2dArray();
	
	//원본 이미지 출력
	for (int i = 0; i < dy; i++)
	{
		for (int j = 0; j < dx; j++)
		{
			outputRedArray[i][j] = inputRedArray[i][j];
			outputGreenArray[i][j] = inputGreenArray[i][j];
			outputBlueArray[i][j] = inputBlueArray[i][j];
		}
	}
	//경로 출력
	for (int i = 0; i < route.size(); i++)
	{
		int y = route[i].first;
		int x = route[i].second;
		outputRedArray[y][x] = 255;
		outputGreenArray[y][x] = 0;
		outputBlueArray[y][x] = 0;
	}
	output->MergeAllPlane(outputRed, outputGreen, outputBlue);
	*/


	Mat src;
	src = KScRgbImage2dToMat(input);
	for (int i = 0; i < route.size() - 1; i++)
	{
		line(src, Point(route[i].second, route[i].first), Point(route[i + 1].second, route[i + 1].first), Scalar(0, 0, 255), 2);
	}
	MatToKScRgbImage2d(src, output);

	delete input_red;
	delete input_green;
	delete input_blue;

// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


