
#include "stdafx.h"
#include <chrono>
#include <random>

using namespace std;

class Cuckoo
{
public:

	Cuckoo(int _n_elems);

	~Cuckoo();

	// Вставка
	void hash_insert(int _key);

	// Поиск
	int hash_search (int _key);

	// Удаление
	void hash_delete (int _key);

private:

	int n_elems;			// Число элементов

	int **hashtable;		// Хэш-таблица
	
	int pos[2];				// Массив хранения для возможного значения ключа
		
	unsigned __int64 a1;	// Число a1 для хэш-функции
	unsigned __int64 b1;	// Число b1 для хэш-функции
	unsigned __int64 a2;	// Число a2 для хэш-функции
	unsigned __int64 b2;	// Число b2 для хэш-функции			

	int P;					// Наибольшее простое число, меньшее чем 2 147 483 647 (= max int)

	// Универсальная хэш-функция
	unsigned __int64 H_ab(__int32 _x, unsigned __int32 _a, unsigned __int32 _b, int _n_elem)			
	{	
		return ( (( _a * _x + _b ) % P) % _n_elem );
	}

	// Хэш-функция
	int hash(int function, int _key);

	// Размещение элемента в таблице
	int place(int _key, int _tableID, int _cnt, int _n);

	// Перехэширование
	void rehash(int _key);
};