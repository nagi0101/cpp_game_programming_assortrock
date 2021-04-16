#include <iostream>
#include <string.h>

using namespace std;

#define NAME_SIZE 32

struct _tagStudent {
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

int main() {
	_tagStudent tStudent = {};
	_tagStudent tStudentArr[100] = {};

	tStudent.iKor = 100;

	strcpy_s(tStudent.strName, "sdfahdgfsd");

	return 0;
}