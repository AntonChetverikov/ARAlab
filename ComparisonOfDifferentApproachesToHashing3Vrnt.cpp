// ComparisonOfDifferentApproachesToHashing3Vrnt.cpp : Defines the entry point for the console application.
//

// Лабораторная работа № 2
// По курсу Анализ и разработка алгоритмов
// Тема: Сравнение различных подходов к хешированию
//		Метод открытой адресации
//		Метод кукушки
//		std::map, std::hash_map
// Данные: Случайные натуральные числа
// Вариант 3
// 

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <conio.h>
#include <random>
#include <map>
#include <hash_map>
#include "OpenAddressing.h"
#include "Cuckoo.h"

using namespace std;

int P = 2147483629;																// Наибольшее простое число, меньшее чем 2 147 483 647 (= max int)

// Универсальная хэш-функция
unsigned __int64 H_ab(__int32 _x, unsigned __int64 _a, unsigned __int64 _b, int _n_elem)			
{	
	return ( (( _a * _x + _b ) % P) % _n_elem );	
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n_elem;																	// Число элементов
	cout << "Enter the number of elements:" << endl;
	cin >> n_elem;

	unsigned __int32 *elems;
	elems = new unsigned __int32[n_elem];										// Массив входных данных - случайные натуральные числа

	unsigned __int64 *h;
	h = new unsigned __int64[n_elem];											// Массив значений универсальной хэш-функции

	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distA(1, P - 1);
	uniform_int_distribution<> distB(0, P - 1);

	unsigned __int64 a = distA(gen);											// Число a для хэш-функции
	unsigned __int64 b = distB(gen);											// Число b для хэш-функции


	for (int i = 0; i < n_elem; i++)											// Генерация входных данных 
	{
		elems[i] = 1 + (rand() + rand()) % P;									// Генерация входных данных
		h[i] = H_ab(elems[i], a, b, n_elem);									// Подсчёт значений хэш-функций
	}

	cout << " " << endl;

	#define NUM_ITER 10															// Число повторений для усреднения
	int NUM_SEARCH_DEL = n_elem/10;									


#pragma region Std
		
	// std::map
	std::chrono::time_point<std::chrono::high_resolution_clock> map_start, map_check1, map_check2, map_check3, map_check4, map_end;

	double map_time_insert = 0;		
	double map_time_search = 0;		
	double map_time_delete = 0;
		
	cout << "std::map results:" << endl;

	for (int j=0; j < NUM_ITER; j++)
	{
		map <int,int> testMap;

		// Вставка в std::map, нужно подсчитать время вставки
		map_start = std::chrono::high_resolution_clock::now();				
		for (int i = 0; i < n_elem; i++)
			testMap.insert (pair<int, int>(elems[i], h[i]));
		map_check1 = std::chrono::high_resolution_clock::now();

		int *num1;
		num1 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			num1[i] = rand() % n_elem;
		// Поиск в std::map, нужно подсчитать время поиска
		map_check2 = std::chrono::high_resolution_clock::now();
				
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			testMap.find(elems[num1[i]]);
		map_check3 = std::chrono::high_resolution_clock::now();
				
		int *num2;
		num2 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			num2[i] = rand() % n_elem;
		// Удаление из std::map, нужно подсчитать время удаления
		map_check4 = std::chrono::high_resolution_clock::now();				
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			testMap.erase(elems[num2[i]]);
		map_end = std::chrono::high_resolution_clock::now();

		map_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds> (map_check1 - map_start).count();
		map_time_search += std::chrono::duration_cast<std::chrono::nanoseconds> (map_check3 - map_check2).count();
		map_time_delete += std::chrono::duration_cast<std::chrono::nanoseconds> (map_end - map_check4).count();	
	}

	map_time_insert /= NUM_ITER;
	map_time_search /= NUM_ITER;
	map_time_delete /= NUM_ITER;
		
	cout << map_time_insert << endl;
	cout << map_time_search << endl;
	cout << map_time_delete << endl;

	// std::hash_map		
	std::chrono::time_point<std::chrono::high_resolution_clock> hash_map_start, hash_map_check1, hash_map_check2, hash_map_check3, hash_map_check4, hash_map_end;	
		
	double hash_map_time_insert = 0;		
	double hash_map_time_search = 0;		
	double hash_map_time_delete = 0;	
		
	cout << "std::hash_map results:" << endl;

		
	for (int j=0; j < NUM_ITER; j++)
	{

		hash_map <int,int> testHashMap;

		// Вставка в std::hash_map, нужно подсчитать время вставки
		hash_map_start = std::chrono::high_resolution_clock::now();				
		for (int i = 0; i < n_elem; i++)
			testHashMap.insert (pair<int, int>(elems[i], h[i]));
		hash_map_check1 = std::chrono::high_resolution_clock::now();
				
		int *num1;
		num1 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			num1[i] = rand() % n_elem;
		// Поиск в std::hash_map, нужно подсчитать время поиска
		hash_map_check2 = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < NUM_SEARCH_DEL; i++)	
			testHashMap.find(elems[num1[i]]);	
		hash_map_check3 = std::chrono::high_resolution_clock::now();
			
		int *num2;
		num2 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			num2[i] = rand() % n_elem;
		// Удаление из std::hash_map, нужно подсчитать время удаления
		hash_map_check4 = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			testHashMap.erase(elems[num2[i]]);
		hash_map_end = std::chrono::high_resolution_clock::now();

		hash_map_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds> (hash_map_check1 - hash_map_start).count();
		hash_map_time_search += std::chrono::duration_cast<std::chrono::nanoseconds> (hash_map_check3 - hash_map_check2).count();
		hash_map_time_delete += std::chrono::duration_cast<std::chrono::nanoseconds> (hash_map_end - hash_map_check4).count();		
	}

	hash_map_time_insert /= NUM_ITER;
	hash_map_time_search /= NUM_ITER;
	hash_map_time_delete /= NUM_ITER;
		
	cout << hash_map_time_insert << endl;
	cout << hash_map_time_search << endl;
	cout << hash_map_time_delete << endl;

