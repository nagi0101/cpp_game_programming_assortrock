#include <iostream>
#include <string.h>

using namespace std;

#define	NAME_SIZE	32
#define	STORE_WEAPON_MAX	3
#define	STORE_ARMOR_MAX		3
#define	ITEM_DESC_LENGTH	512

enum MAIN_MENU
{
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	//MM_FIX,
	MM_EXIT
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

struct _tagItem
{
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE	eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

// ���� �Է��� �޴´�. �Է� �������� ó�����ְ� INT_MAX��
//�����ϸ� ���� �߻��� ���̴�.
int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;	// INT_MAX�� ���ϵǸ� �Է��� �߸���
	}

	return iInput;
}

void AddItem(_tagItem* pWeaponStore, _tagItem* pArmorStore)
{
	int iStore = 0;
	while (true)
	{
		system("cls");
		cout << "1. �������" << endl;
		cout << "2. ������" << endl;
		cout << "3. ���" << endl;
		cout << "�߰��� ������ �����ϼ��� : ";
		iStore = InputInt();

		if (iStore == 3)
			return;
		else if (iStore < 1 || iStore >3)
			continue;

		//1���� �����̶� 1�� ���ҽ��Ѿ� ���� �ε����� ���´�.
		break;
	}

	int iItemLevel = 0;
	while (true)
	{
		system("cls");
		cout << "1. �ʱ�" << endl;
		cout << "2. �߱�" << endl;
		cout << "3. ���" << endl;
		cout << "4. ���" << endl;
		cout << "�߰��� ������ ���̵��� �����ϼ��� : ";
		iItemLevel = InputInt();

		if (iItemLevel == 4)
			return;
		else if (iItemLevel < 1 || iItemLevel > 4)
			continue;

		//1���� �����̶� 1�� ���ҽ��Ѿ� ���� �ε����� ���´�.
		--iItemLevel;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	_tagItem* pItem = NULL;

	//���ڷ� ����������� ����� ������ �迭�� �� ��������
	//����� ������ �迭 ���� �־��־���. �������� �߰��Ҷ�����
	//�߰��� ������ �����ϰ� �������� ���̵��� �����ߴ�.
	//�׷��Ƿ� �����ϱ� ������ ���⿡�� �߰��� �������� �޸�
	// �ּҸ� ���ͼ� �ű⿡ �߰����ָ� ���� ó�� �����ϴ�.
	if (iStore == SM_WEAPON)
	{
		pItem = &pWeaponStore[iItemLevel];
		pItem->eType = IT_WEAPON;
		strcpy_s(pItem->strTypeName, "����");
	}
	else
	{
		pItem = &pArmorStore[iItemLevel];
		pItem->eType = IT_ARMOR;
		strcpy_s(pItem->strTypeName, "��");
	}
	// ������ �̸��� �Է¹޴´�.
	cout << "�̸� : ";
	cin.getline(pItem->strName, NAME_SIZE - 1);
	cout << "������ ���� : ";
	cin.getline(pItem->strDesc, ITEM_DESC_LENGTH - 1);

	cout << "�ּҴɷ�ġ : ";
	pItem->iMin = InputInt();
	cout << "�ִ�ɷ�ġ : ";
	pItem->iMax = InputInt();
	cout << "���Ű� : ";
	pItem->iPrice = InputInt();
	cout << "�ǸŰ� : ";
	pItem->iSell = InputInt();

	cout << "������ �߰� �Ϸ�" << endl;
	system("pause");
}

bool SaveStore(_tagItem* pWeapon, _tagItem* pArmor)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Store.str", "wb");

	if (pFile)
	{
		fwrite(pWeapon, sizeof(_tagItem), STORE_WEAPON_MAX, pFile);
		fwrite(pArmor, sizeof(_tagItem), STORE_ARMOR_MAX, pFile);
		fclose(pFile);
		return true;
	}
	return false;
}

bool LoadStore(_tagItem* pWeapon, _tagItem* pArmor)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Store.str", "rb");

	if (pFile)
	{
		fread(pWeapon, sizeof(_tagItem), STORE_WEAPON_MAX, pFile);
		fread(pArmor, sizeof(_tagItem), STORE_ARMOR_MAX, pFile);
		fclose(pFile);
		return true;
	}
	return false;
}

void Output(_tagItem* pWeapon, _tagItem* pArmor)
{
	system("cls");

	cout << "================== Store ==================" << endl;
	for (int i = 0; i < STORE_WEAPON_MAX; i++)
	{
		cout << i + 1 << ". �̸� : " << pWeapon[i].strName <<
			"\t���� : " << pWeapon[i].strTypeName << endl;
		cout << "���ݷ� : " << pWeapon[i].iMin << " - " <<
			pWeapon[i].iMax << endl;
		cout << "�ǸŰ��� : " << pWeapon[i].iPrice <<
			"\t���Ű��� : " << pWeapon[i].iSell << endl;
		cout << "���� : " << pWeapon[i].strDesc << endl << endl;
	}
	for (int i = 0; i < STORE_ARMOR_MAX; i++)
	{
		cout << i + 1 << ". �̸� : " << pArmor[i].strName <<
			"\t���� : " << pArmor[i].strTypeName << endl;
		cout << "���� : " << pArmor[i].iMin << " - " <<
			pArmor[i].iMax << endl;
		cout << "�ǸŰ��� : " << pArmor[i].iPrice <<
			"\t���Ű��� : " << pArmor[i].iSell << endl;
		cout << "���� : " << pArmor[i].strDesc << endl << endl;
	}
	system("pause");
}
/*
void Fix(_tagItem* pWeapon, _tagItem* pArmor)
{
	_tagItem tTemp[STORE_ARMOR_MAX] = {};
	for (int i = 0; i < STORE_ARMOR_MAX; ++i)
	{
		tTemp[i] = pWeapon[i];
		pWeapon[i] = pArmor[i];
		pArmor[i] = tTemp[i];
		strcpy_s(pWeapon[i].strTypeName, NAME_SIZE, "����");
		strcpy_s(pArmor[i].strTypeName, NAME_SIZE, "��");
	}
	cout << "Fix Done!" << endl;
	system("pause");
}
*/
int main()
{
	_tagItem tWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tArmor[STORE_ARMOR_MAX] = {};

	while (true)
	{
		system("cls");
		cout << "1. ������ �߰�" << endl;
		cout << "2. �о����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ������ ���" << endl;
		//cout << "5. �����ġ" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		int iMenu = InputInt();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_ADD:
			AddItem(tWeapon, tArmor);
			break;
		case MM_LOAD:
			LoadStore(tWeapon, tArmor);
			break;
		case MM_SAVE:
			SaveStore(tWeapon, tArmor);
			break;
		case MM_OUTPUT:
			Output(tWeapon, tArmor);
			break;
			/*
		case MM_FIX:
			Fix(tWeapon, tArmor);
			break;
			*/
		}
	}

	//�ڵ� ������
	SaveStore(tWeapon, tArmor);

	return 0;
}