
#include "stdafx.h"
#include <chrono>
#include <random>

using namespace std;

class Cuckoo
{
public:

	Cuckoo(int _n_elems);

	~Cuckoo();

	// �������
	void hash_insert(int _key);

	// �����
	int hash_search (int _key);

	// ��������
	void hash_delete (int _key);

private:

	int n_elems;			// ����� ���������

	int **hashtable;		// ���-�������
	
	int pos[2];				// ������ �������� ��� ���������� �������� �����
		
	unsigned __int64 a1;	// ����� a1 ��� ���-�������
	unsigned __int64 b1;	// ����� b1 ��� ���-�������
	unsigned __int64 a2;	// ����� a2 ��� ���-�������
	unsigned __int64 b2;	// ����� b2 ��� ���-�������			

	int P;					// ���������� ������� �����, ������� ��� 2 147 483 647 (= max int)

	// ������������� ���-�������
	unsigned __int64 H_ab(__int32 _x, unsigned __int32 _a, unsigned __int32 _b, int _n_elem)			
	{	
		return ( (( _a * _x + _b ) % P) % _n_elem );
	}

	// ���-�������
	int hash(int function, int _key);

	// ���������� �������� � �������
	int place(int _key, int _tableID, int _cnt, int _n);

	// ���������������
	void rehash(int _key);
};