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
				cout << "Вводи нормально" << endl;
			}
			else
				isNotOk = 0;
		}
		return number;
	}

	void menu()
	{

		string filename = "D:/ПРОГЕРСТВО/C++/KYRSACH/KYRSACH/UserData.bin";
		ifstream fin(filename, ios::binary);
		ofstream outfile(filename, ios::binary);


		if (!fin.is_open()) cout << "Файл не открывается!\n";
		else { cout << "Файл открыт,нормальненько!\n"; }



		List<User> listUsers;

		int choice = 0;

		cout << "Выберете действие которое хотите произвести" << endl;
		while (choice != 6) {

			User temp;

			cout<< "1 - Внести пользователя" << endl
				<< "2 - Вывести данные на экран" << endl
				<< "3 - Чтение данных из файла" << endl
				<< "4 - Удалить пользователя" << endl
				<< "5 - Использовать полно-функциональное меню дненвника" << endl
				<< "6 - Выход" << endl<< endl;
			choice = Input_int("Ваш выбор");

			switch (choice)
			{
			case 1:
				temp.NewUser();
				temp.WriteToFile(outfile);
				listUsers.PushBack(temp);
				break;
			case 2:
				listUsers.PrintRoles("Ваши пользователи: ");
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
				cout << "данные из файла внесены" << endl;
				break;
					
			case 4:
			{
				int number = Input_int("Введите номер пользователя которого хотите удалить, всего");
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