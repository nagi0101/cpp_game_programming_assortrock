#include <iostream>

using namespace std;

#include "DLL.h"

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_OUTPUTREV,
	MM_EXIT
};

int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}
	return iInput;
}

void InputString(char* pString, int iSize)
{
	cin.clear();
	cin.ignore(1024, '\n');

	cin.getline(pString, iSize - 1);
}

void Insert(PLIST pList)
{
	system("cls");
	cout << "================ �л��߰� ================" << endl;
	STUDENT tStudent = {};

	cout << "�̸� : ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "�й� : ";
	tStudent.iNumber = InputInt();
	cout << "���� : ";
	tStudent.iKor = InputInt();
	cout << "���� : ";
	tStudent.iEng = InputInt();
	cout << "���� : ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	//�߰��� ����Ʈ ��� ����
	PNODE	pNode = new NODE;

	/*���� �߰��ϴ� ���� ���� �������� �߰��Ǳ� ������
	���� ��� NULL�� �ʱ�ȭ.
	*/
	pNode->pNext = NULL;
	pNode->pPrev = NULL;
	pNode->tStudent = tStudent;

	//ó�� ����� �� pBegin�� pNode�� ����
	if (pList->pBegin == NULL)
		pList->pBegin = pNode;
	//ó�� ��尡 �ƴ� �� pNode�� ���� ��带 pEnd��,
	//pEnd�� ���� ���� pNode�� ����.
	else
	{
		pNode->pPrev = pList->pEnd;
		pList->pEnd->pNext = pNode;
	}

	pList->pEnd = pNode;
	pList->iSize++;
}

int OutputMenu()
{
	system("cls");

	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л�Ž��" << endl;
	cout << "4. �л����" << endl;
	cout << "5. �л����(����)" << endl;
	cout << "6. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput == INT_MAX)
		return MM_NONE;

	return iInput;
}

//const �������̱⿡ �� ���� �Ұ�
void OutputStudent(const PSTUDENT pStudent)
{
	cout << "�̸� : " << pStudent->strName << "\t�й� : " << pStudent->iNumber << endl;
	cout << "���� : " << pStudent->iKor << "\t���� : " << pStudent->iEng << endl;
	cout << "���� : " << pStudent->iMath << endl;
	cout << "���� : " << pStudent->iTotal << "\t��� : " << pStudent->fAvg << endl;
	cout << endl;
}

void Output(const PLIST pList)
{
	system("cls");
	cout << "================ �л���� ================" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}

	cout << "�л��� : " << pList->iSize << endl;

	system("pause");
}

void OutputReverse(const PLIST pList)
{
	system("cls");
	cout << "================ �л����(����) ================" << endl;

	PNODE pNode = pList->pEnd;

	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pPrev;
	}

	cout << "�л��� : " << pList->iSize << endl;

	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "================ �л�Ž�� ================" << endl;

	cout << "Ž���� �̸��� �Է��ϼ��� : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}
	cout << "ã�� �л��� �����ϴ�." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "================ �л����� ================" << endl;

	cout << "������ �̸��� �Է��ϼ��� : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			cout << strName << " �л� ����" << endl;
			//���� ����� ���� ��� ���´�
			PNODE pNext = pNode->pNext;
			//���� ��尡 ������ ���� ù��° ��带 ����� ��
			if (pNode->pPrev == NULL)
			{
				pList->pBegin = pNext;

				//���� ��尡 ������
				if (pNext == NULL)
					pList->pEnd = NULL;
				delete pNode;
			}
			//���� ��尡 ���� ��� ���� ����� ������ ���� ����� ���� ���� ����
			else
			{
				pNode->pPrev->pNext = pNext;

				//������ ����� ��
				if (pNext == NULL)
					pList->pEnd = pNode->pPrev;
				delete pNode;
			}
			cout << strName << " �л� ���� �Ϸ�!" << endl;

			--pList->iSize;
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}
	cout << "������ �л��� �����ϴ�." << endl;
	system("pause");
}

int main()
{
	LIST	tList;

	InitList(&tList);

	while (true)
	{
		int iMenu = OutputMenu();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_INSERT:
			Insert(&tList);
			break;
		case MM_DELETE:
			Delete(&tList);
			break;
		case MM_SEARCH:
			Search(&tList);
			break;
		case MM_OUTPUT:
			Output(&tList);
			break;
		case MM_OUTPUTREV:
			OutputReverse(&tList);
			break;
		}
	}

	DestroyList(&tList);
}