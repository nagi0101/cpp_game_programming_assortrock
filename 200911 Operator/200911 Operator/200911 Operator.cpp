#include <iostream>

using namespace std;

typedef struct _tagPoint
{
	int x;
	int y;

	_tagPoint() :
		x(0), y(0) {}

	_tagPoint(int _x, int _y) :
		x(_x), y(_y) {}

	_tagPoint(const _tagPoint& pt)
	{
		//얕은 복사를 한다. 이렇게 해줄 경우
		//this는 자기 자신의 포인터이고
		//*를 붙여서 자기자신을 역참조하여
		//모든 데이터를 복사한다.
		*this = pt;
	}

	_tagPoint operator +(const _tagPoint& pt)
	{
		_tagPoint result;
		result.x = x + pt.x;
		result.y = y + pt.y;
		return result;
	}

	void operator << (const _tagPoint& pt)
	{
		x = pt.x;
		y = pt.y;
	}
}POINT, * PPOINT;

int main()
{
	POINT pt1(10, 20), pt2(30, 40), pt3;

	pt3 = pt1 + pt2;

	pt3 << pt1;

	cout << "x : " << pt3.x << "\ty : " << pt3.y << endl;
}