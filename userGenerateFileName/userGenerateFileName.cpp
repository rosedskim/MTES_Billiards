//////////////////////////////////////////////////////////////////////////
//
// �� ȭ���� �Լ� ��Ͻ� �ڵ����� ������ ������Ʈ�Դϴ�.
//
// ����ڰ� ������ ���� ���, Project�� Setting...�� ������ �ʿ��ϹǷ�,
//
// �̴� ������ '�Լ� �ۼ���'�� ���� �ٶ��ϴ�.
//
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "userGenerateFileName.h"
#include <string>

// DLL�� ����� ���� �κ�
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

// �Լ��� ���� �κ�
int CDECL userGenerateFileName(KScString* in,KScString* out,int* num)
{
	//����� �ȿ��� �۾��ϱ⶧���� �����Ҵ� ����ߵ�
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

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


