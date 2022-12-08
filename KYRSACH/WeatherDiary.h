#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;



class WeatherDiary
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

	//конструктор без параметров
	WeatherDiary()
	{
		data = 0;
		cloudiness = " ";
		napravlenie = " ";
		temperature = 0;
		pressure = 0;

	}

	//конструктор с параметрами
	WeatherDiary(const string cloudiness, const string direction,
		int data, int temperature, int pressure)
	{
		this->cloudiness = cloudiness;

		this->napravlenie = direction;

		this->data = data;

		this->temperature = temperature;

		this->pressure = pressure;

	}

	WeatherDiary(const WeatherDiary& obj)
	{
		cloudiness = obj.cloudiness;
		napravlenie = obj.napravlenie;
		data = obj.data;
		temperature = obj.temperature;
		pressure = obj.pressure;

	}

	//деструктор
	~WeatherDiary() {}

	//облачность
	string GetCloudiness() { return cloudiness; }
	void SetCloudiness(string value) { cloudiness = value; }

	//направление
	string GetNapravlenie() { return napravlenie; }
	void SetNapravlenie(string value) { napravlenie = value; }

	//дата
	int GetData() { return data; }
	void SetData(int value) { data = value; }

	//давление
	int GetPressure() { return pressure; }
	void SetPressure(int value) { pressure = value; }

	//температура
	int GetTemperature() { return temperature; }
	void SetTemperature(int value) { temperature = value; }

	//конструктор копирования
	WeatherDiary& operator=(const WeatherDiary& obj)
	{
		if (this == &obj) return*this;

		cloudiness = obj.cloudiness;
		napravlenie = obj.napravlenie;

		data = obj.data;
		temperature = obj.temperature;
		pressure = obj.pressure;
		return *this;
	}


	void print()
	{
		cout << "|" << setw(20) << GetCloudiness() << "|"
			 << setw(23) << GetNapravlenie() << "|"
			 << setw(19) << to_string(temperature) << "|"
			 << setw(14) << to_string(pressure) << "|"
			 << setw(12) << to_string(data) << "|" << endl;
	}

	void getData()
	{
		data = Input_int("Введите дату");
	
		cout << "Введите степень облачности: ";
		cin >> cloudiness;

		cout << "Введите направление ветра: ";
		cin >> napravlenie;

		temperature = Input_int("Введите температуру");
		pressure = Input_int("Введите давление");

		cout << endl;
	}


	void WriteToFile(ofstream& outfile)
	{

		size_t count = cloudiness.length();
		outfile.write(reinterpret_cast<char*>(&count), sizeof(count));
		outfile.write(cloudiness.c_str(), count + 1);

		size_t count2 = napravlenie.length();
		outfile.write(reinterpret_cast<char*>(&count2), sizeof(count2));
		outfile.write(napravlenie.c_str(), count2 + 1);

		outfile.write(reinterpret_cast<char*>(&data), sizeof(data));
		outfile.write(reinterpret_cast<char*>(&temperature), sizeof(temperature));
		outfile.write(reinterpret_cast<char*>(&pressure), sizeof(pressure));
		outfile.close();
	}

	void ReadFromFile(ifstream& infile)
	{

		size_t count;
		infile.read(reinterpret_cast<char*>(&count), sizeof(count));
		char* str = new char[count + 1];

		infile.read(str, count + 1);
		cloudiness = str;
		delete str;

		size_t count2;
		infile.read(reinterpret_cast<char*>(&count2), sizeof(count2));
		char* str2 = new char[count2 + 1];
		infile.read(str2, count2 + 1);
		napravlenie = str2;
		delete str2;

		infile.read(reinterpret_cast<char*>(&data), sizeof(data));
		infile.read(reinterpret_cast<char*>(&temperature), sizeof(temperature));
		infile.read(reinterpret_cast<char*>(&pressure), sizeof(pressure));


	}

	void EditFile()
	{
		int choice = 0;

		while (choice != 6) {
			cout << "1 - Направвление ветра" << endl
				<< "2 - Температура" << endl
				<< "3 - Облачность" << endl
				<< "4 - Давление" << endl
				<< "5 - Дата" << endl
				<< "6 - Ничего" << endl;
			choice = Input_int("Выберете какое поле вы будете редактировать");
			switch (choice)
			{
			case 1:
				cout << "Введите новую направление ветра: ";
				cin >> napravlenie;
				break;
			case 2:
				cout << "Введите новую температуру: ";
				cin >> temperature;
				break;
			case 3:
				cout << "Введите новую облачность: ";
				cin >> cloudiness;
				break;
			case 4:
				cout << "Введите новую давление: ";
				cin >> pressure;
				break;
			case 5:
				cout << "Введите новую дату: ";
				cin >> data;
				break;
			default:
				break;
			}
		}
	}

	void SearchInFile(vector<WeatherDiary> records)
	{
		int basis;
		basis = Input_int("Введите температуру для поиска");

		for (int i = 0; i < records.size(); i++)
		{
			if (basis == records[i].temperature)
			{
				cout << "Совпадение с записью " + to_string(i + 1) << endl;
			}
		}
	}


private:

	int data;
	string cloudiness;
	string napravlenie;
	int temperature;
	int pressure;

};
//Простой вывод информации




