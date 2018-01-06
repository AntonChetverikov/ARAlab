
#include "stdafx.h"
#include <chrono>
#include <random>

using namespace std;

class OpAdd
{
public:	

	OpAdd(int _table_size);

	~OpAdd();

	// �������
	void hash_insert (int _key);		

	// �����
	int hash_search (int _key);

	// ��������
	void hash_delete (int _key);
	

private:

	int table_size;			// ������� �������

	int *Table;				// ���-�������

	unsigned __int64 a;		// ����� a ��� ���-�������
	unsigned __int64 b;		// ����� b ��� ���-�������


	int P;					// ���������� ������� �����, ������� ��� 2 147 483 647 (= max int)

	// ������������� ���-�������
	int H_ab(__int32 _x, unsigned __int64 _a, unsigned __int64 _b, int _n_elem)		
	{	
		return ( (( _a * _x + _b ) % P) % _n_elem );
	}
	
	// �������� �����������
	unsigned __int64 hashLin(int _H_ab, int _i);		
	
	// ���������� �������� � ���-�������
	int add_elem(int _key);				
	
	// ���������� ������� �������
	void remake_table(int _key);
};