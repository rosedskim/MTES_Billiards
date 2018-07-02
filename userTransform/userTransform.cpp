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
#include "userTransform.h"
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

bool yellowCheck, red1Check, red2Check, whiteCheck;

int edge_minX = 114;
int edge_maxX = 1165;
int edge_minY = 90;
int edge_maxY = 614;

struct circle {
	string color;
	int post_y;
	int post_x;
	int cur_y;
	int cur_x;
	int radius;
};
struct item {
	int  y1;
	int  x1;
	int  y2;
	int  x2;
	int type;
	int way;
};
struct info {
	int y;
	int x;
	int r_value;
	int g_value;
	int b_value;
};
//현재 색깔을 가지고있는 좌표들 다 저장
vector<info> yellow_point;
vector<info> red1_point;
vector<info> red2_point;
vector<info> white_point;
circle yellow, red1, red2, white;
double dist(int point_y, int point_x, int center_y, int center_x)
{
	int dist_y = (point_y - center_y);
	int dist_x = (point_x - center_x);
	return sqrt(dist_y*dist_y + dist_x*dist_x);
}
bool checkInRange(int y, int x, int radius, string color)
{
	if (color == "yellow")
	{
		int center_y = yellow.post_y;
		int center_x = yellow.post_x;
		if (dist(y, x, center_y, center_x) <= radius)
		{
			return true;
		}
		//범위 안에 없는경우
		else
		{
			return false;
		}
	}
	else if (color == "red1")
	{
		int center_y = red1.post_y;
		int center_x = red1.post_x;
		if (dist(y, x, center_y, center_x) <= radius)
		{
			return true;
		}
		//범위 안에 없는경우
		else
		{
			return false;
		}
	}
	else if (color == "red2")
	{
		int center_y = red2.post_y;
		int center_x = red2.post_x;
		if (dist(y, x, center_y, center_x) <= radius)
		{
			return true;
		}
		//범위 안에 없는경우
		else
		{
			return false;
		}
	}
	else
	{
		int center_y = white.post_y;
		int center_x = white.post_x;
		if (dist(y, x, center_y, center_x) <= radius)
		{
			return true;
		}
		//범위 안에 없는경우
		else
		{
			return false;
		}
	}
}
pair<int, int> makeNext(int post_y, int post_x, int cur_y, int cur_x)
{
	int next_y, next_x;
	next_y = 2 * cur_y - post_y;
	next_x = 2 * cur_x - post_x;
	return{ next_y, next_x };
}
//비율 줘서  점 구하기
pair<double, double> make_point(int y1, int x1, int y2, int x2, int ratio1, int ratio2)
{
	double ratio = ratio1 + ratio2;
	return{ y1*(ratio2 / ratio) + y2*(ratio1 / ratio),x1*(ratio2 / ratio) + x2*(ratio1 / ratio) };
}
double makeSize(int y1, int x1, int y2, int x2, int y3, int x3)
{
	return abs((y1*x2 + y2*x3 + y3*x1) - (y1*x3 + y3*x2 + y2*x1)) / 2;
}
pair<int, int> getOtherPoint(int  y1, int  x1, int  y2, int  x2, double length, int type, int way)
{
	vector<pair<int, int>> p;
	int min_x = x2 - yellow.radius;
	int max_x = x2 + yellow.radius;
	int min_y = y2 - yellow.radius;
	int max_y = y2 + yellow.radius;
	for (int i = min_y; i <= max_y; i++)
	{
		for (int j = min_x; j <= max_x; j++)
		{
			if (dist(y2, x2, i, j) <= (double)yellow.radius)
			{
				p.push_back({ i,j });
			}
		}
	}
	double _max = 0;
	vector<pair<int, int>> di;
	for (int i = 0; i < p.size(); i++)
	{
		double temp = makeSize(y1, x1, y2, x2, p[i].first, p[i].second);
		if (_max < temp)
		{
			_max = temp;
		}
	}
	for (int i = 0; i < p.size(); i++)
	{
		if (_max == makeSize(y1, x1, y2, x2, p[i].first, p[i].second))
		{
			di.push_back({ p[i].first,p[i].second });
		}
	}
	int index_y = 0, index_x = 0;
	//type과 way 구별
	//아래 왼쪽 -> 
	if (type == 1 && way == 2)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first < y2 && di[i].second > x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	//아래 오른쪽 -> 
	else if (type == 1 && way == 4)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first < y2 && di[i].second < x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	//왼쪽 아래
	else if (type == 2 && way == 1)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first < y2 && di[i].second > x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	//왼쪽 위
	else if (type == 2 && way == 3)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first > y2 && di[i].second > x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	//위 왼쪽
	else if (type == 3 && way == 2)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first > y2 && di[i].second > x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	//위 오른쪽
	else if (type == 3 && way == 4)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first > y2 && di[i].second < x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	//오른쪽 아래
	else if (type == 4 && way == 1)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first < y2 && di[i].second < x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	//오른쪽 위
	else if (type == 4 && way == 3)
	{
		for (int i = 0; i < di.size(); i++)
		{
			if (di[i].first > y2 && di[i].second < x2)
			{
				index_y = di[i].first;
				index_x = di[i].second;
			}
		}
	}
	int ret_y, ret_x = 0;
	ret_y = 2 * index_y - y2;
	ret_x = 2 * index_x - x2;
	return{ ret_y,ret_x };
}
item isYellowHit(string str)
{
	int post_y, post_x, cur_y, cur_x, radius;
	if (str == "yellow")
	{
		post_y = yellow.post_y;
		post_x = yellow.post_x;
		cur_y = yellow.cur_y;
		cur_x = yellow.cur_x;
		radius = yellow.radius;
	}
	else if (str == "red1")
	{
		post_y = red1.post_y;
		post_x = red1.post_x;
		cur_y = red1.cur_y;
		cur_x = red1.cur_x;
		radius = red1.radius;
	}
	else if (str == "red2")
	{
		post_y = red2.post_y;
		post_x = red2.post_x;
		cur_y = red2.cur_y;
		cur_x = red2.cur_x;
		radius = red2.radius;
	}
	else
	{
		post_y = white.post_y;
		post_x = white.post_x;
		cur_y = white.cur_y;
		cur_x = white.cur_x;
		radius = white.radius;
	}
	double d = dist(post_y, post_x, cur_y, cur_x);
	int _d = (int)d;
	for (int i = 1; i < _d; i++)
	{
		pair<double, double> p = make_point(post_y, post_x, cur_y, cur_x, i, _d - i);
		int real_y = (int)(p.first + 0.5);
		int real_x = (int)(p.second + 0.5);
		double temp = dist(real_y, real_x, yellow.cur_y, yellow.cur_x) - (radius + yellow.radius);
		double gradient1 = (double)(real_x - yellow.cur_x) / (real_y - yellow.cur_y);
		double gradient2 = (double)(post_x - cur_x) / (post_y - cur_y);
		if (-5 <= temp && temp <= 5)
		{
			//y1,x1,y2,x2 type way
			if (yellow.cur_y > real_y && yellow.cur_x < real_x)	//어짜피 gradient1 < 0인경우
			{
				if (gradient2 > 0)
				{
					return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 4,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 4,1 };
					}
					else
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 3,2 };
					}
				}
			}
			else if (yellow.cur_y < real_y && yellow.cur_x < real_x)	//gradient 1이 양수인경우밖에없음
			{
				if (gradient2 < 0)
				{
					return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 4,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 1,2 };
					}
					else
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 4,3 };
					}
				}
			}
			else if (yellow.cur_y > real_y && yellow.cur_x > real_x)	//gradient1이 양수
			{
				if (gradient2 < 0)
				{
					return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 2,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 3,4 };
					}
					else
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 2,1 };
					}
				}
			}
			else if (yellow.cur_y < real_y && yellow.cur_x > real_x)	//gradient1이 음수
			{
				if (gradient2 > 0)
				{
					return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 2,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 2,3 };
					}
					else
					{
						return{ yellow.cur_y, yellow.cur_x,real_y, real_x, 1,4 };
					}
				}
			}
		}
	}
	return{ 0,0,0,0,0 };
}
item isRed1Hit(string str)
{
	int post_y, post_x, cur_y, cur_x, radius;
	if (str == "yellow")
	{
		post_y = yellow.post_y;
		post_x = yellow.post_x;
		cur_y = yellow.cur_y;
		cur_x = yellow.cur_x;
		radius = yellow.radius;
	}
	else if (str == "red1")
	{
		post_y = red1.post_y;
		post_x = red1.post_x;
		cur_y = red1.cur_y;
		cur_x = red1.cur_x;
		radius = red1.radius;
	}
	else if (str == "red2")
	{
		post_y = red2.post_y;
		post_x = red2.post_x;
		cur_y = red2.cur_y;
		cur_x = red2.cur_x;
		radius = red2.radius;
	}
	else
	{
		post_y = white.post_y;
		post_x = white.post_x;
		cur_y = white.cur_y;
		cur_x = white.cur_x;
		radius = white.radius;
	}
	double d = dist(post_y, post_x, cur_y, cur_x);
	int _d = (int)d;
	for (int i = 1; i < _d; i++)
	{
		pair<double, double> p = make_point(post_y, post_x, cur_y, cur_x, i, _d - i);
		int real_y = (int)(p.first + 0.5);
		int real_x = (int)(p.second + 0.5);
		double temp = dist(real_y, real_x, red1.cur_y, red1.cur_x) - (radius + red1.radius);
		double gradient1 = (double)(real_x - red1.cur_x) / (real_y - red1.cur_y);
		double gradient2 = (double)(post_x - cur_x) / (post_y - cur_y);
		if (-5 <= temp && temp <= 5)
		{
			//y1,x1,y2,x2 type way
			if (red1.cur_y > real_y && red1.cur_x < real_x)	//어짜피 gradient1 < 0인경우
			{
				if (gradient2 > 0)
				{
					return{ red1.cur_y, red1.cur_x,real_y, real_x, 4,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 4,1 };
					}
					else
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 3,2 };
					}
				}
			}
			else if (red1.cur_y < real_y && red1.cur_x < real_x)	//gradient 1이 양수인경우밖에없음
			{
				if (gradient2 < 0)
				{
					return{ red1.cur_y, red1.cur_x,real_y, real_x, 4,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 1,2 };
					}
					else
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 4,3 };
					}
				}
			}
			else if (red1.cur_y > real_y && red1.cur_x > real_x)	//gradient1이 양수
			{
				if (gradient2 < 0)
				{
					return{ red1.cur_y, red1.cur_x,real_y, real_x, 2,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 3,4 };
					}
					else
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 2,1 };
					}
				}
			}
			else if (red1.cur_y < real_y && red1.cur_x > real_x)	//gradient1이 음수
			{
				if (gradient2 > 0)
				{
					return{ red1.cur_y, red1.cur_x,real_y, real_x, 2,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 2,3 };
					}
					else
					{
						return{ red1.cur_y, red1.cur_x,real_y, real_x, 1,4 };
					}
				}
			}
		}
	}
	return{ 0,0,0,0,0 };
}
item isRed2Hit(string str)
{
	int post_y, post_x, cur_y, cur_x, radius;
	if (str == "yellow")
	{
		post_y = yellow.post_y;
		post_x = yellow.post_x;
		cur_y = yellow.cur_y;
		cur_x = yellow.cur_x;
		radius = yellow.radius;
	}
	else if (str == "red1")
	{
		post_y = red1.post_y;
		post_x = red1.post_x;
		cur_y = red1.cur_y;
		cur_x = red1.cur_x;
		radius = red1.radius;
	}
	else if (str == "red2")
	{
		post_y = red2.post_y;
		post_x = red2.post_x;
		cur_y = red2.cur_y;
		cur_x = red2.cur_x;
		radius = red2.radius;
	}
	else
	{
		post_y = white.post_y;
		post_x = white.post_x;
		cur_y = white.cur_y;
		cur_x = white.cur_x;
		radius = white.radius;
	}
	double d = dist(post_y, post_x, cur_y, cur_x);
	int _d = (int)d;
	for (int i = 1; i < _d; i++)
	{
		pair<double, double> p = make_point(post_y, post_x, cur_y, cur_x, i, _d - i);
		int real_y = (int)(p.first + 0.5);
		int real_x = (int)(p.second + 0.5);
		double temp = dist(real_y, real_x, red2.cur_y, red2.cur_x) - (radius + red2.radius);
		double gradient1 = (double)(real_x - red2.cur_x) / (real_y - red2.cur_y);
		double gradient2 = (double)(post_x - cur_x) / (post_y - cur_y);
		if (-5 <= temp && temp <= 5)
		{
			//y1,x1,y2,x2 type way
			if (red2.cur_y > real_y && red2.cur_x < real_x)	//어짜피 gradient1 < 0인경우
			{
				if (gradient2 > 0)
				{
					return{ red2.cur_y, red2.cur_x,real_y, real_x, 4,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 4,1 };
					}
					else
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 3,2 };
					}
				}
			}
			else if (red2.cur_y < real_y && red2.cur_x < real_x)	//gradient 1이 양수인경우밖에없음
			{
				if (gradient2 < 0)
				{
					return{ red2.cur_y, red2.cur_x,real_y, real_x, 4,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 1,2 };
					}
					else
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 4,3 };
					}
				}
			}
			else if (red2.cur_y > real_y && red2.cur_x > real_x)	//gradient1이 양수
			{
				if (gradient2 < 0)
				{
					return{ red2.cur_y, red2.cur_x,real_y, real_x, 2,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 3,4 };
					}
					else
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 2,1 };
					}
				}
			}
			else if (red2.cur_y < real_y && red2.cur_x > real_x)	//gradient1이 음수
			{
				if (gradient2 > 0)
				{
					return{ red2.cur_y, red2.cur_x,real_y, real_x, 2,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 2,3 };
					}
					else
					{
						return{ red2.cur_y, red2.cur_x,real_y, real_x, 1,4 };
					}
				}
			}
		}
	}
	return{ 0,0,0,0,0 };
}
item isWhiteHit(string str)
{
	int post_y, post_x, cur_y, cur_x, radius;
	if (str == "yellow")
	{
		post_y = yellow.post_y;
		post_x = yellow.post_x;
		cur_y = yellow.cur_y;
		cur_x = yellow.cur_x;
		radius = yellow.radius;
	}
	else if (str == "red1")
	{
		post_y = red1.post_y;
		post_x = red1.post_x;
		cur_y = red1.cur_y;
		cur_x = red1.cur_x;
		radius = red1.radius;
	}
	else if (str == "red2")
	{
		post_y = red2.post_y;
		post_x = red2.post_x;
		cur_y = red2.cur_y;
		cur_x = red2.cur_x;
		radius = red2.radius;
	}
	else
	{
		post_y = white.post_y;
		post_x = white.post_x;
		cur_y = white.cur_y;
		cur_x = white.cur_x;
		radius = white.radius;
	}
	double d = dist(post_y, post_x, cur_y, cur_x);
	int _d = (int)d;
	for (int i = 1; i < _d; i++)
	{
		pair<double, double> p = make_point(post_y, post_x, cur_y, cur_x, i, _d - i);
		int real_y = (int)(p.first + 0.5);
		int real_x = (int)(p.second + 0.5);
		double temp = dist(real_y, real_x, white.cur_y, white.cur_x) - (radius + white.radius);
		double gradient1 = (double)(real_x - white.cur_x) / (real_y - white.cur_y);
		double gradient2 = (double)(post_x - cur_x) / (post_y - cur_y);
		if (-5 <= temp && temp <= 5)
		{
			//y1,x1,y2,x2 type way
			if (white.cur_y > real_y && white.cur_x < real_x)	//어짜피 gradient1 < 0인경우
			{
				if (gradient2 > 0)
				{
					return{ white.cur_y, white.cur_x,real_y, real_x, 4,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 4,1 };
					}
					else
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 3,2 };
					}
				}
			}
			else if (white.cur_y < real_y && white.cur_x < real_x)	//gradient 1이 양수인경우밖에없음
			{
				if (gradient2 < 0)
				{
					return{ white.cur_y, white.cur_x,real_y, real_x, 4,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 1,2 };
					}
					else
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 4,3 };
					}
				}
			}
			else if (white.cur_y > real_y && white.cur_x > real_x)	//gradient1이 양수
			{
				if (gradient2 < 0)
				{
					return{ white.cur_y, white.cur_x,real_y, real_x, 2,1 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 3,4 };
					}
					else
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 2,1 };
					}
				}
			}
			else if (white.cur_y < real_y && white.cur_x > real_x)	//gradient1이 음수
			{
				if (gradient2 > 0)
				{
					return{ white.cur_y, white.cur_x,real_y, real_x, 2,3 };
				}
				else
				{
					if (gradient2 < gradient1)
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 2,3 };
					}
					else
					{
						return{ white.cur_y, white.cur_x,real_y, real_x, 1,4 };
					}
				}
			}
		}
	}
	return{ 0,0,0,0,0 };
}
item isEdgeHit(string str)
{
	int post_y, post_x, cur_y, cur_x, radius;
	if (str == "yellow")
	{
		post_y = yellow.post_y;
		post_x = yellow.post_x;
		cur_y = yellow.cur_y;
		cur_x = yellow.cur_x;
		radius = yellow.radius;
	}
	else if (str == "red1")
	{
		post_y = red1.post_y;
		post_x = red1.post_x;
		cur_y = red1.cur_y;
		cur_x = red1.cur_x;
		radius = red1.radius;
	}
	else if (str == "red2")
	{
		post_y = red2.post_y;
		post_x = red2.post_x;
		cur_y = red2.cur_y;
		cur_x = red2.cur_x;
		radius = red2.radius;
	}
	else
	{
		post_y = white.post_y;
		post_x = white.post_x;
		cur_y = white.cur_y;
		cur_x = white.cur_x;
		radius = white.radius;
	}
	double d = dist(post_y, post_x, cur_y, cur_x);
	int _d = (int)d;
	for (int i = 1; i < _d; i++)
	{
		pair<double, double> p = make_point(post_y, post_x, cur_y, cur_x, i, _d - i);
		int real_y = (int)(p.first + 0.5);
		int real_x = (int)(p.second + 0.5);
		//아래랑 부딪혔을때
		if (abs(edge_maxY - real_y) <= radius)
		{
			//이전 x위치따라서 왼쪽인지 오른쪽인지
			if (post_x > real_x)
			{
				//오른쪽에서 들어오는거->way=4
				return{ post_y, post_x, real_y,real_x, 1 ,4 };
			}
			else
			{//왼쪽은 2
				return{ post_y, post_x, real_y,real_x, 1 ,2 };
			}
		}
		//왼쪽이랑 부딪혔을떄
		if (abs(edge_minX - real_x) <= radius)
		{
			if (post_y > real_y)
			{
				//아래쪽에서 오는거
				return{ post_y, post_x, real_y,real_x, 2 ,1 };
			}
			else
			{
				return{ post_y, post_x, real_y,real_x, 2 ,3 };
			}
		}
		//위랑 부딪혔을때
		if (abs(edge_minY - real_y) <= radius)
		{
			if (post_x > real_x)
			{
				//오른쪽에서
				return{ post_y, post_x, real_y,real_x, 3 ,4 };
			}
			else
			{
				return{ post_y, post_x, real_y,real_x, 3 , 2 };
			}
		}
		//오른쪽이랑 부딪혔을떄
		if (abs(edge_maxX - real_x) <= radius)
		{
			if (post_y > real_y)
			{
				//아래쪽에서 오는거
				return{post_y, post_x, real_y,real_x, 4 ,1 };
			}
			else
			{
				return{ post_y, post_x, real_y,real_x, 4 ,3 };
			}
		}
	}
	return{ 0,0,0,0,0 };
}
void transformationYellow()
{
	//이동하기
	pair<int, int> yellow_next = makeNext(yellow.post_y, yellow.post_x, yellow.cur_y, yellow.cur_x);
	pair<int, int> red1_next = makeNext(red1.post_y, red1.post_x, red1.cur_y, red1.cur_x);
	pair<int, int> red2_next = makeNext(red2.post_y, red2.post_x, red2.cur_y, red2.cur_x);
	pair<int, int> white_next = makeNext(white.post_y, white.post_x, white.cur_y, white.cur_x);
	bool c = false;
	//노란공에서 다른 공이 맞는지 확인
	item red1Hit = isRed1Hit("yellow");
	//부딪혔을때
	if (!yellowCheck)
	{
		if (!(red1Hit.y1 == 0 && red1Hit.x1 == 0 && red1Hit.y2 == 0 && red1Hit.x2 == 0 && red1Hit.type == 0))
		{
			c = true;
			yellow.post_y = red1Hit.y2;
			yellow.post_x = red1Hit.x2;
			pair<int, int> anoterPoint = getOtherPoint(red1Hit.y1, red1Hit.x1, red1Hit.y2, red1Hit.x2, dist(red1Hit.y1, red1Hit.x1, red1Hit.y2, red1Hit.x2), red1Hit.type, red1Hit.way);
			yellow_next = { anoterPoint };	//맞고 각도로 나아가는 방향이 cur로 바뀐다.

			red1Check = true;
			//red1 이동
			red1.post_y = red1.cur_y;
			red1.post_x = red1.cur_x;
			red1_next.first = 2 * red1.cur_y - red1Hit.y2;
			red1_next.second = 2 * red1.cur_x - red1Hit.x2;
			red1.cur_y = red1_next.first;
			red1.cur_x = red1_next.second;
		}
	}
	item red2Hit = isRed2Hit("yellow");
	if (!red2Check)
	{
		if (!(red2Hit.y1 == 0 && red2Hit.x1 == 0 && red2Hit.y2 == 0 && red2Hit.x2 == 0 && red2Hit.type == 0))
		{
			c = true;
			yellow.post_y = red2Hit.y2;
			yellow.post_x = red2Hit.x2;
			pair<int, int> anoterPoint = getOtherPoint(red2Hit.y1, red2Hit.x1, red2Hit.y2, red2Hit.x2, dist(red2Hit.y1, red2Hit.x1, red2Hit.y2, red2Hit.x2), red2Hit.type, red2Hit.way);
			yellow_next = { anoterPoint };

			red2Check = true;
			//red2 이동
			red2.post_y = red2.cur_y;
			red2.post_x = red2.cur_x;
			red2_next.first = 2 * red2.cur_y - red2Hit.y2;
			red2_next.second = 2 * red2.cur_x - red2Hit.x2;
			red2.cur_y = red2_next.first;
			red2.cur_x = red2_next.second;
		}
	}
	item whiteHit = isWhiteHit("yellow");
	if (!whiteCheck)
	{
		if (!(whiteHit.y1 == 0 && whiteHit.x1 == 0 && whiteHit.y2 == 0 && whiteHit.x2 == 0 && whiteHit.type == 0))
		{
			c = true;
			yellow.post_y = whiteHit.y2;
			yellow.post_x = whiteHit.x2;
			pair<int, int> anoterPoint = getOtherPoint(whiteHit.y1, whiteHit.x1, whiteHit.y2, whiteHit.x2, dist(whiteHit.y1, whiteHit.x1, whiteHit.y2, whiteHit.x2), whiteHit.type, whiteHit.way);
			yellow_next = { anoterPoint };

			whiteCheck = true;
			//white 이동
			white.post_y = white.cur_y;
			white.post_x = white.cur_x;
			white_next.first = 2 * white.cur_y - whiteHit.y2;
			white_next.second = 2 * white.cur_x - whiteHit.x2;
			white.cur_y = white_next.first;
			white.cur_x = white_next.second;
		}
	}
	item edgeHit = isEdgeHit("yellow");
	//부딪힌경우
	if (!(edgeHit.y1 == 0 && edgeHit.x1 == 0 && edgeHit.y2 == 0 && edgeHit.x2 == 0 && edgeHit.type == 0))
	{
		c = true;
		yellow.post_y = edgeHit.y2;
		yellow.post_x = edgeHit.x2;
		pair<int, int > anoterPoint = getOtherPoint(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2, dist(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2), edgeHit.type, edgeHit.way);
		yellow_next = { anoterPoint };
	}
	//이동좌표 구하기
	if (c == false)
	{
		yellow.post_y = yellow.cur_y;
		yellow.post_x = yellow.cur_x;
	}
	yellow.cur_y = yellow_next.first;
	yellow.cur_x = yellow_next.second;
}
void transformationRed1()
{
	//이동하기
	pair<int, int> yellow_next = makeNext(yellow.post_y, yellow.post_x, yellow.cur_y, yellow.cur_x);
	pair<int, int> red1_next = makeNext(red1.post_y, red1.post_x, red1.cur_y, red1.cur_x);
	pair<int, int> red2_next = makeNext(red2.post_y, red2.post_x, red2.cur_y, red2.cur_x);
	pair<int, int> white_next = makeNext(white.post_y, white.post_x, white.cur_y, white.cur_x);
	bool c = false;
	item yellowHit = isYellowHit("red1");
	//부딪혔을때
	if (!yellowCheck)
	{
		if (!(yellowHit.y1 == 0 && yellowHit.x1 == 0 && yellowHit.y2 == 0 && yellowHit.x2 == 0 && yellowHit.type == 0))
		{
			c = true;
			red1.post_y = yellowHit.y2;
			red1.post_x = yellowHit.x2;
			pair<int, int> anoterPoint = getOtherPoint(yellowHit.y1, yellowHit.x1, yellowHit.y2, yellowHit.x2, dist(yellowHit.y1, yellowHit.x1, yellowHit.y2, yellowHit.x2), yellowHit.type, yellowHit.way);
			red1_next = { anoterPoint };	//맞고 각도로 나아가는 방향이 cur로 바뀐다.

			//yellow이동
			yellowCheck = true;
			yellow.post_y = yellow.cur_y;
			yellow.post_x = yellow.cur_x;
			yellow_next.first = 2 * yellow.cur_y - yellowHit.y2;
			yellow_next.second = 2 * yellow.cur_x - yellowHit.x2;
			yellow.cur_y = yellow_next.first;
			yellow.cur_x = yellow_next.second;
		}
	}
	if (!red2Check)
	{
		item red2Hit = isRed2Hit("red1");
		if (!(red2Hit.y1 == 0 && red2Hit.x1 == 0 && red2Hit.y2 == 0 && red2Hit.x2 == 0 && red2Hit.type == 0))
		{
			c = true;
			red1.post_y = red2Hit.y2;
			red1.post_x = red2Hit.x2;
			pair<int, int> anoterPoint = getOtherPoint(red2Hit.y1, red2Hit.x1, red2Hit.y2, red2Hit.x2, dist(red2Hit.y1, red2Hit.x1, red2Hit.y2, red2Hit.x2), red2Hit.type, red2Hit.way);
			red1_next = { anoterPoint };

			//red2 이동
			red2Check = true;
			red2.post_y = red2.cur_y;
			red2.post_x = red2.cur_x;
			red2_next.first = 2 * red2.cur_y - red2Hit.y2;
			red2_next.second = 2 * red2.cur_x - red2Hit.x2;
			red2.cur_y = red2_next.first;
			red2.cur_x = red2_next.second;
		}
	}
	item whiteHit = isWhiteHit("red1");
	if (!whiteCheck)
	{
		if (!(whiteHit.y1 == 0 && whiteHit.x1 == 0 && whiteHit.y2 == 0 && whiteHit.x2 == 0 && whiteHit.type == 0))
		{
			c = true;
			red1.post_y = whiteHit.y2;
			red1.post_x = whiteHit.x2;
			pair<int, int> anoterPoint = getOtherPoint(whiteHit.y1, whiteHit.x1, whiteHit.y2, whiteHit.x2, dist(whiteHit.y1, whiteHit.x1, whiteHit.y2, whiteHit.x2), whiteHit.type, whiteHit.way);
			red1_next = { anoterPoint };

			//white 이동
			whiteCheck = true;
			white.post_y = white.cur_y;
			white.post_x = white.cur_x;
			white_next.first = 2 * white.cur_y - whiteHit.y2;
			white_next.second = 2 * white.cur_x - whiteHit.x2;
			white.cur_y = white_next.first;
			white.cur_x = white_next.second;
		}
	}
	item edgeHit = isEdgeHit("red1");
	//부딪힌경우
	if (!(edgeHit.y1 == 0 && edgeHit.x1 == 0 && edgeHit.y2 == 0 && edgeHit.x2 == 0 && edgeHit.type == 0))
	{
		c = true;
		red1.post_y = edgeHit.y2;
		red1.post_x = edgeHit.x2;
		pair<int, int > anoterPoint = getOtherPoint(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2, dist(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2), edgeHit.type, edgeHit.way);
		red1_next = { anoterPoint };
	}
	//이동좌표 구하기
	if (c == false)
	{
		red1.post_y = red1.cur_y;
		red1.post_x = red1.cur_x;
	}
	red1.cur_y = red1_next.first;
	red1.cur_x = red1_next.second;
}
void transformationRed2()
{
	//이동하기
	pair<int, int> yellow_next = makeNext(yellow.post_y, yellow.post_x, yellow.cur_y, yellow.cur_x);
	pair<int, int> red1_next = makeNext(red1.post_y, red1.post_x, red1.cur_y, red1.cur_x);
	pair<int, int> red2_next = makeNext(red2.post_y, red2.post_x, red2.cur_y, red2.cur_x);
	pair<int, int> white_next = makeNext(white.post_y, white.post_x, white.cur_y, white.cur_x);
	bool c = false;
	item yellowHit = isYellowHit("red2");
	//부딪혔을때
	if (!yellowCheck)
	{
		if (!(yellowHit.y1 == 0 && yellowHit.x1 == 0 && yellowHit.y2 == 0 && yellowHit.x2 == 0 && yellowHit.type == 0))
		{
			c = true;
			red2.post_y = yellowHit.y2;
			red2.post_x = yellowHit.x2;
			pair<int, int> anoterPoint = getOtherPoint(yellowHit.y1, yellowHit.x1, yellowHit.y2, yellowHit.x2, dist(yellowHit.y1, yellowHit.x1, yellowHit.y2, yellowHit.x2), yellowHit.type, yellowHit.way);
			red2_next = { anoterPoint };	//맞고 각도로 나아가는 방향이 cur로 바뀐다.

			yellowCheck = true;
			yellow.post_y = yellow.cur_y;
			yellow.post_x = yellow.cur_x;
			yellow_next.first = 2 * yellow.cur_y - yellowHit.y2;
			yellow_next.second = 2 * yellow.cur_x - yellowHit.x2;
			yellow.cur_y = yellow_next.first;
			yellow.cur_x = yellow_next.second;
		}
	}
	item red1Hit = isRed1Hit("red2");
	if (!red1Check)
	{
		if (!(red1Hit.y1 == 0 && red1Hit.x1 == 0 && red1Hit.y2 == 0 && red1Hit.x2 == 0 && red1Hit.type == 0))
		{
			c = true;
			red2.post_y = red1Hit.y2;
			red2.post_x = red1Hit.x2;
			pair<int, int> anoterPoint = getOtherPoint(red1Hit.y1, red1Hit.x1, red1Hit.y2, red1Hit.x2, dist(red1Hit.y1, red1Hit.x1, red1Hit.y2, red1Hit.x2), red1Hit.type, red1Hit.way);
			red2_next = { anoterPoint };

			//red1 이동
			red1Check = true;
			red1.post_y = red1.cur_y;
			red1.post_x = red1.cur_x;
			red1_next.first = 2 * red1.cur_y - red1Hit.y2;
			red1_next.second = 2 * red1.cur_x - red1Hit.x2;
			red1.cur_y = red1_next.first;
			red1.cur_x = red1_next.second;
		}
	}
	item whiteHit = isWhiteHit("red2");
	if (!whiteCheck)
	{
		if (!(whiteHit.y1 == 0 && whiteHit.x1 == 0 && whiteHit.y2 == 0 && whiteHit.x2 == 0 && whiteHit.type == 0))
		{
			c = true;
			red2.post_y = whiteHit.y2;
			red2.post_x = whiteHit.x2;
			pair<int, int> anoterPoint = getOtherPoint(whiteHit.y1, whiteHit.x1, whiteHit.y2, whiteHit.x2, dist(whiteHit.y1, whiteHit.x1, whiteHit.y2, whiteHit.x2), whiteHit.type, whiteHit.way);
			red2_next = { anoterPoint };

			//white 이동
			whiteCheck = true;
			white.post_y = white.cur_y;
			white.post_x = white.cur_x;
			white_next.first = 2 * white.cur_y - whiteHit.y2;
			white_next.second = 2 * white.cur_x - whiteHit.x2;
			white.cur_y = white_next.first;
			white.cur_x = white_next.second;
		}
	}
	item edgeHit = isEdgeHit("red2");
	//부딪힌경우
	if (!(edgeHit.y1 == 0 && edgeHit.x1 == 0 && edgeHit.y2 == 0 && edgeHit.x2 == 0 && edgeHit.type == 0))
	{
		c = true;
		red2.post_y = edgeHit.y2;
		red2.post_x = edgeHit.x2;
		pair<int, int > anoterPoint = getOtherPoint(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2, dist(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2), edgeHit.type, edgeHit.way);
		red2_next = { anoterPoint };
	}
	//이동좌표 구하기
	if (c == false)
	{
		red2.post_y = red2.cur_y;
		red2.post_x = red2.cur_x;
	}
	red2.cur_y = red2_next.first;
	red2.cur_x = red2_next.second;
}
void transformationWhite()
{
	//이동하기
	pair<int, int> yellow_next = makeNext(yellow.post_y, yellow.post_x, yellow.cur_y, yellow.cur_x);
	pair<int, int> red1_next = makeNext(red1.post_y, red1.post_x, red1.cur_y, red1.cur_x);
	pair<int, int> red2_next = makeNext(red2.post_y, red2.post_x, red2.cur_y, red2.cur_x);
	pair<int, int> white_next = makeNext(white.post_y, white.post_x, white.cur_y, white.cur_x);
	bool c = false;
	item yellowHit = isYellowHit("white");
	//부딪혔을때
	if (!yellowCheck)
	{
		if (!(yellowHit.y1 == 0 && yellowHit.x1 == 0 && yellowHit.y2 == 0 && yellowHit.x2 == 0 && yellowHit.type == 0))
		{
			c = true;
			white.post_y = yellowHit.y2;
			white.post_x = yellowHit.x2;
			pair<int, int> anoterPoint = getOtherPoint(yellowHit.y1, yellowHit.x1, yellowHit.y2, yellowHit.x2, dist(yellowHit.y1, yellowHit.x1, yellowHit.y2, yellowHit.x2), yellowHit.type, yellowHit.way);
			white_next = { anoterPoint };	//맞고 각도로 나아가는 방향이 cur로 바뀐다.
			
			yellowCheck = true;
			yellow.post_y = yellow.cur_y;
			yellow.post_x = yellow.cur_x;
			yellow_next.first = 2 * yellow.cur_y - yellowHit.y2;
			yellow_next.second = 2 * yellow.cur_x - yellowHit.x2;
			yellow.cur_y = yellow_next.first;
			yellow.cur_x = yellow_next.second;
		}
	}
	item red1Hit = isRed1Hit("white");
	if (!red1Check)
	{
		if (!(red1Hit.y1 == 0 && red1Hit.x1 == 0 && red1Hit.y2 == 0 && red1Hit.x2 == 0 && red1Hit.type == 0))
		{
			c = true;
			white.post_y = red1Hit.y2;
			white.post_x = red1Hit.x2;
			pair<int, int> anoterPoint = getOtherPoint(red1Hit.y1, red1Hit.x1, red1Hit.y2, red1Hit.x2, dist(red1Hit.y1, red1Hit.x1, red1Hit.y2, red1Hit.x2), red1Hit.type, red1Hit.way);
			white_next = { anoterPoint };

			//red1 이동
			red1Check = true;
			red1.post_y = red1.cur_y;
			red1.post_x = red1.cur_x;
			red1_next.first = 2 * red1.cur_y - red1Hit.y2;
			red1_next.second = 2 * red1.cur_x - red1Hit.x2;
			red1.cur_y = red1_next.first;
			red1.cur_x = red1_next.second;
		}
	}
	item red2Hit = isRed2Hit("white");
	if (!red2Check)
	{
		if (!(red2Hit.y1 == 0 && red2Hit.x1 == 0 && red2Hit.y2 == 0 && red2Hit.x2 == 0 && red2Hit.type == 0))
		{
			c = true;
			white.post_y = red2Hit.y2;
			white.post_x = red2Hit.x2;
			pair<int, int> anoterPoint = getOtherPoint(red2Hit.y1, red2Hit.x1, red2Hit.y2, red2Hit.x2, dist(red2Hit.y1, red2Hit.x1, red2Hit.y2, red2Hit.x2), red2Hit.type, red2Hit.way);
			white_next = { anoterPoint };

			//red2
			red2Check = true;
			red2.post_y = red2.cur_y;
			red2.post_x = red2.cur_x;
			red2_next.first = 2 * red2.cur_y - red2Hit.y2;
			red2_next.second = 2 * red2.cur_x - red2Hit.x2;
			red2.cur_y = red2_next.first;
			red2.cur_x = red2_next.second;
		}
	}
	item edgeHit = isEdgeHit("white");
	//부딪힌경우
	if (!(edgeHit.y1 == 0 && edgeHit.x1 == 0 && edgeHit.y2 == 0 && edgeHit.x2 == 0 && edgeHit.type == 0))
	{
		c = true;
		white.post_y = edgeHit.y2;
		white.post_x = edgeHit.x2;
		pair<int, int > anoterPoint = getOtherPoint(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2, dist(edgeHit.y1, edgeHit.x1, edgeHit.y2, edgeHit.x2), edgeHit.type, edgeHit.way);
		white_next = { anoterPoint };
	}
	//이동좌표 구하기
	if (c == false)
	{
		white.post_y = white.cur_y;
		white.post_x = white.cur_x;
	}
	white.cur_y = white_next.first;
	white.cur_x = white_next.second;
}
// DLL을 만들기 위한 부분
BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
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
int CDECL userTransform(int* point_y, int* point_x, KScRgbImage2d* input, KScRgbImage2d* output)
{
	int dx = input->GetXSize();
	int dy = input->GetYSize();
	output->Free();
	output->Alloc(dx, dy);

	//input 이미지에 대한 R,G,B 색상
	KScScalarImage2dUint8 *inputRed = new KScScalarImage2dUint8;
	inputRed->Free();
	inputRed->Alloc(dx, dy);
	KScScalarImage2dUint8 *inputGreen = new KScScalarImage2dUint8;
	inputGreen->Free();
	inputGreen->Alloc(dx, dy);
	KScScalarImage2dUint8 *inputBlue = new KScScalarImage2dUint8;
	inputBlue->Free();
	inputBlue->Alloc(dx, dy);

	input->SplitAllPlane(inputRed, inputGreen, inputBlue);
	KSdUint8 **inputRedArray = inputRed->Get2dArray();
	KSdUint8 **inputGreenArray = inputGreen->Get2dArray();
	KSdUint8 **inputBlueArray = inputBlue->Get2dArray();

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

	//파일읽어서 원의 정보 저장
	ifstream inFile;
	inFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt");
	while (!inFile.eof())
	{
		circle temp;
		inFile >> temp.color >> temp.post_y >> temp.post_x >> temp.cur_y >> temp.cur_x >> temp.radius;
		if (temp.color == "yellow")
		{
			yellow = temp;
		}
		else if (temp.color == "red1")
		{
			red1 = temp;
		}
		else if (temp.color == "red2")
		{
			red2 = temp;
		}
		else if (temp.color == "white")
		{
			white = temp;
		}
	}

	transformationYellow();
	transformationRed1();
	transformationRed2();
	transformationWhite();

	//이동한 중점 저장하기
	ofstream outFile;
	outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::trunc);
	outFile.close();
	outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::app);
	outFile << yellow.color << " " << yellow.post_y << " " << yellow.post_x << " " << yellow.cur_y << " " << yellow.cur_x << " " << yellow.radius << "\n";
	outFile.close();
	outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::app);
	outFile << red1.color << " " << red1.post_y << " " << red1.post_x << " " << red1.cur_y << " " << red1.cur_x << " " << red1.radius << "\n";
	outFile.close();
	outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::app);
	outFile << red2.color << " " << red2.post_y << " " << red2.post_x << " " << red2.cur_y << " " << red2.cur_x << " " << red2.radius << "\n";
	outFile.close();
	outFile.open("C:\\Program Files (x86)\\MTES2.0\\Work\\Tif\\pointSave.txt", ios::app);
	outFile << white.color << " " << white.post_y << " " << white.post_x << " " << white.cur_y << " " << white.cur_x << " " << white.radius << "\n";
	outFile.close();

	//전체 칠하기
	for (int i = 0; i < dy; i++)
	{
		for (int j = 0; j < dx; j++)
		{
			outputRedArray[i][j] = inputRedArray[i][j];
			outputGreenArray[i][j] = inputGreenArray[i][j];
			outputBlueArray[i][j] = inputBlueArray[i][j];
		}
	}
	//노랑색 출력
	int yellow_min_y = yellow.post_y - yellow.radius;
	int yellow_max_y = yellow.post_y + yellow.radius;
	int yellow_min_x = yellow.post_x - yellow.radius;
	int yellow_max_x = yellow.post_x + yellow.radius;
	for (int j = yellow_min_y; j <= yellow_max_y; j++)
	{
		for (int k = yellow_min_x; k <= yellow_max_x; k++)
		{
			if (checkInRange(j, k, yellow.radius, "yellow"))
			{
				outputRedArray[j][k] = 200;
				outputGreenArray[j][k] = 200;
				outputBlueArray[j][k] = 150;
			}
		}
	}
	//red1 출력
	int red1_min_y = red1.post_y - red1.radius;
	int red1_max_y = red1.post_y + red1.radius;
	int red1_min_x = red1.post_x - red1.radius;
	int red1_max_x = red1.post_x + red1.radius;
	for (int j = red1_min_y; j <= red1_max_y; j++)
	{
		for (int k = red1_min_x; k <= red1_max_x; k++)
		{
			if (checkInRange(j, k, red1.radius, "red1"))
			{
				outputRedArray[j][k] = 200;
				outputGreenArray[j][k] = 50;
				outputBlueArray[j][k] = 120;
			}
		}
	}
	//red2 출력
	int red2_min_y = red2.post_y - red2.radius;
	int red2_max_y = red2.post_y + red2.radius;
	int red2_min_x = red2.post_x - red2.radius;
	int red2_max_x = red2.post_x + red2.radius;
	for (int j = red2_min_y; j <= red2_max_y; j++)
	{
		for (int k = red2_min_x; k <= red2_max_x; k++)
		{
			if (checkInRange(j, k, red2.radius, "red2"))
			{
				outputRedArray[j][k] = 200;
				outputGreenArray[j][k] = 50;
				outputBlueArray[j][k] = 120;
			}
		}
	}
	//white 출력
	int white_min_y = white.post_y - white.radius;
	int white_max_y = white.post_y + white.radius;
	int white_min_x = white.post_x - white.radius;
	int white_max_x = white.post_x + white.radius;
	for (int j = white_min_y; j <= white_max_y; j++)
	{
		for (int k = white_min_x; k <= white_max_x; k++)
		{
			if (checkInRange(j, k, white.radius, "white"))
			{
				outputRedArray[j][k] = 250;
				outputGreenArray[j][k] = 250;
				outputBlueArray[j][k] = 250;
			}
		}
	}
	input->MergeAllPlane(inputRed, inputGreen, inputBlue);
	output->MergeAllPlane(outputRed, outputGreen, outputBlue);

	delete inputRed;
	delete inputGreen;
	delete inputBlue;
	delete outputRed;
	delete outputGreen;
	delete outputBlue;
	return TRUE;
}

// 2 개 이상의 함수를 정의할 경우, 아래에 수동으로 삽입합니다.


