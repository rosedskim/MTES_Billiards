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
#include "userGetFileName.h"
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
int CDECL userGetFileName(KScString* outputSequenceImg,KScString* outputBackgroundImg)
{
// ��ó�� /////////////////////////////////////////////////////////////////////
	outputSequenceImg->Alloc(256);
	outputBackgroundImg->Alloc(256);

	//��� ȣ��
	std::string filepath = "C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\capture\\";

	std::string filename = "background.jpg";

	std::string str = filepath + filename;

	strcpy((char*)outputSequenceImg->GetBuffer(), filepath.c_str());	//������ �ִ� ���
	strcpy((char*)outputBackgroundImg->GetBuffer(), str.c_str());		//����

	return TRUE;

	//Sleep(300);
    // �Է� ���� �ڷ� ���� �˻�.

    // ��� ���� �ڷ� ���� �˻�.

    // �Է� ���� �Ҵ� ���� �˻�.

	// ��� ���� �Ҵ� ���� �˻�.

// ���� ó�� �κ� /////////////////////////////////////////////////////////////

	// �� ���� �Լ��� ���� ó�� �ڵ带 �����մϴ�.

// ��ó�� /////////////////////////////////////////////////////////////////////

	return TRUE;
}

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


