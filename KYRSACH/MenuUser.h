#pragma once

#include "ListDouble.h"
#include "Roles.h"	
#include "MenuUserDiary.h"

int Input_int(const string ch)
{
	int isNotOk = 1;
	int number = 0;
	cout << ch + ": " << endl;
	while (isNotOk)
	{
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "����� ���������" << endl;
		}
		else
			isNotOk = 0;
	}
	return number;
}


class MenuUser
{




public:
	void menu()
	{
		string filename = "D:/����������/C++/KYRSACH/KYRSACH/UserData.bin";
		ifstream fin(filename, ios::binary);
		ofstream outfile(filename, ios::binary);


		if (!fin.is_open()) cout << "���� �� �����������!\n";
		else { cout << "���� ������,�������������!\n"; }


		List<User> listUsers;

		int choice = 0;

		cout << "�������� �������� ������� ������ ����������" << endl;
		while (choice != 6)
		{

			User temp;
				
			cout<< "1 - ������ ������ ��������" << endl
				<< "2 - �����" << endl;
			choice = Input_int("��� �����");

			switch (choice)
			{
			case 1:
				{
				MenuUserDiary* menuUserDiary = new MenuUserDiary;
				menuUserDiary->menu();
				}
				break;

			default:
				break;
			}

		}

	}

};