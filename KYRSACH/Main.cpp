#include "MenuAdmin.h"
#include "MenuUser.h"
#include "ListDouble.h"
#include "WeatherDiary.h"
#include "Roles.h"





int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	 system("color 3F");

	



	WeatherDiary zapisi[] = {
		WeatherDiary("����������� ", "������-��������", 12, 30, 1000),
		WeatherDiary("���������", "�����", 14, 4000, 900),
		WeatherDiary("�����������", "���������",16, 3000, 800),
		WeatherDiary("������-��������", "���-�������", 18, 12, 700),
		WeatherDiary("��������", "��������",20, 12, 500),
		WeatherDiary("�������������", "�������-���������",22, 3000, 600),
		WeatherDiary("�������", "��������",24, 3000, 400),
		WeatherDiary("�������-��������", "���-���������",26, 3000, 300),
		WeatherDiary("�������-��������", "���������",28, 3000, 200),
		WeatherDiary("�����������", "��������",30, 3000, 100)
	};
	int size = _countof(zapisi);
	WeatherDiary tmp;

	List<WeatherDiary> list;
	for (int i = 0; i < size; i++)
	{
		list.PushBack(zapisi[i]);
	}


	/*MenuAdmin* menuAdmin = new MenuAdmin;
	menuAdmin->menu();*/

	/*list.PrintDiary("");*/



	User* newUser = new User;
	newUser->Vxodim(User()/*("rapkup","228","Admin")*/);


	if(newUser->role == "Admin" && "admin")
	{
		MenuAdmin* menuAdmin = new MenuAdmin;
		menuAdmin->menu();

		delete menuAdmin;
	}
	else 
	{
		if (newUser->role == "User" && "user")
		{
			MenuUser* menuUser = new MenuUser;
			menuUser->menu();
			delete menuUser;
		}
		else
		{
			cout << "������ ������������ �� ����������" << endl;
		}
	}
	




	



	system("pause");
}
