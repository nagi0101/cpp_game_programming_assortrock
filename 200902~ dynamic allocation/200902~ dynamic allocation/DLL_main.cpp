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
	cout << "================ 학생추가 ================" << endl;
	STUDENT tStudent = {};

	cout << "이름 : ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "학번 : ";
	tStudent.iNumber = InputInt();
	cout << "국어 : ";
	tStudent.iKor = InputInt();
	cout << "영어 : ";
	tStudent.iEng = InputInt();
	cout << "수학 : ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	//추가할 리스트 노드 생성
	PNODE	pNode = new NODE;

	/*현재 추가하는 노드는 가장 마지막에 추가되기 때문에
	다음 노드 NULL로 초기화.
	*/
	pNode->pNext = NULL;
	pNode->pPrev = NULL;
	pNode->tStudent = tStudent;

	//처음 노드일 때 pBegin을 pNode로 설정
	if (pList->pBegin == NULL)
		pList->pBegin = pNode;
	//처음 노드가 아닐 때 pNode의 이전 노드를 pEnd로,
	//pEnd의 다음 노드는 pNode로 설정.
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

	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 학생출력(역순)" << endl;
	cout << "6. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput == INT_MAX)
		return MM_NONE;

	return iInput;
}

//const 포인터이기에 값 변경 불가
void OutputStudent(const PSTUDENT pStudent)
{
	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << "\t영어 : " << pStudent->iEng << endl;
	cout << "수학 : " << pStudent->iMath << endl;
	cout << "총점 : " << pStudent->iTotal << "\t평균 : " << pStudent->fAvg << endl;
	cout << endl;
}

void Output(const PLIST pList)
{
	system("cls");
	cout << "================ 학생출력 ================" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}

	cout << "학생수 : " << pList->iSize << endl;

	system("pause");
}

void OutputReverse(const PLIST pList)
{
	system("cls");
	cout << "================ 학생출력(역순) ================" << endl;

	PNODE pNode = pList->pEnd;

	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pPrev;
	}

	cout << "학생수 : " << pList->iSize << endl;

	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "================ 학생탐색 ================" << endl;

	cout << "탐색할 이름을 입력하세요 : ";
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
	cout << "찾을 학생이 없습니다." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "================ 학생삭제 ================" << endl;

	cout << "삭제할 이름을 입력하세요 : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			cout << strName << " 학생 삭제" << endl;
			//지울 노드의 다음 노드 얻어온다
			PNODE pNext = pNode->pNext;
			//이전 노드가 없으면 제일 첫번째 노드를 지우는 것
			if (pNode->pPrev == NULL)
			{
				pList->pBegin = pNext;

				//다음 노드가 없으면
				if (pNext == NULL)
					pList->pEnd = NULL;
				delete pNode;
			}
			//이전 노드가 있을 경우 이전 노드의 다음을 지운 노드의 다음 노드로 연결
			else
			{
				pNode->pPrev->pNext = pNext;

				//마지막 노드일 때
				if (pNext == NULL)
					pList->pEnd = pNode->pPrev;
				delete pNode;
			}
			cout << strName << " 학생 삭제 완료!" << endl;

			--pList->iSize;
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}
	cout << "삭제할 학생이 없습니다." << endl;
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