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
#include <cmath>
#include "userSubtractImage.h"

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
int CDECL userSubtractImage(KScRgbImage2d* background,KScRgbImage2d* input,KScRgbImage2d* output)
{
	int back_dx = background->GetXSize();
	int back_dy = background->GetYSize();
	int input_dx = input->GetXSize();
	int input_dy = input->GetYSize();
	output->Free();
	output->Alloc(input_dx, input_dy);

	//��׶��� �̹����� ���� R,G,B ����
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

	//input �̹����� ���� R,G,B ����
	KScScalarImage2dUint8 *input_red = new KScScalarImage2dUint8;
	input_red->Free();
	input_red->Alloc(input_dx, input_dy);
	KScScalarImage2dUint8 *input_green = new KScScalarImage2dUint8;
	input_green->Free();
	input_green->Alloc(input_dx, input_dy);
	KScScalarImage2dUint8 *input_blue = new KScScalarImage2dUint8;
	input_blue->Free();
	input_blue->Alloc(input_dx, input_dy);

	input->SplitAllPlane(input_red, input_green, input_blue);
	KSdUint8 **inputRedArray = input_red->Get2dArray();
	KSdUint8 **inputGreenArray = input_green->Get2dArray();
	KSdUint8 **inputBlueArray = input_blue->Get2dArray();


	//output �̹����� ���� R,G,B ����
	KScScalarImage2dUint8 *output_red = new KScScalarImage2dUint8;
	output_red->Free();
	output_red->Alloc(input_dx, input_dy);
	KScScalarImage2dUint8 *output_green = new KScScalarImage2dUint8;
	output_green->Free();
	output_green->Alloc(input_dx, input_dy);
	KScScalarImage2dUint8 *output_blue = new KScScalarImage2dUint8;
	output_blue->Free();
	output_blue->Alloc(input_dx, input_dy);

	output->SplitAllPlane(output_red, output_green, output_blue);
	KSdUint8 **outputRedArray = output_red->Get2dArray();
	KSdUint8 **outputGreenArray = output_green->Get2dArray();
	KSdUint8 **outputBlueArray = output_blue->Get2dArray();
	
	//���� ������ �дµ� ���� �̹����� �ȳ��´�!!!
	//->Alloc �Ҷ� ũ�� �ο��ѰŶ� RGB ũ��� ���� �ؾߵȴ�.!!!!!!!!!!!
	bool red_check = false;
	bool green_check = false;
	bool blue_check = false;
	for (int i = 0; i < back_dy; i++)
	{
		for (int j = 0; j < back_dx; j++)
		{
			red_check = false;
			green_check = false;
			blue_check = false;
			if (i == 304 && j == 804)
			{
				int a = 0;
				a++;
			}

			int red_diff = backRedArray[i][j] - inputRedArray[i][j];
			int green_diff = backGreenArray[i][j] - inputGreenArray[i][j];
			int blue_diff = backBlueArray[i][j] - inputBlueArray[i][j];
			
			
			/*
			if (-30 <= red_diff && red_diff <= 30)
			{
				outputRedArray[i][j] = (unsigned char)abs(red_diff);
			}
			else
			{
				outputRedArray[i][j] = inputRedArray[i][j];
			}
			if (-30 <= green_diff && green_diff <= 30)
			{
				outputGreenArray[i][j] = (unsigned char)abs(green_diff);
			}
			else
			{
				outputGreenArray[i][j] = inputGreenArray[i][j];
			}
			//����̶� ������� chec=true;
			if (-30 <= blue_diff && blue_diff <= 30)
			{
				outputBlueArray[i][j] = (unsigned char)abs(blue_diff);
			}
			else
			{
				outputBlueArray[i][j] = inputBlueArray[i][j];
			}
			*/


			
			//���������� +,-40�� ��� ���������� �������� ����
			//���������ȿ� �������� ���� ���ϴ°Ծƴϰ� input�� ���� �״�� output����
			if (-40 <= red_diff && red_diff <= 40)
			{
				red_check = true;
				//outputRedArray[i][j] = (unsigned char)abs(red_diff);
			}

			if (-40 <= green_diff && green_diff <= 40)
			{
				green_check = true;
				//outputGreenArray[i][j] = (unsigned char)abs(green_diff);
			}
			//����̶� ������� chec=true;
			if (-40 <= blue_diff && blue_diff <= 40)
			{
				blue_check = true;
				//outputBlueArray[i][j] = (unsigned char)abs(blue_diff);
			}
			//�̵��ϴ� ��ü�� ���°��
			if (red_check && green_check && blue_check)
			{
				outputRedArray[i][j] = 0;
				outputGreenArray[i][j] = 0;
				outputBlueArray[i][j] = 0;
				//outputRedArray[i][j] = (unsigned char)abs(red_diff);
				//outputGreenArray[i][j] = (unsigned char)abs(green_diff);
				//outputBlueArray[i][j] = (unsigned char)abs(blue_diff);
			}
			//�̵��ϴ� ��ü�� ���
			else
			{
				outputRedArray[i][j] = inputRedArray[i][j];
				outputGreenArray[i][j] = inputGreenArray[i][j];
				outputBlueArray[i][j] = inputBlueArray[i][j];
			}
			
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

// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


