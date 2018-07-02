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
#include "makeBackground.h"

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
int CDECL makeBackground(KScRgbImage2d* ref,KScRgbImage2d* input,KScRgbImage2d* output)
{
	int dx = input->GetXSize();
	int dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	KScScalarImage2dUint8 * r_red = new KScScalarImage2dUint8;
	r_red->Free();
	r_red->Alloc(dx, dy);
	KScScalarImage2dUint8 * r_green = new KScScalarImage2dUint8;
	r_green->Free();
	r_green->Alloc(dx, dy);
	KScScalarImage2dUint8 * r_blue = new KScScalarImage2dUint8;
	r_blue->Free();
	r_blue->Alloc(dx, dy);

	KScScalarImage2dUint8 * i_red = new KScScalarImage2dUint8;
	i_red->Free();
	i_red->Alloc(dx, dy);
	KScScalarImage2dUint8 * i_green = new KScScalarImage2dUint8;
	i_green->Free();
	i_green->Alloc(dx, dy);
	KScScalarImage2dUint8 * i_blue = new KScScalarImage2dUint8;
	i_blue->Free();
	i_blue->Alloc(dx, dy);

	KScScalarImage2dUint8 * o_red = new KScScalarImage2dUint8;
	o_red->Free();
	o_red->Alloc(dx, dy);
	KScScalarImage2dUint8 * o_green = new KScScalarImage2dUint8;
	o_green->Free();
	o_green->Alloc(dx, dy);
	KScScalarImage2dUint8 * o_blue = new KScScalarImage2dUint8;
	o_blue->Free();
	o_blue->Alloc(dx, dy);


	ref->SplitAllPlane(r_red, r_green, r_blue);
	KSdUint8 **r_redArr = r_red->Get2dArray();
	KSdUint8 **r_greenArr = r_green->Get2dArray();
	KSdUint8 **r_blueArr = r_blue->Get2dArray();

	input->SplitAllPlane(i_red, i_green, i_blue);
	KSdUint8 **i_redArr = i_red->Get2dArray();
	KSdUint8 **i_greenArr = i_green->Get2dArray();
	KSdUint8 **i_blueArr = i_blue->Get2dArray();

	output->SplitAllPlane(o_red, o_blue, o_green);
	KSdUint8 **o_redArr = o_red->Get2dArray();
	KSdUint8 **o_greenArr = o_green->Get2dArray();
	KSdUint8 **o_blueArr = o_blue->Get2dArray();
	
	for (int i = 0; i < dy; i++)
	{
		for (int j = 0; j < dx; j++)
		{
			if (640 <= i && i <= 719 && 50<=j && j<=1200)
			{
				o_redArr[i][j] = r_redArr[i][j];
				o_greenArr[i][j] = r_greenArr[i][j];
				o_blueArr[i][j] = r_blueArr[i][j];
			}
			else
			{
				o_redArr[i][j] = i_redArr[i][j];
				o_greenArr[i][j] = i_greenArr[i][j];
				o_blueArr[i][j] = i_blueArr[i][j];
			}
		}
	}
	output->MergeAllPlane(o_red, o_green, o_blue);
	/*
	//밑에 자막없애기
	for (int i = 640; i <= 719; i++)
	{
		for (int j = 50; j <= 1200; j++)
		{
			o_redArr[i][j] = r_redArr[i][j];
			o_greenArr[i][j] = r_greenArr[i][j];
			o_blueArr[i][j] = r_blueArr[i][j];
		}
	}

	ref->MergeAllPlane(r_red, r_green, r_blue);
	input->MergeAllPlane(i_red, i_green, i_blue);
	output->MergeAllPlane(o_red, o_green, o_blue);
	*/
	delete r_red;
	delete r_green;
	delete r_blue;
	delete i_red;
	delete i_green;
	delete i_blue;
	delete o_red;
	delete o_green;
	delete o_blue;

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


