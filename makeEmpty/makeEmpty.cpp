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
#include "makeEmpty.h"

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
int CDECL makeEmpty(KScRgbImage2d* input1,KScRgbImage2d* input2,KScRgbImage2d* output)
{
	int dx = input1->GetXSize();
	int dy = input1->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	KScScalarImage2dUint8 * i1_red = new KScScalarImage2dUint8;
	i1_red->Free();
	i1_red->Alloc(dx, dy);
	KScScalarImage2dUint8 * i1_green = new KScScalarImage2dUint8;
	i1_green->Free();
	i1_green->Alloc(dx, dy);
	KScScalarImage2dUint8 * i1_blue = new KScScalarImage2dUint8;
	i1_blue->Free();
	i1_blue->Alloc(dx, dy);

	KScScalarImage2dUint8 * i2_red = new KScScalarImage2dUint8;
	i2_red->Free();
	i2_red->Alloc(dx, dy);
	KScScalarImage2dUint8 * i2_green = new KScScalarImage2dUint8;
	i2_green->Free();
	i2_green->Alloc(dx, dy);
	KScScalarImage2dUint8 * i2_blue = new KScScalarImage2dUint8;
	i2_blue->Free();
	i2_blue->Alloc(dx, dy);

	KScScalarImage2dUint8 * o_red = new KScScalarImage2dUint8;
	o_red->Free();
	o_red->Alloc(dx, dy);
	KScScalarImage2dUint8 * o_green = new KScScalarImage2dUint8;
	o_green->Free();
	o_green->Alloc(dx, dy);
	KScScalarImage2dUint8 * o_blue = new KScScalarImage2dUint8;
	o_blue->Free();
	o_blue->Alloc(dx, dy);

	input1->SplitAllPlane(i1_red, i1_green, i1_blue);
	KSdUint8 **i1_redArr = i1_red->Get2dArray();
	KSdUint8 **i1_greenArr = i1_green->Get2dArray();
	KSdUint8 **i1_blueArr = i1_blue->Get2dArray();

	input2->SplitAllPlane(i2_red, i2_green, i2_blue);
	KSdUint8 **i2_redArr = i2_red->Get2dArray();
	KSdUint8 **i2_greenArr = i2_green->Get2dArray();
	KSdUint8 **i2_blueArr = i2_blue->Get2dArray();

	output->SplitAllPlane(o_red, o_blue, o_green);
	KSdUint8 **o_redArr = o_red->Get2dArray();
	KSdUint8 **o_greenArr = o_green->Get2dArray();
	KSdUint8 **o_blueArr = o_blue->Get2dArray();

	for (int i = 0; i < dy; i++)
	{
		for (int j = 0; j < dx; j++)
		{
			if (273 <= i && i <= 310 && 880 <= j && j <= 925)
			{
				o_redArr[i][j] = i1_redArr[i - 60][j - 60];
				o_greenArr[i][j] = i1_greenArr[i - 60][j - 60];
				o_blueArr[i][j] = i1_blueArr[i - 60][j - 60];
			}
			else if (324 <= i && i <= 356 && 888 <= j && j <= 920)
			{
				o_redArr[i][j] = i1_redArr[i - 60][j - 60];
				o_greenArr[i][j] = i1_greenArr[i - 60][j - 60];
				o_blueArr[i][j] = i1_blueArr[i - 60][j - 60];
			}
			else if (330 <= i && i <= 364 && 372 <= j && j <= 406)
			{
				o_redArr[i][j] = i1_redArr[i - 60][j - 60];
				o_greenArr[i][j] = i1_greenArr[i - 60][j - 60];
				o_blueArr[i][j] = i1_blueArr[i - 60][j - 60];
			}
			else if (332 <= i && i <= 369 && 226 <= j && j <= 264)
			{
				o_redArr[i][j] = i1_redArr[i - 60][j - 60];
				o_greenArr[i][j] = i1_greenArr[i - 60][j - 60];
				o_blueArr[i][j] = i1_blueArr[i - 60][j - 60];
			}
			else if (219 <= i && i <= 425 && 940 <= j && j <= 1160)
			{
				o_redArr[i][j] = i2_redArr[i][j];
				o_greenArr[i][j] = i2_greenArr[i][j];
				o_blueArr[i][j] = i2_blueArr[i][j];
			}
			else
			{
				o_redArr[i][j] = i1_redArr[i][j];
				o_greenArr[i][j] = i1_greenArr[i][j];
				o_blueArr[i][j] = i1_blueArr[i][j];
			}
		}
	}
	input1->MergeAllPlane(i1_red, i1_green, i1_blue);
	input1->MergeAllPlane(i2_red, i2_green, i2_blue);
	output->MergeAllPlane(o_red, o_green, o_blue);

	delete i1_red;
	delete i1_blue;
	delete i1_green;
	delete i2_red;
	delete i2_blue;
	delete i2_green;
	delete o_red;
	delete o_blue;
	delete o_green;
	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


