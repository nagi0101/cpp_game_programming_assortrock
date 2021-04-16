#include <iostream>

using namespace std;

class CParent
{
public:
	CParent()
	{
		cout << "CParent ������" << endl;
	}
	~CParent()
	{
		cout << "CParent �Ҹ���" << endl;
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
		//m_iC�� private�̱⿡ �ڽ� ���ο����� ���� �Ұ���
		cout << "CChild ������" << endl;
	}
	~CChild()
	{
		cout << "CChild �Ҹ���" << endl;
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
		cout << "CChildChild ������" << endl;
	}
	~CChildChild()
	{
		cout << "CChildChild �Ҹ���" << endl;
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