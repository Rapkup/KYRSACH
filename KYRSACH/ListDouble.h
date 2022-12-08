#pragma once 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <iterator>
#include <iomanip>
#include <stdlib.h>
#include <iostream>


	using namespace std;

	// ���������, ����������� ���� ������� (����)
	template <class T>
	struct Element
	{
		T data; // ������
		Element<T>* next; // ����� ���������� �������� � ������
		Element<T>* prev; // ����� ����������� �������� � ������
	};

	// ����, ����������� ���������� ������
	template <class T>
	class List
	{
	private:
		Element<T>* begin; // ��������� �� ������ ������� ������
		Element<T>* end; // ��������� �� ��������� ������� ������
		int count; // ���������� ��������� � ������

		// �����, ������������ ������� � �������� �������,
		// ��������� ��� ������� ���������.
		Element<T>* Move(int index)
		{
			// 1. ���������� ��������� �� ������ ������
			Element<T>* t = begin;

			// 2. ���������� � ������� index
			for (int i = 0; i < index; i++)
				t = t->next;

			// 3. ������� ���������
			return t;
		}

		// �����, ���������� ������
		void Copy(const List<T>& obj)
		{
			// 1. �������� ������ (���������� ������)
			Clear();

			// 2. ���� ����������� this <= obj
			Element<T>* t = obj.begin;

			while (t != nullptr)
			{
				PushBack(t->data);
				t = t->next;
			}
		}


		// �����, ����������� ������������ ������ (�������) � ������
		bool CorrectIndex(int index)
		{
			return (index >= 0) && (index < count);

		}	

	public:
		

		// �����������
		//template <class T>
		List() 
		{
			
			// ������� ������ ������
			begin = end = nullptr;
			count = 0;
		}

		// ����������� �����������
		List(const List& obj)
		{
			// ������� ����� �� ������
			Copy(obj);
		}

		// �������� �����������
		List<T>& operator=(const List& obj)
		{
			Copy(obj);
			return *this;
		}


		// ����������
		~List()
		{
			Clear(); // �������� ������
		}


		// ---------- ������ ������� � ��������� ��������� ������ --------
		// �������� ������� ������ �� �������
		T GetElement(int index)
		{
			// ��������, ��������� �� ������,
			// ���� ������ �� ���������, ������������� ����������
			if (!CorrectIndex(index))
				throw out_of_range("Incorrect index.");

			// ���� ������ ���������, �� ������� �������
			Element<T>* t = Move(index);
			return t->data;
		}


		// �������� �������� �������� � �������� �������
		void SetElement(T _data, int index)
		{
			// ��������, ��������� �� �������
			if (!CorrectIndex(index))
				return;

			// �������� ������� �� ������� � �������� ��� ��������
			Element<T>* t = Move(index);
			t->data = _data;
		}


		// ---------- ������ ��������� ������� ������ ------------
		// �������� ������� � ����� ������
		void PushBack(T _data)
		{
			try
			{
				// 1. ������� ����� ������� � ������� _data
				Element<T>* t = new Element<T>;
				t->next = nullptr; // ���������� �������� ���
				t->prev = end; // ���������� ���������� �������
				t->data = _data; // �������� ������

				// 2. ��������� ���� next ���� ��� ���������� ��������
				if (end != nullptr)
					end->next = t;

				// 3. ��������, ���� �� � ������ ��������
				if (count == 0)
				{
					// ���� ��������� ���,
					// �� ��� ������������ � ������ � ����� ������
					begin = end = t;
				}
				else
				{
					// ���� �������� � ������ ����, �� ��� ����� ������
					end = t;
				}

				// 4. ��������� ����� ���������� ���������
				count++;
			}
			catch (bad_alloc e)
			{
				// ���� ������ �� ��������, �� ������� ��������� ���������
				cout << e.what() << endl;
			}

		}


		// �������� ������� � ������ ������
		void PushFront(T _data)
		{
			try
			{
				// 1. ������� ����� ������� (����� ������ ������)
				// � ��������� ��� �������
				Element<T>* t = new Element<T>;
				t->data = _data; // ������
				t->prev = nullptr; // ����������� �������� ���

				// ��������� ������� ��������� �� ���������� ������
				t->next = begin;

				// 2. ���� �� �������� � ������?
				if (count > 0)
				{
					// ���� ����, �� ������������� ���������� ������ ������
					begin->prev = t;
					begin = t;
				}
				else
				{
					// ���� ��������� ���, �� ������ � ����� ���� ��� ����� ���������
					begin = end = t;
				}

				// 3. ��������� ����� ���������� ���������
				count++;
			}
			catch (bad_alloc e)
			{
				// ���� ������ �� ��������, �� ���������� ������
				cout << e.what() << endl;
			}
		}


		// ������� �������� � �������� ������� ������
		void Insert(T _data, int index)
		{
			// 1. ��������, ��������� �� �������
			if (!CorrectIndex(index))
				return;

			// 2. ��������, ������� �� � ����� ������ (�� ��������� end)
			if (index == count)
			{
				// �������� ������ �� ��������� end
				AddEnd(_data);
				return;
			}

			// 3. ��������, ������� �� � ������ ������ (����� begin)
			if (index == 0)
			{
				AddBegin(_data);
				return;
			}

			try
			{
				// 4. �������� ������� ����� �������� �������
				Element<T>* itemPrev = Move(index - 1);

				// 5. �������� ������� � ������� �������
				Element<T>* item = Move(index);

				// 6. ������� ����� ������� � �������� ��� � ������
				Element<T>* t = new Element<T>;
				t->data = _data;
				t->next = item;
				t->prev = itemPrev;
				itemPrev->next = t;
				item->prev = t;

				// 7. ��������� ���������� ���������
				count++;
			}
			catch (bad_alloc e)
			{
				// ���� ������ �� ��������, �� ������� ��������� ���������
				cout << e.what() << endl;
			}
		}


		// ������� ������� � �������� �������,
		// ������� ���������� � 0
		void Del(int index)
		{
			// 1. ��������, ���� �� �������� � ������
			if (count == 0) return;

			// 2. �����, ���� ������� ������� �����������
			if (!CorrectIndex(index))
				return;

			// 3. ������� � ���������� ��������
			Element<T>* item = Move(index);

			// 4. �������� ���������� �������
			Element<T>* itemPrev = item->prev;

			// 5. �������� ��������� �������
			Element<T>* itemNext = item->next;

			// 6. ��������, ��������� �� �� ������ ������� ������
			if ((count > 1) && (itemPrev != nullptr))
				itemPrev->next = itemNext; // ������ ������� item

			// 7. ��������, ��������� �� �� ��������� ������� ������
			if ((itemNext != nullptr) && (count > 1))
				itemNext->prev = itemPrev;

			// 8. ���� ��������� ������ �������
			if (index == 0)
				begin = itemNext;

			// 9. ���� ��������� ��������� �������
			if (index == count - 1)
				end = itemPrev;

			// 10. ������� ������� item
			delete item;

			// 11. ��������� ����� ���������� ���������
			count--;
		}


		// ������� ������
		void Clear()
		{
			// ����� count ��� ������� ������ ������� ������
			int n = count; // ������� ����� �� count - �����!
			for (int i = 0; i < n; i++)
				Del(0);
		}


		// �������������� ������
		void Reverse()
		{
			List<T> L;
			Element<T>* t = begin;

			// ���� ������������ ������,
			// ������� ����������� � ������ ������
			while (t != nullptr)
			{
				L.AddBegin(t->data);
				t = t->next;
			}
			*this = L;
		}


		// �������� ���������� ��������� ������
		int Size()
		{
			return count;
		}


		// ����� ������
		void PrintDiary(string msg)
		{
			cout << msg << endl;
			cout << "______________________________________________________________________________________________\n";
			cout << "|     ����������     |      �����������      |    �����������    |   ��������   |    ����    |\n";
			cout << "|____________________|_______________________|___________________|______________|____________|\n";
			Element<T>* t = begin;
			for (int i = 0; i < count; i++)	
			{
				t->data.print();
				t = t->next;
				cout << "|____________________|_______________________|___________________|______________|____________|\n";

			}
		}

		void PrintRoles(string msg)
		{
			cout << msg << endl;
			cout << "______________________________________________________\n";
			cout << "|      �����      |     ������     |      C�����     |\n";
			cout << "|_________________|________________|_________________|\n";
			Element<T>* t = begin;
			for (int i = 0; i < count; i++)
			{
				t->data.Print();
				t = t->next;
			}
			cout << "|_________________|_________________|_________________|\n";

		}

		
		void Sort()
		{		   
			Element <T>* t1;
			T temp;
				
			for (int i = 1; i < count; ++i)
			{
				for (int j = i; j > 0 &&  Move(j - 1)->data.GetPressure() > Move(j)->data.GetPressure(); --j)
				{
					swap(Move(j - 1)->data, Move(j)->data);
				}
			}			
		}
		

		void Search()
		{
			Element<T>* t = begin;
			string strToFind,str;
			
			int index = 0;
			cout << "������� ��������� ��� ������ ���������� � ������������ �����: ";
			getline(cin, strToFind); cout << endl;
			
			for (int i = 0; i < count; i++)
			{
				str = t->data.GetNapravlenie();
				if (str == strToFind)
				{
					cout << "���� ���������� � ������� " + to_string(i + 1) << endl;
				}	

				t = t->next;
			}

			/*int index = 0;
			while ((index = str.find(strToFind, index))  {
				cout << index << endl;
				index += strToFind.length();
			}*/
		}

		// ���������� ����������
		// �������� + - ������������ �������
		List<T>& operator+(const List<T>& obj)
		{
			// 1. �������� ������ � ������ obj
			Element<T>* t = obj.begin;

			// 2. �������� � ���������� ������ �������� t
			while (t != nullptr)
			{
				AddEnd(t->data);
				t = t->next;
			}

			// 3. ������� ������������ ������
			return *this;
		}



		// �������� ��������� ������� �� ���������
		bool operator==(const List& obj)
		{
			// 1. ������� �������� ������� �������
			if (count != obj.count)
				return false;

			// 2. ���� ������� ���������, �� �������� �����������
			Element<T>* t1 = begin;
			Element<T>* t2 = obj.begin;

			while (t1 != nullptr)
			{
				// ��� ������ ������� ���� �� ���� ������������, �� ����� � ����� false
				if (t1->data != t2->data)
					return false;

				t1 = t1->next;
				t2 = t2->next;
			}

			return true;
		}


		// �������� ��������� ������� �� �����������
		bool operator!=(const List& obj)
		{
			// ������������ �������� ��������� ==
			return !(*this == obj);
		}


		// �������� >=
		bool operator>=(const List& obj)
		{
			// 1. ��������� �� ���������� ���������
			if (count > obj.count)
				return true;

			// 2. ��������� �� ����������
			if (*this == obj)
				return true;

			return false;
		}


		// �������� <=
		bool operator<=(const List& obj)
		{
			// 1. ��������� �� ���������� ��������� � ������
			if (count < obj.count)
				return true;

			// 2. ��������� �� ����������
			if (*this == obj)
				return true;

			return false;
		}


		// �������� >
		bool operator>(const List& obj)
		{
			if (count > obj.count)
				return true;
			return false;
		}


		// �������� <
		bool operator<(const List& obj)
		{
			if (count < obj.count)
				return true;
			return false;
		}

		int input_int(const string ch)
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

		
	};




