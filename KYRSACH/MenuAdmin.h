#pragma once

#include "ListDouble.h"
#include "Roles.h"
#include "MenuAdminDiary.h"



class MenuAdmin
{




public:

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
		while (choice != 6) {

			User temp;

			cout<< "1 - ������ ������������" << endl
				<< "2 - ������� ������ �� �����" << endl
				<< "3 - ������ ������ �� �����" << endl
				<< "4 - ������� ������������" << endl
				<< "5 - ������������ �����-�������������� ���� ���������" << endl
				<< "6 - �����" << endl<< endl;
			choice = Input_int("��� �����");

			switch (choice)
			{
			case 1:
				temp.NewUser();
				temp.WriteToFile(outfile);
				listUsers.PushBack(temp);
				break;
			case 2:
				listUsers.PrintRoles("���� ������������: ");
				break;

			case 3:
				size_t fileSize;
				fin.seekg(0, ios::end);
				fileSize = fin.tellg();
				fin.seekg(ios::beg);

				while (fin.tellg() < fileSize)
				{
					temp.ReadFromFile(fin);
					listUsers.PushBack(temp);
				};
				cout << "������ �� ����� �������" << endl;
				break;
					
			case 4:
			{
				int number = Input_int("������� ����� ������������ �������� ������ �������, �����");
				listUsers.Del(number);

			}
			case 5: 
				{
				MenuAdminDiary* menuAdminDiary = new MenuAdminDiary;
				menuAdminDiary->menu();
				break;
				}
				
			default:
				break;
			}
		}
	}
};