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
#include "userLabelingCalc.h"
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

struct item {
	int y;
	int x;
};

int min_y = 2000;
int max_y = 0;
int min_x = 2000;
int max_x = 0;
int dx, dy;
//ũ�� �˳��ϰ� 500���� ����
bool check[1500][800];	//labeling üũ
vector<vector<item>> v;	//�󺧸� ����

bool cmp(vector<item> v1, vector<item> v2)
{
	if (v1.size() > v2.size())
	{
		return true;
	}
	return false;
}
//���� ũ�� ������ �ִ� ��츸 �Ѵ�.
bool isRange(int y, int x)
{
	if (0 < y && y < dy && 0 < x && x < dx)
	{
		return true;
	}
	return false;
}
int make(int y, int x);
double dist(int y1, int x1, int y2, int x2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}
//���� �༭  �� ���ϱ�
pair<double, double> make_point(int y1, int x1, int y2, int x2, int ratio1, int ratio2)
{
	double ratio = ratio1 + ratio2;
	return{ y1*(ratio2 / ratio) + y2*(ratio1 / ratio),x1*(ratio2 / ratio) + x2*(ratio1 / ratio) };
}
int checkCount(int y, int x, int _y, int _x)
{
	int ret = 0;
	double d = dist(y, x, _y, _x);
	int _d = (int)d;
	for (int j = 0; j < _d; j++)
	{
		pair<double, double> p = make_point(y, x, _y, _x, j, _d - j);
		int real_y = (int)(p.first + 0.5);
		int real_x = (int)(p.second + 0.5);
		if (check[real_y][real_x] == true)
		{
			ret++;
		}
	}
	return ret;
}
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
int CDECL userLabelingCalc(KScScalarImage2dUint8* input,KScScalarImage2dUint8* output,int* point_y,int* point_x)
{
	dx = input->GetXSize();
	dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	KSdUint8 **inputArray = input->Get2dArray();		//�󺧸� �� �Է� ����
	KSdUint8 **outputArray = output->Get2dArray();	//�󺧸��� ��� ����

	//�󺧸� �Ȱ͵� �ֱ�
	for (int i = 0; i < dy - 1; i++)
	{
		for (int j = 0; j < dx - 1; j++)
		{
			if (i == 282 && j == 955)
			{
				int a = 0;
				a++;
			}
			outputArray[i][j] = 0;
			if (inputArray[i][j] == 255 && check[i][j] == false)
			{
				vector<item> temp;
				queue<item> q;
				q.push({ i,j });
				temp.push_back({ i,j });
				check[i][j] = true;
				while (!q.empty())
				{
					int y = q.front().y;
					int x = q.front().x;
					q.pop();
					//������
					if (isRange(y, x + 1))
					{
						if (inputArray[y][x + 1] == 255 && check[y][x + 1] == false)
						{
							temp.push_back({ y,x + 1 });
							q.push({ y,x + 1 });
							check[y][x + 1] = true;
						}
					}
					//�Ʒ���
					if (isRange(y + 1, x))
					{
						if (inputArray[y + 1][x] == 255 && check[y + 1][x] == false)
						{
							temp.push_back({ y + 1,x });
							q.push({ y + 1,x });
							check[y + 1][x] = true;
						}
					}
					//����
					if (isRange(y, x - 1))
					{
						if (inputArray[y][x - 1] == 255 && check[y][x - 1] == false)
						{
							temp.push_back({ y,x - 1 });
							q.push({ y,x - 1 });
							check[y][x - 1] = true;
						}
					}
					//����
					if (isRange(y - 1, x))
					{
						if (inputArray[y - 1][x] == 255 && check[y - 1][x] == false)
						{
							temp.push_back({ y - 1,x });
							q.push({ y - 1,x });
							check[y - 1][x] = true;
						}
					}
				}
				v.push_back(temp);
			}
		}
	}
	//�� ũ�� ������� ����
	sort(v.begin(), v.end(), cmp);

	for (int i = 0; i < v[0].size(); i++)
	{
		int y = v[0][i].y;
		int x = v[0][i].x;
		outputArray[y][x] = 255;
	}

	//������ �ſ��� �ִ� �ּ���ǥ ���ϱ�
	for (int i = 0; i < v[0].size(); i++)
	{
		if (min_y > v[0][i].y)
		{
			min_y = v[0][i].y;
		}
		if (max_y < v[0][i].y)
		{
			max_y = v[0][i].y;
		}
		if (min_x > v[0][i].x)
		{
			min_x = v[0][i].x;
		}
		if (max_x < v[0][i].x)
		{
			max_x = v[0][i].x;
		}
	}
	//�ִ� �ּ� �� �� ���ϱ�
	vector<item> point;
	for (int i = 0; i < v[0].size(); i++)
	{
		if (v[0][i].y == min_y)
		{
			point.push_back({ min_y,v[0][i].x });
		}
		if (v[0][i].y == max_y)
		{
			point.push_back({ max_y,v[0][i].x });
		}
		if (v[0][i].x == min_x)
		{
			point.push_back({ v[0][i].y, min_x });
		}
		if (v[0][i].x == max_x)
		{
			point.push_back({ v[0][i].y, max_x });
		}
	}
	int index_y, index_x = 0;
	int _max = 0;
	//point���� �� �� �÷����鼭 �ִ�����ΰ� ���ϱ� 
	for (int i = 0; i < point.size(); i++)
	{
		int temp = make(point[i].y, point[i].x);
		//�ִ밳���� �������� �� ���� �籸 ť�� point�� ��´�
		if (_max < temp)
		{
			index_y = point[i].y;
			index_x = point[i].x;
			_max = temp;
		}
	}
	
	//�������� ������߽� -> ġ�� ����
	*point_y = index_y;
	*point_x = index_x;
	//

	return TRUE;
}
//point �������� ���� 1���� ����ؼ� ���� ū ���� ��ȯ 
int make(int y, int x)
{
	int _max = 0;
	int index_y, index_x;
	//x �� min_x�ΰ�� -> �Ʒ����� 180��
	//���� �����ļ���µ� ��ǥ�谡 �޶� ���� ��Ī�̵���Ű�� �����Ѵ�.
	if (x == min_x)
	{
		int cnt = 0;
		//(i~,min_x) ������ �˻�
		for (int i = min_y; i <= max_y; i++)
		{
			//check�迭�� �̹� �󺧸��Ȱ� ó���Ǿ������� check�迭���� 255�� ã����ȴ�.
			cnt = checkCount(y, x, i, min_x);
			//�ִ밳�� ã��
			_max = max(_max, cnt);
		}
		//min_x~max_x
		for (int i = min_x; i <= max_x; i++)
		{
			cnt = checkCount(y, x, max_y, i);
			_max = max(_max, cnt);
		}
		//
		for (int i = min_y; i <= max_y; i++)
		{
			cnt = checkCount(y, x, i, max_x);
			_max = max(_max, cnt);
		}
	}
	//x�� max_x�ΰ�� -> ������ 180��
	if (x == max_x)
	{
		int cnt = 0;
		for (int i = min_y; i <= max_y; i++)
		{
			cnt = checkCount(y, x, i, min_x);
			_max = max(_max, cnt);
		}
		for (int i = min_x; i <= max_x; i++)
		{
			cnt = checkCount(y, x, min_y, i);
			_max = max(_max, cnt);
		}
		for (int i = min_y; i <= max_y; i++)
		{
			cnt = checkCount(y, x, i, max_x);
			_max = max(_max, cnt);
		}
	}
	//y�� min_y�ΰ�� -> �������� 180��
	if (y == min_y)
	{
		int cnt = 0;
		for (int i = min_x; i <= max_x; i++)
		{
			cnt = checkCount(y, x, min_y, i);
			_max = max(_max, cnt);
		}
		for (int i = min_y; i <= max_y; i++)
		{
			cnt = checkCount(y, x, i, max_x);
			_max = max(_max, cnt);
		}
		for (int i = min_x; i <= max_x; i++)
		{
			cnt = checkCount(y, x, max_y, i);
			_max = max(_max, cnt);
		}
	}
	//y�� max_y�ΰ�� -> ���ʹ��� 180��
	if (y == max_y)
	{
		int cnt = 0;
		for (int i = min_x; i <= max_x; i++)
		{
			cnt = checkCount(y, x, min_y, i);
			_max = max(_max, cnt);
		}
		for (int i = min_y; i <= max_y; i++)
		{
			cnt = checkCount(y, x, i, min_x);
			_max = max(_max, cnt);
		}
		for (int i = min_x; i <= max_x; i++)
		{
			cnt = checkCount(y, x, max_y, i);
			_max = max(_max, cnt);
		}
	}
	return _max;
}
// 2 �� �̻��� �Լ��� ������ ���, �Ʒ��� �������� �����մϴ�.


