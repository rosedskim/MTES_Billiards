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
#include "userGetFileName.h"
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
int CDECL userGetFileName(KScString* outputSequenceImg,KScString* outputBackgroundImg)
{
// 전처리 /////////////////////////////////////////////////////////////////////
	outputSequenceImg->Alloc(256);
	outputBackgroundImg->Alloc(256);

	//경로 호출
	std::string filepath = "C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\capture\\";

	std::string filename = "background.jpg";

	std::string str = filepath + filename;

	strcpy((char*)outputSequenceImg->GetBuffer(), filepath.c_str());	//파일이 있는 경로
	strcpy((char*)outputBackgroundImg->GetBuffer(), str.c_str());		//파일

	return TRUE;

	//Sleep(300);
    // 입력 버퍼 자료 형태 검사.

    // 출력 버퍼 자료 형태 검사.

    // 입력 버퍼 할당 여부 검사.

	// 출력 버퍼 할당 여부 검사.

// 실제 처리 부분 /////////////////////////////////////////////////////////////

	// 이 곳에 함수의 실제 처리 코드를 삽입합니다.

// 후처리 /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


