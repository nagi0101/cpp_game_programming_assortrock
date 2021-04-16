#include <iostream>

using namespace std;

class CParent
{
public:
	CParent()
	{
		cout << "CParent 생성자" << endl;
	}
	~CParent()
	{
		cout << "CParent 소멸자" << endl;
	}

public:
	int m_iA;
	void Output()
	{
		cout << "A : " << m_iA << endl;
		cout << "B : " << m_iB << endl;
		cout << "C : " << m_iC << endl;
	}
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
	~CChild()
	{
		cout << "CChild 소멸자" << endl;
	}
protected:
	int m_iD;
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
	CParent* pParentArr[2] = {};
	pParentArr[0] = new CChild;
	pParentArr[1] = new CChildChild;

	for (int i = 0; i < 2; ++i)
	{
		delete pParentArr[i];
	}
}