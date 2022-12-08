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
				cout << "����� ���������" << endl;
			}
			else
				isNotOk = 0;
		}
		return number;
	}

	//����������� ��� ����������
	WeatherDiary()
	{
		data = 0;
		cloudiness = " ";
		napravlenie = " ";
		temperature = 0;
		pressure = 0;

	}

	//����������� � �����������
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

	//����������
	~WeatherDiary() {}

	//����������
	string GetCloudiness() { return cloudiness; }
	void SetCloudiness(string value) { cloudiness = value; }

	//�����������
	string GetNapravlenie() { return napravlenie; }
	void SetNapravlenie(string value) { napravlenie = value; }

	//����
	int GetData() { return data; }
	void SetData(int value) { data = value; }

	//��������
	int GetPressure() { return pressure; }
	void SetPressure(int value) { pressure = value; }

	//�����������
	int GetTemperature() { return temperature; }
	void SetTemperature(int value) { temperature = value; }

	//����������� �����������
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
		data = Input_int("������� ����");
	
		cout << "������� ������� ����������: ";
		cin >> cloudiness;

		cout << "������� ����������� �����: ";
		cin >> napravlenie;

		temperature = Input_int("������� �����������");
		pressure = Input_int("������� ��������");

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
			cout << "1 - ������������ �����" << endl
				<< "2 - �����������" << endl
				<< "3 - ����������" << endl
				<< "4 - ��������" << endl
				<< "5 - ����" << endl
				<< "6 - ������" << endl;
			choice = Input_int("�������� ����� ���� �� ������ �������������");
			switch (choice)
			{
			case 1:
				cout << "������� ����� ����������� �����: ";
				cin >> napravlenie;
				break;
			case 2:
				cout << "������� ����� �����������: ";
				cin >> temperature;
				break;
			case 3:
				cout << "������� ����� ����������: ";
				cin >> cloudiness;
				break;
			case 4:
				cout << "������� ����� ��������: ";
				cin >> pressure;
				break;
			case 5:
				cout << "������� ����� ����: ";
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
		basis = Input_int("������� ����������� ��� ������");

		for (int i = 0; i < records.size(); i++)
		{
			if (basis == records[i].temperature)
			{
				cout << "���������� � ������� " + to_string(i + 1) << endl;
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
//������� ����� ����������




