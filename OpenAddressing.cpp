
#include "stdafx.h"
#include "OpenAddressing.h"



OpAdd::OpAdd(int _table_size)
{
	P = 65521;

	table_size = _table_size;
	Table = new int[table_size];
	for (int i = 0; i < table_size; i++)
		Table[i] = -1;

	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distA(1, P - 1);
	uniform_int_distribution<> distB(0, P - 1);

	a = distA(gen);
	b = distB(gen);
}

OpAdd::~OpAdd()
{		
	delete(Table);
}

unsigned __int64 OpAdd::hashLin(int _H_ab, int _i)
{
	return ((_H_ab + _i) % table_size);
}

int OpAdd::add_elem(int _key)
{		
	for (int i = 0; i < table_size; i++)
	{
		int j = hashLin(H_ab(_key, a, b, table_size),i);
		if (Table[j] < 0)
		{
			Table[j] = _key;
			return j;
		}
	}
	return -1;													// ѕереполнение хэш-таблицы
}

void OpAdd::hash_insert (int _key)
{
	int key = add_elem(_key);
	if (key == -1)												// ѕереполнение хэш-таблицы, увеличиваем еЄ размер
		remake_table(_key);
}

int OpAdd::hash_search (int _key)
{
	for (int i = 0; i < table_size; i++)
	{
		int j = hashLin(H_ab(_key, a, b, table_size), i);			
		if (Table[j] == _key)
			return j;
	}
	return -1;													// Ёлемент не найден
}

void OpAdd::hash_delete (int _key)
{
	for (int i = 0; i < table_size; i++)
	{
		int j = hashLin(H_ab(_key, a, b, table_size), i);
		if (Table[j] == _key)
			Table[j] = -2;										// -2 это значение, указывающее на то, что элемент был удалЄн		
	}
}

void OpAdd::remake_table(int _key)
{
	srand(time(NULL));

	a = 1 + (rand() + rand()) % (P - 1);
	b = (rand() + rand()) % P;
			
	int old_table_size = table_size;
	table_size = 2 * table_size;
	
	int *old_elems;
	old_elems = new int[old_table_size];

	for (int i = 0; i < old_table_size; i++)
	{
		old_elems[i] = -1;
		if (Table[i] > -1)
		{
			old_elems[i] = Table[i];
			Table[i] = -1;
		}
	}
	old_table_size++;
	old_elems[old_table_size] = _key;

	for (int i = 0; i < old_table_size; i++)
	{			
		if (old_elems[i] > -1)
			hash_insert(old_elems[i]);		
	}
}