#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <iterator>
#include <iomanip>
#include <fstream>





class User
{
public:
	string login;
	string pass;
	string role;

	User()
	{
		login = "rapkup";
		pass = "228";
		role = "Admin";
	}

	User(string login, string pass, string role)
	{
		this->login = login;
		this->pass = pass;
		this->role = role;
	}

	bool Login(string login, string pass, User registerUser, User currentUser)
	{
		bool isUser = false;

		if ((this->login == login) && (this->pass == pass))
		{
			isUser = true;
			currentUser = registerUser;
			cout << "Вход выполнен" << endl;
			//return true;
			//cout << "Ошибка: неверно введен логин или пароль";
		}
		//return false;
		return isUser;
	}

	void NewUser()
	{
		cout << "Введите информацию о новом Пользователе" << endl;
		cout << "Логин: ";  cin >> login; cout << endl;
		cout << "Пароль: "; cin >> pass; cout << endl;
		cout << "Роль: "; cin >> role; cout << endl;
	}

	User Vxodim(User registerUser)
	{
		User currentUser;
		string log; string pass;

		cout << "Введите информацию о Юзере" << endl;;
		cout << "Логин: ";  cin >> log;
		cout << "Пароль: "; cin >> pass;


		if (Login(log, pass, registerUser, currentUser))
		{
			cout << "Нихао " << log << endl;
		}
		else
			cout << "Ошибка: неверно введен логин или пароль\n";
		return(currentUser);
	};

	void WriteToFile(ofstream& outfile)
	{

		size_t count = login.length();
		outfile.write(reinterpret_cast<char*>(&count), sizeof(count));
		outfile.write(login.c_str(), count + 1);

		size_t count2 = pass.length();
		outfile.write(reinterpret_cast<char*>(&count2), sizeof(count2));
		outfile.write(pass.c_str(), count2 + 1);

		size_t count3 = role.length();
		outfile.write(reinterpret_cast<char*>(&count3), sizeof(count3));
		outfile.write(role.c_str(), count3 + 1);



		outfile.close();
	}

	void ReadFromFile(ifstream& infile)
	{

		size_t count;
		infile.read(reinterpret_cast<char*>(&count), sizeof(count));
		char* str = new char[count + 1];

		infile.read(str, count + 1);
		login = str;
		delete str;

		size_t count2;
		infile.read(reinterpret_cast<char*>(&count2), sizeof(count2));
		char* str2 = new char[count2 + 1];
		infile.read(str2, count2 + 1);
		pass = str2;
		delete str2;


		size_t count3;
		infile.read(reinterpret_cast<char*>(&count3), sizeof(count3));
		char* str3 = new char[count3 + 1];
		infile.read(str3, count3 + 1);
		role = str3;
		delete str3;

	}

	void Print()
	{
		cout << "|" << setw(17) << login << "|"
					<< setw(16) << pass << "|"
					<< setw(17) << role << "|" << endl;
	}
	



};




