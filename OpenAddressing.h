
#include "stdafx.h"
#include <chrono>
#include <random>

using namespace std;

class OpAdd
{
public:	

	OpAdd(int _table_size);

	~OpAdd();

	// Вставка
	void hash_insert (int _key);		

	// Поиск
	int hash_search (int _key);

	// Удаление
	void hash_delete (int _key);
	

private:

	int table_size;			// Ёмкость таблицы

	int *Table;				// Хэш-таблица

	unsigned __int64 a;		// Число a для хэш-функции
	unsigned __int64 b;		// Число b для хэш-функции


	int P;					// Наибольшее простое число, меньшее чем 2 147 483 647 (= max int)

	// Универсальная хэш-функция
	int H_ab(__int32 _x, unsigned __int64 _a, unsigned __int64 _b, int _n_elem)		
	{	
		return ( (( _a * _x + _b ) % P) % _n_elem );
	}
	
	// Линейное хэширование
	unsigned __int64 hashLin(int _H_ab, int _i);		
	
	// Добавление элемента в хэш-таблицу
	int add_elem(int _key);				
	
	// Увеличение ёмкости таблицы
	void remake_table(int _key);
};