#pragma endregion Std

#pragma region OpenAddressing

	// Open addressing m=n
	std::chrono::time_point<std::chrono::high_resolution_clock> oa2_start, oa2_check1, oa2_check2, oa2_check3, oa2_check4, oa2_end;

	double oa2_time_insert = 0;		
	double oa2_time_search = 0;		
	double oa2_time_delete = 0;
		
	cout << "open addressing m=n results:" << endl;

	for (int j=0; j < NUM_ITER; j++)
	{			
		OpAdd testOpAdd2(n_elem);

		// Вставка в OpenAddressing m=n, нужно подсчитать время вставки 
		oa2_start = std::chrono::high_resolution_clock::now();				
		for (int i = 0; i < n_elem; i++)
			testOpAdd2.hash_insert(elems[i]);	
		oa2_check1 = std::chrono::high_resolution_clock::now();

		int *num1;
		num1 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			num1[i] = rand() % n_elem;
		// Поиск в OpenAddressing m=n, нужно подсчитать время поиска
		oa2_check2 = std::chrono::high_resolution_clock::now();				
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			testOpAdd2.hash_search(elems[num1[i]]);
		oa2_check3 = std::chrono::high_resolution_clock::now();

		int *num2;
		num2 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			num2[i] = rand() % n_elem;
		// Удаление из OpenAddressing m=n, нужно подсчитать время удаления
		oa2_check4 = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			testOpAdd2.hash_delete(elems[num2[i]]);
		oa2_end = std::chrono::high_resolution_clock::now();

		oa2_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds> (oa2_check1 - oa2_start).count();
		oa2_time_search += std::chrono::duration_cast<std::chrono::nanoseconds> (oa2_check3 - oa2_check2).count();
		oa2_time_delete += std::chrono::duration_cast<std::chrono::nanoseconds> (oa2_end - oa2_check4).count();
	}
			
	oa2_time_insert /= NUM_ITER;
	oa2_time_search /= NUM_ITER;
	oa2_time_delete /= NUM_ITER;
		
	cout << oa2_time_insert << endl;
	cout << oa2_time_search << endl;
	cout << oa2_time_delete << endl;

	// Open addressing m=2n
	std::chrono::time_point<std::chrono::high_resolution_clock> oa3_start, oa3_check1, oa3_check2, oa3_check3, oa3_check4, oa3_end;

	double oa3_time_insert = 0;		
	double oa3_time_search = 0;		
	double oa3_time_delete = 0;
		
	cout << "open addressing m=2n results:" << endl;

	for (int j=0; j < NUM_ITER; j++)
	{			
		OpAdd testOpAdd3(n_elem * 2);

		// Вставка в OpenAddressing m=2n, нужно подсчитать время вставки 
		oa3_start = std::chrono::high_resolution_clock::now();				
		for (int i = 0; i < n_elem; i++)
			testOpAdd3.hash_insert(elems[i]);	
		oa3_check1 = std::chrono::high_resolution_clock::now();
				
		int *num1;
		num1 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)			
			num1[i] = rand() % n_elem;
		// Поиск в OpenAddressing m=2n, нужно подсчитать время поиска
		oa3_check2 = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			testOpAdd3.hash_search(elems[num1[i]]);
		oa3_check3 = std::chrono::high_resolution_clock::now();

		int *num2;
		num2 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			num2[i] = rand() % n_elem;
		// Удаление из OpenAddressing m=2n, нужно подсчитать время удаления
		oa3_check4 = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < NUM_SEARCH_DEL; i++)
			testOpAdd3.hash_delete(elems[num2[i]]);
		oa3_end = std::chrono::high_resolution_clock::now();

		oa3_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds> (oa3_check1 - oa3_start).count();
		oa3_time_search += std::chrono::duration_cast<std::chrono::nanoseconds> (oa3_check3 - oa3_check2).count();
		oa3_time_delete += std::chrono::duration_cast<std::chrono::nanoseconds> (oa3_end - oa3_check4).count();
	}
			
	oa3_time_insert /= NUM_ITER;
	oa3_time_search /= NUM_ITER;
	oa3_time_delete /= NUM_ITER;
		
	cout << oa3_time_insert << endl;
	cout << oa3_time_search << endl;
	cout << oa3_time_delete << endl;

