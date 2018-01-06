
#include "stdafx.h"
#include "Cuckoo.h"



Cuckoo::Cuckoo(int _n_elems)
{
	P = 2147483629;

	n_elems = _n_elems;

	hashtable = new int*[2];
    for (int i = 0; i < 2; i++) 
        hashtable[i] = new int[n_elems];

	for (int j = 0; j < n_elems; j++)        
		for (int i = 0; i < 2; i++)
            hashtable[i][j] = -1;

	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distA(1, P - 1);
	uniform_int_distribution<> distB(0, P - 1);

	a1 = distA(gen);
	b1 = distB(gen);
	a2 = distA(gen);
	b2 = distB(gen);
}

Cuckoo::~Cuckoo()
{
	delete(hashtable);
}

// Хэш-функция
int Cuckoo::hash(int function, int _key)
{
    switch (function)    
	{
		case 1: return H_ab(_key, a1, b1, n_elems);        
		case 2: return H_ab(_key, a2, b2, n_elems);
    }
} 

void Cuckoo::hash_insert(int _key)
{
	int cnt = 0;
	int res = place(_key, 0, cnt, n_elems);
	if (res == _key)
		rehash(_key);
}

int Cuckoo::place(int _key, int tableID, int cnt, int n)
{
    if (cnt==n)
        return _key;
										
    for (int i = 0; i < 2; i++)
    {
        pos[i] = hash(i+1, _key);
        if (hashtable[i][pos[i]] == _key)           
			return -1;
    }
					
    if (hashtable[tableID][pos[tableID]]!=-1)
    {
        int dis = hashtable[tableID][pos[tableID]];
        hashtable[tableID][pos[tableID]] = _key;
        place(dis, (tableID+1)%2, cnt+1, n);
		return -1;
    }
    else
	{
       hashtable[tableID][pos[tableID]] = _key;
	   return -1;
	}
	
}

void Cuckoo::rehash(int _key)
{
	srand(time(NULL));

	a1 = 1 + (rand() + rand()) % (P - 1);
	b1 = (rand() + rand()) % P;

	a2 = 1 + (rand() + rand()) % (P - 1);
	b2 = (rand() + rand()) % P;

	int size = n_elems * 2;
	int* a = new int[size];
	int index = 0;		
	for(int i = 0; i < 2; i++)        
		for(int j = 0; j < n_elems; j++, index++)        
			a[index] = hashtable[i][j];
	index++;
	a[index] = _key;
		
	for(int i = 0; i < size; i++)
		if(a[i] > -1)		
			hash_insert(a[i]);
}

int Cuckoo::hash_search(int _key)
{		
    for (int i = 0; i < 2; i++)
    {
        pos[i] = hash(i + 1, _key);
        if (hashtable[i][pos[i]] == _key)
           return pos[i];
    }
	return -1;
}

void Cuckoo::hash_delete (int _key)
{
	for (int i = 0; i < 2; i++)
    {
        pos[i] = hash(i + 1, _key);
        if (hashtable[i][pos[i]] == _key)		
			hashtable[i][pos[i]] == -1;
    }
}