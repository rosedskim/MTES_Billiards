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
#include <cmath>
#include "userHistSpecification.h"

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
int CDECL userHistSpecification(KScRgbImage2d* background,KScRgbImage2d* input,KScRgbImage2d* output)
{
	int back_dx = background->GetXSize();
	int back_dy = background->GetYSize();
	int dx = input->GetXSize();
	int dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	//백그라운드 이미지에 대한 R,G,B 색상
	KScScalarImage2dUint8 *back_red = new KScScalarImage2dUint8;
	back_red->Free();
	back_red->Alloc(back_dx, back_dy);
	KScScalarImage2dUint8 *back_green = new KScScalarImage2dUint8;
	back_green->Free();
	back_green->Alloc(back_dx, back_dy);
	KScScalarImage2dUint8 *back_blue = new KScScalarImage2dUint8;
	back_blue->Free();
	back_blue->Alloc(back_dx, back_dy);

	background->SplitAllPlane(back_red, back_green, back_blue);
	KSdUint8 **backRedArray = back_red->Get2dArray();
	KSdUint8 **backGreenArray = back_green->Get2dArray();
	KSdUint8 **backBlueArray = back_blue->Get2dArray();

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

	unsigned long backRedHist[256];
	unsigned long inputRedHist[256];
	unsigned long sum_backRedHist[256];
	unsigned long sum_inputRedHist[256];

	unsigned long backGreenHist[256];
	unsigned long inputGreenHist[256];
	unsigned long sum_backGreenHist[256];
	unsigned long sum_inputGreenHist[256];

	unsigned long backBlueHist[256];
	unsigned long inputBlueHist[256];
	unsigned long sum_backBlueHist[256];
	unsigned long sum_inputBlueHist[256];

	//히스토그램 배열 초기화
	memset(backRedHist, 0, sizeof(backRedHist));
	memset(inputRedHist, 0, sizeof(inputRedHist));
	memset(backGreenHist, 0, sizeof(backGreenHist));
	memset(inputGreenHist, 0, sizeof(inputGreenHist));
	memset(backBlueHist, 0, sizeof(backBlueHist));
	memset(inputBlueHist, 0, sizeof(inputBlueHist));
	
	//백그라운드, 입력이미지 R,G,B 각각의 히스토그램 값 계산
	for (int i = 0; i < back_dy; i++)
	{
		for (int j = 0; j < back_dx; j++)
		{
			if (i == 474 && j == 321)
			{
				int a = 0;
				a++;
			}
			int back_red_value = backRedArray[i][j];
			int input_red_value = inputRedArray[i][j];

			int back_green_value = backGreenArray[i][j];
			int input_green_value = inputGreenArray[i][j];

			int back_blue_value = backBlueArray[i][j];
			int input_blue_value = inputBlueArray[i][j];

			backRedHist[back_red_value]++;
			inputRedHist[input_red_value]++;

			backGreenHist[back_green_value]++;
			inputGreenHist[input_green_value]++;

			backBlueHist[back_blue_value]++;
			inputBlueHist[input_blue_value]++;
		}
	}

	//배경이미지 누적 히스토그램 계산
	int back_red_sum = 0;
	int back_green_sum = 0;
	int back_blue_sum = 0;
	for (int i = 0; i < 256; i++)
	{
		back_red_sum += backRedHist[i];
		sum_backRedHist[i] = back_red_sum;

		back_green_sum += backGreenHist[i];
		sum_backGreenHist[i] = back_green_sum;

		back_blue_sum += backBlueHist[i];
		sum_backBlueHist[i] = back_blue_sum;
	}
	int input_red_sum = 0;
	int input_green_sum = 0;
	int input_blue_sum = 0;
	//입력 이미지 누적 히스토그램 계산
	for (int i = 0; i < 256; i++)
	{
		input_red_sum += inputRedHist[i];
		sum_inputRedHist[i] = input_red_sum;

		input_green_sum += inputGreenHist[i];
		sum_inputGreenHist[i] = input_green_sum;

		input_blue_sum += inputBlueHist[i];
		sum_inputBlueHist[i] = input_blue_sum;
	}

	//R 누적 히스토그램 명세화
	int new_red_arr[256];	//R에 관한 LUT
	int new_green_arr[256];
	int new_blue_arr[256];
	int min_red_value = 100000;
	int red_index = 0;
	int min_green_value = 100000;
	int green_index = 0;
	int min_blue_value = 100000;
	int blue_index = 0;
	for (int i = 0; i < 256; i++)
	{
		min_red_value = 100000;
		red_index = 0;
		min_green_value = 100000;
		green_index = 0;
		min_blue_value = 100000;
		blue_index = 0;
		for (int j = 0; j < 256; j++)
		{
			int red_diff = (sum_backRedHist[i] - sum_inputRedHist[j]);
			int green_diff = (sum_backGreenHist[i] - sum_inputGreenHist[j]);
			int blue_diff = (sum_backBlueHist[i] - sum_inputBlueHist[j]);

			if (min_red_value > abs(red_diff))
			{
				min_red_value = abs(red_diff);
				red_index = j;
			}
			if (min_green_value > abs(green_diff))
			{
				min_green_value = abs(green_diff);
				green_index = j;
			}
			if (min_blue_value > abs(blue_diff))
			{
				min_blue_value = abs(blue_diff);
				blue_index = j;
			}
		}
		new_red_arr[i] = red_index;
		new_green_arr[i] = green_index;
		new_blue_arr[i] = blue_index;
	}

	//output 이미지에 대한 R,G,B 색상
	KScScalarImage2dUint8 *output_red = new KScScalarImage2dUint8;
	output_red->Alloc(dx, dy);
	KScScalarImage2dUint8 *output_green = new KScScalarImage2dUint8;
	output_green->Alloc(dx, dy);
	KScScalarImage2dUint8 *output_blue = new KScScalarImage2dUint8;
	output_blue->Alloc(dx, dy);

	output->SplitAllPlane(output_red, output_green, output_blue);
	KSdUint8 **outputRedArray = output_red->Get2dArray();
	KSdUint8 **outputGreenArray = output_green->Get2dArray();
	KSdUint8 **outputBlueArray = output_blue->Get2dArray();

	//매칭시키기
	for (int i = 0; i < back_dy; i++)
	{
		for (int j = 0; j < back_dx; j++)
		{
			outputRedArray[i][j] = new_red_arr[inputRedArray[i][j]];
			outputGreenArray[i][j] = new_green_arr[inputGreenArray[i][j]];
			outputBlueArray[i][j] = new_blue_arr[inputBlueArray[i][j]];
		}
	}

	output->MergeAllPlane(output_red, output_green, output_blue);


	delete back_red;
	delete back_green;
	delete back_blue;
	delete input_red;
	delete input_green;
	delete input_blue;
	delete output_red;
	delete output_green;
	delete output_blue;

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