#pragma endregion OpenAddressing

#pragma region Cuckoo

	// Cuckoo	
	std::chrono::time_point<std::chrono::high_resolution_clock> cu_start, cu_check1, cu_check2, cu_check3, cu_check4, cu_end;

	double cu_time_insert = 0;		
	double cu_time_search = 0;		
	double cu_time_delete = 0;
		
	cout << "cuckoo results:" << endl;

	for (int j=0; j < NUM_ITER; j++)
	{			
		Cuckoo testCuckoo(n_elem);

		// Вставка в Cuckoo, нужно подсчитать время вставки 
		cu_start = std::chrono::high_resolution_clock::now();				
		for (int i = 0; i < n_elem; i++)							// Заполнение OppAdd	
			testCuckoo.hash_insert(elems[i]);
		cu_check1 = std::chrono::high_resolution_clock::now();

		int *num1;
		num1 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)			
			num1[i] = rand() % n_elem;
		// Поиск в Cuckoo, нужно подсчитать время поиска
		cu_check2 = std::chrono::high_resolution_clock::now();
		for(int i = 0; i < NUM_SEARCH_DEL; i++)		
			testCuckoo.hash_search(elems[num1[i]]);
		cu_check3 = std::chrono::high_resolution_clock::now();

		int *num2;
		num2 = new int[NUM_SEARCH_DEL];
		for(int i = 0; i < NUM_SEARCH_DEL; i++)			
			num2[i] = rand() % n_elem;
		// Удаление из Cuckoo, нужно подсчитать время удаления
		cu_check4 = std::chrono::high_resolution_clock::now();				
		for(int i = 0; i < NUM_SEARCH_DEL; i++)		
			testCuckoo.hash_delete(elems[num2[i]]);
		cu_end = std::chrono::high_resolution_clock::now();

		cu_time_insert += std::chrono::duration_cast<std::chrono::nanoseconds> (cu_check1 - cu_start).count();
		cu_time_search += std::chrono::duration_cast<std::chrono::nanoseconds> (cu_check3 - cu_check2).count();
		cu_time_delete += std::chrono::duration_cast<std::chrono::nanoseconds> (cu_end - cu_check4).count();
	}
			
	cu_time_insert /= NUM_ITER;
	cu_time_search /= NUM_ITER;
	cu_time_delete /= NUM_ITER;
		
	cout << cu_time_insert << endl;
	cout << cu_time_search << endl;
	cout << cu_time_delete << endl;

#pragma endregion Cuckoo

	_getch ();
}

