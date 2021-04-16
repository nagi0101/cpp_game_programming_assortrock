#include <iostream>
#include "FileStream.h"

using namespace std;

int main()
{
	char m_cStage[10][50];
	CFileStream file;

	file.Open("stage1.txt", "rt");

	for (int i = 0; i < 10; ++i)
	{
		int iSize = 0;
		file.ReadLine(m_cStage[i], iSize);

		for (int j = 0; j < 50; ++j)
		{
			cout << m_cStage[i][j];
		}
		cout << endl;
	}
	cout << endl << endl;

	return 0;
}