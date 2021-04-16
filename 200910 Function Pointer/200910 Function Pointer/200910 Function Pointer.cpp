#include <iostream>
#include <functional>

using namespace std;

int Sum(int a, int b)
{
	return a + b;
}

int OutSum(int a, int b)
{
	cout << a - b << endl;
	return a - b;
}

void Output() {
	cout << "Output Function" << endl;
}

class CHanzo
{
public:
	CHanzo()
	{
		m_iTest = 10;
	}
	~CHanzo()
	{
	}
public:
	int m_iTest;
	void Output()
	{
		cout << "Hanzo" << endl;
		//this는 생략할 수 있다.
		cout << "Test : " << this->m_iTest << endl;
	}
};

int main()
{
	int(*pFunc)(int, int) = Sum;

	cout << pFunc(10, 20) << endl;

	pFunc = OutSum;

	pFunc(10, 20);

	void(*pFunc1)() = Output;

	pFunc1();

	CHanzo hanzo1, hanzo2;

	hanzo1.m_iTest = 100;
	hanzo2.m_iTest = 200;

	//this 포인터 : 클래스 안에서 this를 사용할 경우 해당 객체의 메모리
	//주소가 된다. 즉 자기자신의 포인터이다.
	//맴버 함수를 호출할 때 this를 호출자로 세팅한다.
	hanzo1.Output();
	hanzo2.Output();

	//맴버함수포인터 선언시 포인터변수 이름 앞에 클래스명:: 붙여준다.
	void(CHanzo:: * pFunc2)() = &CHanzo::Output;

	//(*pFunc2)();

	(hanzo1.*pFunc2)();

	function<void()> func;
	function<void()> func1;

	func = bind(Output);
	func1 = bind(&CHanzo::Output, &hanzo2);

	cout << "========= Functional ========= " << endl;

	func();
	func1();

	function<int(int, int)> func3;
	function<float(float)> func4;

	func3 = bind(OutSum, placeholders::_1, placeholders::_2);

	func3(10, 20);

	return 0;
}