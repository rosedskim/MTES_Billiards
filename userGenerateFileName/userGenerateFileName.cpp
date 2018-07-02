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
#include "userGenerateFileName.h"
#include <string>

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
int CDECL userGenerateFileName(KScString* in,KScString* out,int* num)
{
	//출력은 안에서 작업하기때문에 동적할당 해줘야됨
	out->Alloc(256);

	std::string filepath = (char*)in->GetBuffer();

	std::string filename;
	std::string number;

	number = std::to_string(*num);

	if (number.length() == 1)
		filename = "img000" + number;
	else if (number.length() == 2)
		filename = "img00" + number;
	else if (number.length() == 3)
		filename = "img0" + number;
	else if (number.length() == 4)
		filename = "img" + number;

	filename = filename + ".jpg";

	std::string str = filepath + filename;

	strcpy((char*)out->GetBuffer(), str.c_str());

	//Sleep(300);

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


