#pragma once

#include "ListDouble.h"
#include "WeatherDiary.h"

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

class MenuAdminDiary
{

public:  static void menu()
{
		string filename = "D:/����������/C++/KYRSACH/KYRSACH/TextSource.bin";
		ifstream fin(filename, ios::binary);
		ofstream outfile(filename, ios::binary);


		if (!fin.is_open()) cout << "���� �� �����������!\n";
		else { cout << "���� ������,�������������!\n"; }



		List<WeatherDiary> list;

		int choice = 0;

		cout << "�������� �������� ������� ������ ����������" << endl;
		while (choice != 6) {
			WeatherDiary tmp;

			cout << "1 - ������ ������" << endl
				<< "2 - ����� ������ �� �����" << endl
				<< "3 - ������������� ��������� ������" << endl
				<< "4 - ����� �� ���������� ����������� " << endl
				<< "5 - ������ ������ �� �����" << endl
				<< "6 - �����" << endl << endl;
			choice = Input_int("��� �����");

			switch (choice)
			{
			case 1:
				tmp.getData();

				tmp.WriteToFile(outfile);
				list.PushBack(tmp);
				break;
			case 2:
				list.PrintDiary("��� ������");
				break;
			case 3:

				while (!fin.eof())
				{
					tmp.ReadFromFile(fin);
					list.PushBack(tmp);
					if (list.Size() > 1)
					{
						int num;
						num = Input_int("������� ����� ������, ������� ������ ���������������");
						list.GetElement(num).EditFile();
						tmp.WriteToFile(outfile);
					}
					list.GetElement(0).EditFile();
				}
				break;
			case 4:

				while (!fin.eof())
				{
					tmp.ReadFromFile(fin);
					list.PushBack(tmp);
				}
				list.Search();
				break;
			case 5:
				size_t fileSize;
				fin.seekg(0, ios::end);
				fileSize = fin.tellg();
				fin.seekg(ios::beg);

				while (fin.tellg() < fileSize)
				{
					tmp.ReadFromFile(fin);
					list.PushBack(tmp);
				};
				cout << "������ �� ����� �������" << endl;
				break;
			

			default:
				break;
			}
		}
}
};