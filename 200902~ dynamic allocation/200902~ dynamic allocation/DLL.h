#pragma once

#include <iostream>

using namespace std;

#define NAME_SIZE 32

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
}STUDENT, * PSTUDENT;

typedef struct _tagNode
{
	STUDENT tStudent;
	_tagNode* pNext;
	_tagNode* pPrev;
}NODE, * PNODE;

typedef struct _tagList
{
	PNODE	pBegin;
	PNODE	pEnd;
	int		iSize;
}LIST, * PLIST;

void InitList(PLIST pList);
void ClearList(PLIST pList);
void DestroyList(PLIST pList);