#include <iostream>

using namespace std;

#define NAME_SIZE	32
#define ADDRESS_SIZE 128
#define PHONE_SIZE 14
#define STUDENT_MAX 10

struct _tagStudent {
	char	strName[NAME_SIZE];
	char	strAdddress[ADDRESS_SIZE];
	char	strPhoneNumber[PHONE_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

enum MENU {
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT,
};

int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};

	//배열에 추가된 개수를 저장할 변수
	int iStudentCount = 0;
	int iStdNumber = 1;

	char strName[NAME_SIZE] = {};

	while (true) {
		system("cls");

		//Print menu
		cout << "1. 학생등록" << endl;
		cout << "2. 학생삭제" << endl;
		cout << "3. 학생탐색" << endl;
		cout << "4. 학생출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int iMenu;
		cin >> iMenu;

		if (cin.fail()) {
			//Flush error buffer
			cin.clear();

			//Delete \n in input buffer
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MENU_EXIT)
			break;

		switch (iMenu) {
		case MENU_INSERT:
			system("cls");
			cout << "========== 학생 추가 ==========" << endl;

			//If number of saved student is maximum, block new
			//student data.
			if (iStudentCount == STUDENT_MAX)
				break;

			//Insert student data.
			//Student data is name, address, and phone number.
			//After korean, english, and math score Inserted,
			//calculate total score and average score.

			//Recieve name
			cout << "이름 : ";
			cin >> tStudentArr[iStudentCount].strName;
			cin.ignore(1024, '\n');

			//Recieve address
			cout << "주소 : ";
			cin.getline(tStudentArr[iStudentCount].strAdddress, ADDRESS_SIZE);

			//Recieve phone number
			cout << "전화번호 : ";
			cin.getline(tStudentArr[iStudentCount].strPhoneNumber, PHONE_SIZE);

			//Recieve korean score
			cout << "국어 : ";
			cin >> tStudentArr[iStudentCount].iKor;

			//Recieve english score
			cout << "영어 : ";
			cin >> tStudentArr[iStudentCount].iEng;

			//Recieve math score
			cout << "수학 : ";
			cin >> tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].iTotal =
				tStudentArr[iStudentCount].iKor +
				tStudentArr[iStudentCount].iEng +
				tStudentArr[iStudentCount].iMath;
			tStudentArr[iStudentCount].fAvg =
				tStudentArr[iStudentCount].iTotal / 3.f;

			tStudentArr[iStudentCount].iNumber = iStdNumber;
			++iStdNumber;
			++iStudentCount;

			cout << "학생 추가 완료" << endl;

			break;
		case MENU_DELETE:
			system("cls");
			cout << "========== 학생 삭제 ==========" << endl;

			cin.ignore(1024, '\n');
			cout << "삭제할 이름을 입력하세요 : ";
			cin.getline(strName, NAME_SIZE);

			//Search student reapeating as number of saved student
			for (int i = 0; i < iStudentCount; i++) {
				if (strcmp(strName, tStudentArr[i].strName) == 0) {
					for (int j = i; j < iStudentCount - 1; j++) {
						tStudentArr[j] = tStudentArr[j + 1];
					}
					iStudentCount--;

					cout << "학생을 삭제했습니다." << endl;
					break;
				}
			}
			break;
		case MENU_SEARCH:
			system("cls");
			cout << "========== 학생 탐색 ==========" << endl;

			cin.ignore(1024, '\n');
			cout << "탐색할 이름을 입력하세요 : ";
			cin.getline(strName, NAME_SIZE);

			//Search student reapeating as number of saved student
			for (int i = 0; i < iStudentCount; i++) {
				if (strcmp(strName, tStudentArr[i].strName) == 0) {
					cout << "이름 : " << tStudentArr[i].strName << endl;
					cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
					cout << "주소 : " << tStudentArr[i].strAdddress << endl;
					cout << "학번 : " << tStudentArr[i].iNumber << endl << endl;

					cout << "국어 : " << tStudentArr[i].iKor << endl;
					cout << "영어 : " << tStudentArr[i].iEng << endl;
					cout << "수학 : " << tStudentArr[i].iMath << endl;
					cout << "총점 : " << tStudentArr[i].iTotal << endl;
					cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;

					break;
				}
			}
			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "========== 학생 출력 ==========" << endl;

			//Print Student data as repeat as number of saved student
			for (int i = 0; i < iStudentCount; i++) {
				cout << "이름 : " << tStudentArr[i].strName << endl;
				cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
				cout << "주소 : " << tStudentArr[i].strAdddress << endl;
				cout << "학번 : " << tStudentArr[i].iNumber << endl << endl;

				cout << "국어 : " << tStudentArr[i].iKor << endl;
				cout << "영어 : " << tStudentArr[i].iEng << endl;
				cout << "수학 : " << tStudentArr[i].iMath << endl;
				cout << "총점 : " << tStudentArr[i].iTotal << endl;
				cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;

				cout << "==========" << endl;
			}

			break;
		default:
			cout << "메뉴를 잘못 선택했습니다." << endl;
			break;
		}

		system("pause");
	}
	return 0;
}