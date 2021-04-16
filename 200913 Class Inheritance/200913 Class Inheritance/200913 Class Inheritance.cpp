#include <iostream>

using namespace std;

/*
자식 클래스는 부모 클래스의 멤버들을 사용할 수 있다.

부모 클래스에서 public이나 protected로 되어있는 멤버들은 사용 가능하지만,
private으로 되어있는 멤버는 자식에서도 사용이 불가능하다.

상속의 형태 : public, private 상속이 있다.

다형성 : 상속 관계에 있는 클래스간에 서로 형변환이 가능한 성질을 말한다.

가상함수 : 함수 오버라이딩 이라고도 부른다. 함수를 재정의하는 기능이다.
맴버함수 앞에 virtual 키워드를 붙이면 해당 함수는 가상함수가 된다.
만약 CParent 클래스에 virtual void Output() 함수가 있다면 자식 클래스에서는 이
가상함수를 재정의할 수 있다. 재정의는 함수 이름과 인자가 완전히 똑같아야 한다.

가상함수를 가지고 있는 클래스는 내부적으로 가상함수 테이블이라는 것을 생성한다.
가상함수 테이블은 가상함수들의 메모리 주소를 저장하는 테이블이다.

만약 CParent의 Output이 가상함수이고 CChild 클래스에 Output을 재정의한다면
그런 뒤 CChild 객체를 생성하면 가상함수 테이블에는 CChlid 클래스의 Output
주소가 올라가게 된다.

만약 CParent 객체를 생성한다면 CParent의 Output 주소가 올라가게 된다.

그래서 Output함수, 즉 가상함수를 호출하게 되면 먼저 가상함수 테이블을 참조해서
메모리 주소를 확인한다. 가상함수 테이블에 CChild의 Output 주소가 들어가있다면
그 주소의 함수를 호출해주는 개념이다.

소멸자도 가상함수로 만들 수 있다. 부모의 소멸자는 가상함수로 만들어두자.
*/

class CParent
{
public:
	CParent()
	{
		cout << "CParent 생성자" << endl;
	}
	virtual ~CParent()
	{
		cout << "CParent 소멸자" << endl;
	}

public:
	int m_iA;
	virtual void Output()
	{
		cout << "Parent Output Func" << endl;
	}
	//순수가상함수 : 함수 뒤에 = 0 을 붙여주면 해당 가상함수는 순수가상함수가된다.
	//순수가상함수는 구현부분이 존재하지 않는다.
	//순수가상함수를 가지고 있는 클래스를 추상클래스라고 부른다.
	//추상클래스는 인스턴스(객체) 생성이 불가능하다
	//순수가상함수는 자식에서 반드시 재정의 해야한다. 왜냐하면 순수가상함수는
	//정의 부분이 없기 때문에 반드시 자식에서 재정의해서 사용할 목적으로
	//만들어주는 함수이기 때문이다.
	virtual void OutputPure() = 0;
protected:
	int m_iB;
private:
	int m_iC;
};

class CChild : public CParent
{
public:
	CChild()
	{
		m_iB = 200;
		//m_iC는 private이기에 자식 내부에서도 접근 불가능
		cout << "CChild 생성자" << endl;
	}
	virtual ~CChild()
	{
		cout << "CChild 소멸자" << endl;
	}
protected:
	int m_iD;

public:
	void ChildOutput()
	{
		cout << "Child Output Func" << endl;
	}

	void Output()
	{
		CParent::Output();
		cout << "Child Output Func" << endl;
	}
	virtual void OutputPure()
	{
	}
};

class CChild1 : private CParent
{
public:
	CChild1()
	{
		m_iA = 100;
		m_iB = 200;
		cout << "CChild1 생성자" << endl;
	}
	~CChild1()
	{
		cout << "CChild1 소멸자" << endl;
	}
private:
	int m_iD;

public:
	virtual void OutputPure()
	{
	}
};

class CChildChild : public CChild
{
public:
	CChildChild()
	{
		m_iD = 500;
		cout << "CChildChild 생성자" << endl;
	}
	~CChildChild()
	{
		cout << "CChildChild 소멸자" << endl;
	}
private:
	int m_iE;
};

int main()
{
	/*
	상속 관계에서 생성자 호출 순서 : 부모 -> 자식 순서
	상속 관계에서 소멸자 호출 순서 : 자식 -> 부모 순서
	*/
	//CParent	parent;
	//CChild	child;
	//CChild1	child1;
	//CChildChild	childchild;

	//parent.m_iA = 100;
	//child.m_iA = 200;
	//	child1.m_iA = 300;
	//	child1.Output();
	//child.Output();

	//자식->부모 형변환 : 업캐스팅
	//부모->자식 형변환 : 다운캐스팅(주의 필요!)
	CParent* pParent = new CChild;
	CChild1 child1;
	//	CParent parent; 불가능. 추상 클래스.
		//CParent* pParent1 = new CChild1;
	//	CParent* pParent2 = new CChildChild;

	CParent* pParentArr[2] = {};
	//	pParentArr[0] = new CChild;
	//	pParentArr[1] = new CChildChild;

		//아래 두 클래스는 모두 CParent 클래스를 상속받고 있다.
		//그러므로 pParent를 두 타입 모두 다운캐스팅 가능하다.
		//그런데 pParent는 CChild로 할당한 객체이다.
		//이 객체를 CChild1 타입으로 다운캐스팅 하여 넣어주게 되면
		//이 객체를 사용할때 문제가 발생할 수 있다. 왜냐하면 애초에 생성한 객체가 아닌
		//다른 타입으로 변환됐기 때문이다.

	CChild* pChild = (CChild*)pParent;

	//	((CChild*)pParent)->ChildOutput();
	pParent->Output();
	pParent->CParent::Output();

	//	delete pParent;
		//	delete pParent2;
	delete pChild;

	//	for (int i = 0; i < 2; ++i)
	//	{
	//		delete pParentArr[i];
	//	}

	return 0;
}