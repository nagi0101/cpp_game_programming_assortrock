#include <iostream>

using namespace std;

int main() {
	const int iAttack = 0x00000001;	//     1
	const int iArmor = 0x00000002;	//    10
	const int iHp = 0x00000004;		//   100
	const int iMp = 0x00000008;		//  1000
	const int iCrit = 0x00000010;	// 10000

	// 1 | 100 = 101 | 10000 = 10101
	int iBuf = iAttack | iHp | iCrit;

	iBuf ^= iHp;

	cout << "Attack : " << (iBuf & iAttack) << endl;
	cout << "Armor : " << (iBuf & iArmor) << endl;
	cout << "Hp : " << (iBuf & iHp) << endl;
	cout << "Mp : " << (iBuf & iMp) << endl;
	cout << "Crit : " << (iBuf & iCrit) << endl;

	return 0;
}