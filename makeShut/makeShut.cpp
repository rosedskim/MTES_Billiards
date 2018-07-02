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
#include "makeShut.h"

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
int CDECL makeShut(KScRgbImage2d* input,KScRgbImage2d* output)
{
	int dx = input->GetXSize();
	int dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

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

	//output 관련
	//RGB 분리
	KScScalarImage2dUint8 *outputRed = new KScScalarImage2dUint8;
	KScScalarImage2dUint8 *outputGreen = new KScScalarImage2dUint8;
	KScScalarImage2dUint8 *outputBlue = new KScScalarImage2dUint8;
	outputRed->Free();
	outputRed->Alloc(dx, dy);
	outputGreen->Free();
	outputGreen->Alloc(dx, dy);
	outputBlue->Free();
	outputBlue->Alloc(dx, dy);
	output->SplitAllPlane(outputRed, outputGreen, outputBlue);
	//RGB 값 배열
	KSdUint8 **outputRedArray = outputRed->Get2dArray();
	KSdUint8 **outputGreenArray = outputGreen->Get2dArray();
	KSdUint8 **outputBlueArray = outputBlue->Get2dArray();

	for (int i = 0; i < dy; i++)
	{
		for (int j = 0; j < dx; j++)
		{
			if (273 <= i && i <= 310 && 880 <= j && j <= 925)
			{
				outputRedArray[i][j] = inputRedArray[i - 60][j - 60];
				outputGreenArray[i][j] = inputGreenArray[i - 60][j - 60];
				outputBlueArray[i][j] = inputBlueArray[i - 60][j - 60];
			}
			else if (324 <= i && i <= 356 && 888 <= j && j <= 920)
			{
				outputRedArray[i][j] = inputRedArray[i - 60][j - 60];
				outputGreenArray[i][j] = inputGreenArray[i - 60][j - 60];
				outputBlueArray[i][j] = inputBlueArray[i - 60][j - 60];
			}
			else if (330 <= i && i <= 364 && 372 <= j && j <= 406)
			{
				outputRedArray[i][j] = inputRedArray[i - 60][j - 60];
				outputGreenArray[i][j] = inputGreenArray[i - 60][j - 60];
				outputBlueArray[i][j] = inputBlueArray[i - 60][j - 60];
			}
			else if (332 <= i && i <= 369 && 226 <= j && j <= 264)
			{
				outputRedArray[i][j] = inputRedArray[i - 60][j - 60];
				outputGreenArray[i][j] = inputGreenArray[i - 60][j - 60];
				outputBlueArray[i][j] = inputBlueArray[i - 60][j - 60];
			}
			else
			{
				outputRedArray[i][j] = inputRedArray[i][j];
				outputGreenArray[i][j] = inputGreenArray[i][j];
				outputBlueArray[i][j] = inputBlueArray[i][j];
			}
		}
	}
	output->MergeAllPlane(outputRed, outputGreen, outputBlue);

	delete inputRedArray;
	delete inputGreenArray;
	delete inputBlueArray;
	delete outputRedArray;
	delete outputGreenArray;
	delete outputBlueArray;
	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


