#include <iostream>

using namespace std;

/*
객체(Object) : 모든 사물을 의미한다. C++에서 객체를
의미라는 것은 각 변수들도 객체로 취급할 수도 있다.
하지만 객체 지향 프로그래밍을 지원하기 위해 제공되는
수간은 Class이다. Class가 객체인 것은 아니고 객체를
만드는 틀임.

객체 지향 프로그래밍(OOP) : 객체들의 관계를 설정해주어서
부품을 조립하듯이 객체들을 조립하여 완성된 프로그램을
만들어나가는 방식

class className {};의 형태로 선언.
코드블럭 안에 맴버 변수를 넣어줄 수 있다.
함수도 맴버로 만들 수 있다.

클래스의 4가지 속성
캡슐화 : 클래스 안에 속하는 여러 변수 혹은 함수를
하나의 클래스로 묶어주는 기능을 말한다.
은닉화 : 클래스 안에 속하는 변수 혹은 함수를 내가 원하는
부분만 외부에 공개하고 외부에 공개하지 않을 수 있다.
	- public(structure default) : 클래스 내부와 외부에서 모두 접근 가능
	- protected : 클래스 외부에서는 접근이 불가능하고 자기자신 내부나
	자식 클래스 내부에서는 접근이 가능한 키워드
	- private(class default) : 자기자신 내부에서만 접근이 가능하고 외부나
	자식 내부에서는 접근이 불가능한 방법이다.
상속성 : 클래스는 클래스와 클래스간에 부모, 자식 관계를 형성할 수 있다.
자식 클래스는 부모 클래스의 맴버를 물려받아 자신의 것처럼 사용할 수 있다.
단, private로 되어있는 맴버에는 접근이 불가능하다.
다형성 : 부모 자식 관계로 상속관계가 형성되어있는 클래스간에 서로 형변환이
가능한 성질을 말한다.

생성자와 소멸자
생성자 : 어떤 클래스를 이용해서 객체를 생성할때 자동으로 호출되는 함수이다.
객체 생성시 자동으로 호출되기에 멤버변수를 초기화할 때 유용하게 사용 가능하다.
생성자를 만들어주지 않을 경우 내부적으로 기본 생성자가 제공되어 자동으로
호출해준다.
ClassName()
{
}
의 형태로 선언

소멸자 : 어떤 클래스를 이용해서 생성한 객체가 메모리에서 해제될 때
자동으로 호출되는 함수이다. 객체를 사용하고 난 뒤 마무리 작업을 해줄때
유용하게 사용할 수 있다.

~ClassName()
{
}
의 형태로 선언
*/
class CTracer
{
public:
	//생성자
	CTracer()
	{
		cout << "Tracer 생성자" << endl;
		strcpy_s(m_strName, "트레이서");
	}

	CTracer(const char* pName)
	{
		strcpy_s(m_strName, pName);
		cout << "Name 생성자" << endl;
	}

	// Initializer
	CTracer(const char* pName, int iFlash, int iBack) :
		m_iBack(iBack),
		m_iFlash(iFlash)
	{
		strcpy_s(m_strName, pName);
		cout << "Name, Flash, Back 생성" << endl;
	}

	//소멸자
	~CTracer()
	{
		cout << "Tracer 소멸자" << endl;
	}

	char	m_strName[32];

public:
	int		m_iAttack;
	int		m_iHP;

private:
	int		m_iFlash;
	int		m_iBack;
public:
	void Output() {
		cout << "Tracer Output" << endl;
		cout << "Name : " << m_strName << endl;
	}
};

int main()
{
	CTracer trl("한조", 3, 1);
	//main() 안은 클래스 외부이므로 public으로 설정된 맴버에만 접근 가능

	trl.Output();

	return 0;
}