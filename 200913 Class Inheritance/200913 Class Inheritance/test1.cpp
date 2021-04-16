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
	int m_iC = 300;
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

int main() {
	CParent* pParent = new CChild;
	CChild* pChild = NULL;
	pChild = (CChild*)pParent;

	pParent->m_iA = 100;

	delete pChild;
	pParent = NULL;
	pChild = NULL;

	return 0;
}