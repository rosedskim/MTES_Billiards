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
//크기 넉넉하게 500으로 잡음
bool check[1500][800];	//labeling 체크
vector<vector<item>> v;	//라벨링 개수

bool cmp(vector<item> v1, vector<item> v2)
{
	if (v1.size() > v2.size())
	{
		return true;
	}
	return false;
}
//사진 크기 범위에 있는 경우만 한다.
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
//비율 줘서  점 구하기
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
int CDECL userLabelingCalc(KScScalarImage2dUint8* input,KScScalarImage2dUint8* output,int* point_y,int* point_x)
{
	dx = input->GetXSize();
	dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	KSdUint8 **inputArray = input->Get2dArray();		//라벨링 전 입력 영상
	KSdUint8 **outputArray = output->Get2dArray();	//라벨링된 출력 영상

	//라벨링 된것들 넣기
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
					//오른쪽
					if (isRange(y, x + 1))
					{
						if (inputArray[y][x + 1] == 255 && check[y][x + 1] == false)
						{
							temp.push_back({ y,x + 1 });
							q.push({ y,x + 1 });
							check[y][x + 1] = true;
						}
					}
					//아래쪽
					if (isRange(y + 1, x))
					{
						if (inputArray[y + 1][x] == 255 && check[y + 1][x] == false)
						{
							temp.push_back({ y + 1,x });
							q.push({ y + 1,x });
							check[y + 1][x] = true;
						}
					}
					//왼쪽
					if (isRange(y, x - 1))
					{
						if (inputArray[y][x - 1] == 255 && check[y][x - 1] == false)
						{
							temp.push_back({ y,x - 1 });
							q.push({ y,x - 1 });
							check[y][x - 1] = true;
						}
					}
					//위쪽
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
	//라벨 크기 순서대로 정렬
	sort(v.begin(), v.end(), cmp);

	for (int i = 0; i < v[0].size(); i++)
	{
		int y = v[0][i].y;
		int x = v[0][i].x;
		outputArray[y][x] = 255;
	}

	//구별한 거에서 최대 최소좌표 구하기
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
	//최대 최소 인 점 구하기
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
	//point에서 각 도 늘려가면서 최대길이인거 구하기 
	for (int i = 0; i < point.size(); i++)
	{
		int temp = make(point[i].y, point[i].x);
		//최대개수가 많은때의 그 점을 당구 큐의 point로 잡는다
		if (_max < temp)
		{
			index_y = point[i].y;
			index_x = point[i].x;
			_max = temp;
		}
	}
	
	//지점에서 노란공중심 -> 치는 기울기
	*point_y = index_y;
	*point_x = index_x;
	//

	return TRUE;
}
//point 들어왔을때 각도 1도식 계산해서 제일 큰 길이 반환 
int make(int y, int x)
{
	int _max = 0;
	int index_y, index_x;
	//x 가 min_x인경우 -> 아래방향 180도
	//직선 방정식세우는데 좌표계가 달라서 위로 대칭이동시키고 생각한다.
	if (x == min_x)
	{
		int cnt = 0;
		//(i~,min_x) 일일이 검사
		for (int i = min_y; i <= max_y; i++)
		{
			//check배열에 이미 라벨링된거 처리되어있으니 check배열에서 255값 찾으면된다.
			cnt = checkCount(y, x, i, min_x);
			//최대개수 찾기
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
	//x가 max_x인경우 -> 위방향 180도
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
	//y가 min_y인경우 -> 오른방향 180도
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
	//y가 max_y인경우 -> 왼쪽방향 180도
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
// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


