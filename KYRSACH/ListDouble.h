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

	// Структура, описывающая один елемент (узел)
	template <class T>
	struct Element
	{
		T data; // данные
		Element<T>* next; // адрес следующего элемента в списке
		Element<T>* prev; // адрес предыдущего элемента в списке
	};

	// Клас, реализующий двусвязный список
	template <class T>
	class List
	{
	private:
		Element<T>* begin; // указатель на первый элемент списка
		Element<T>* end; // указатель на последний элемент списка
		int count; // количество элементов в списке

		// Метод, возвращающий элемент в заданной позиции,
		// считается что позиция корректна.
		Element<T>* Move(int index)
		{
			// 1. Установить указатель на начало списка
			Element<T>* t = begin;

			// 2. Перемотать в позицию index
			for (int i = 0; i < index; i++)
				t = t->next;

			// 3. Вернуть указатель
			return t;
		}

		// Метод, копирующий список
		void Copy(const List<T>& obj)
		{
			// 1. Очистить список (освободить память)
			Clear();

			// 2. Цикл копирования this <= obj
			Element<T>* t = obj.begin;

			while (t != nullptr)
			{
				PushBack(t->data);
				t = t->next;
			}
		}


		// Метод, проверяющий корректность позиии (индекса) в списке
		bool CorrectIndex(int index)
		{
			return (index >= 0) && (index < count);

		}	

	public:
		

		// Конструктор
		//template <class T>
		List() 
		{
			
			// Создать пустой список
			begin = end = nullptr;
			count = 0;
		}

		// Конструктор копирования
		List(const List& obj)
		{
			// Сделать копию из списка
			Copy(obj);
		}

		// Оператор копирования
		List<T>& operator=(const List& obj)
		{
			Copy(obj);
			return *this;
		}


		// Деструктор
		~List()
		{
			Clear(); // очистить список
		}


		// ---------- Методы доступа к отдельным элементам списка --------
		// Получить элемент списка по индексу
		T GetElement(int index)
		{
			// Проверка, корректен ли индекс,
			// если индекс не корректен, сгенерировать исключение
			if (!CorrectIndex(index))
				throw out_of_range("Incorrect index.");

			// Если индекс корректен, то вернуть элемент
			Element<T>* t = Move(index);
			return t->data;
		}


		// Изменить значение элемента в заданной позиции
		void SetElement(T _data, int index)
		{
			// Проверка, корректна ли позиция
			if (!CorrectIndex(index))
				return;

			// Получить элемент по позиции и изменить его значение
			Element<T>* t = Move(index);
			t->data = _data;
		}


		// ---------- Методы изменения размера списка ------------
		// Добавить элемент в конец списка
		void PushBack(T _data)
		{
			try
			{
				// 1. Создать новый элемент с данными _data
				Element<T>* t = new Element<T>;
				t->next = nullptr; // следующего элемента нет
				t->prev = end; // установить предыдущий элемент
				t->data = _data; // записать данные

				// 2. Заполнить поле next пока что последнего элемента
				if (end != nullptr)
					end->next = t;

				// 3. Проверка, есть ли в списке элементы
				if (count == 0)
				{
					// если элементов нет,
					// то это одновременно и начало и конец списка
					begin = end = t;
				}
				else
				{
					// если элементы в списке есть, то это конец списка
					end = t;
				}

				// 4. Увеличить общее количество элементов
				count++;
			}
			catch (bad_alloc e)
			{
				// Если память не выделена, то вывести системное сообщение
				cout << e.what() << endl;
			}

		}


		// Добавить элемент в начало списка
		void PushFront(T _data)
		{
			try
			{
				// 1. Создать новый элемент (новую ячейку памяти)
				// и заполнить его данными
				Element<T>* t = new Element<T>;
				t->data = _data; // данные
				t->prev = nullptr; // предыдущего элемента нет

				// следующий элемент указывает на предыдущий первый
				t->next = begin;

				// 2. Есть ли элементы в списке?
				if (count > 0)
				{
					// если есть, то перенаправить предыдущее начало списка
					begin->prev = t;
					begin = t;
				}
				else
				{
					// если элементов нет, то начало и конец есть тем самым элементом
					begin = end = t;
				}

				// 3. Увеличить общее количество элементов
				count++;
			}
			catch (bad_alloc e)
			{
				// если память не выделена, то обработать ошибку
				cout << e.what() << endl;
			}
		}


		// Вставка элемента в заданную позицию списка
		void Insert(T _data, int index)
		{
			// 1. Проверка, корректна ли позиция
			if (!CorrectIndex(index))
				return;

			// 2. Проверка, вставка ли в конец списка (по указателю end)
			if (index == count)
			{
				// Добавить данные по указателю end
				AddEnd(_data);
				return;
			}

			// 3. Проверка, вставка ли в начало списка (перед begin)
			if (index == 0)
			{
				AddBegin(_data);
				return;
			}

			try
			{
				// 4. Получить элемент перед позицией вставки
				Element<T>* itemPrev = Move(index - 1);

				// 5. Получить элемент в позиции вставки
				Element<T>* item = Move(index);

				// 6. Создать новый элемент и вставить его в список
				Element<T>* t = new Element<T>;
				t->data = _data;
				t->next = item;
				t->prev = itemPrev;
				itemPrev->next = t;
				item->prev = t;

				// 7. Увеличить количество элементов
				count++;
			}
			catch (bad_alloc e)
			{
				// Если память не выделена, то вывести системное сообщение
				cout << e.what() << endl;
			}
		}


		// Удалить элемент в заданной позиции,
		// позиция нумеруется с 0
		void Del(int index)
		{
			// 1. Проверка, есть ли элементы в списке
			if (count == 0) return;

			// 2. Игнор, если позиция указана неправильно
			if (!CorrectIndex(index))
				return;

			// 3. Перейти к удаляемому элементу
			Element<T>* item = Move(index);

			// 4. Получить предыдущий элемент
			Element<T>* itemPrev = item->prev;

			// 5. Получить следующий элемент
			Element<T>* itemNext = item->next;

			// 6. Проверка, удаляется ли не первый элемент списка
			if ((count > 1) && (itemPrev != nullptr))
				itemPrev->next = itemNext; // обойти элемент item

			// 7. Проверка, удаляется ли не последний элемент списка
			if ((itemNext != nullptr) && (count > 1))
				itemNext->prev = itemPrev;

			// 8. Если удаляется первый элемент
			if (index == 0)
				begin = itemNext;

			// 9. Если удаляется последний элемент
			if (index == count - 1)
				end = itemPrev;

			// 10. Удалить элемент item
			delete item;

			// 11. Уменьшить общее количество элементов
			count--;
		}


		// Очистка списка
		void Clear()
		{
			// Нужно count раз удалить первый элемент списка
			int n = count; // сделать копию из count - важно!
			for (int i = 0; i < n; i++)
				Del(0);
		}


		// Реверсирование списка
		void Reverse()
		{
			List<T> L;
			Element<T>* t = begin;

			// цикл формирования списка,
			// элемент добавляется в начало списка
			while (t != nullptr)
			{
				L.AddBegin(t->data);
				t = t->next;
			}
			*this = L;
		}


		// Получить количество элементов списка
		int Size()
		{
			return count;
		}


		// Вывод списка
		void PrintDiary(string msg)
		{
			cout << msg << endl;
			cout << "______________________________________________________________________________________________\n";
			cout << "|     Облачность     |      Направление      |    Температура    |   Давление   |    Дата    |\n";
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
			cout << "|      Логин      |     Пароль     |      Cтатус     |\n";
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
			cout << "Введите подстроку для поиска совпадений с направлением ветра: ";
			getline(cin, strToFind); cout << endl;
			
			for (int i = 0; i < count; i++)
			{
				str = t->data.GetNapravlenie();
				if (str == strToFind)
				{
					cout << "Есть совпадение с записью " + to_string(i + 1) << endl;
				}	

				t = t->next;
			}

			/*int index = 0;
			while ((index = str.find(strToFind, index))  {
				cout << index << endl;
				index += strToFind.length();
			}*/
		}

		// Перегрузка операторов
		// Операция + - конкатенация списков
		List<T>& operator+(const List<T>& obj)
		{
			// 1. Получить доступ к списку obj
			Element<T>* t = obj.begin;

			// 2. Добавить к временному списку элементы t
			while (t != nullptr)
			{
				AddEnd(t->data);
				t = t->next;
			}

			// 3. Вернуть объединенный список
			return *this;
		}



		// Операция сравнения списков на равенство
		bool operator==(const List& obj)
		{
			// 1. Сначала сравнить размеры списков
			if (count != obj.count)
				return false;

			// 2. Если размеры одинаковы, то сравнить поэлементно
			Element<T>* t1 = begin;
			Element<T>* t2 = obj.begin;

			while (t1 != nullptr)
			{
				// Как только найдено хотя бы одно несовпадение, то выход с кодом false
				if (t1->data != t2->data)
					return false;

				t1 = t1->next;
				t2 = t2->next;
			}

			return true;
		}


		// Операция сравнения списков на неравенство
		bool operator!=(const List& obj)
		{
			// Использовать оператор сравнения ==
			return !(*this == obj);
		}


		// Операция >=
		bool operator>=(const List& obj)
		{
			// 1. Сравнение по количеству элементов
			if (count > obj.count)
				return true;

			// 2. Сравнение по содержанию
			if (*this == obj)
				return true;

			return false;
		}


		// Операция <=
		bool operator<=(const List& obj)
		{
			// 1. Сравнение по количеству элементов в списке
			if (count < obj.count)
				return true;

			// 2. Сравнение по содержанию
			if (*this == obj)
				return true;

			return false;
		}


		// Операция >
		bool operator>(const List& obj)
		{
			if (count > obj.count)
				return true;
			return false;
		}


		// Операция <
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
					cout << "Вводи нормально" << endl;
				}
				else
					isNotOk = 0;
			}
			return number;
		}

		
	};




