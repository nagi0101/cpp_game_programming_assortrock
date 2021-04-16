#include "DLL.h"

void InitList(PLIST pList)
{
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

void ClearList(PLIST pList)
{
	PNODE	pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
}

void DestroyList(PLIST pList)
{
	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}