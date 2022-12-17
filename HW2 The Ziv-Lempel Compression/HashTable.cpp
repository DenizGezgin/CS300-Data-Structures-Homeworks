#include "HashTable.h"

//using namespace std;

//constractor
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound, int size)
	:ITEM_NOT_FOUND(notFound), table(size), currentSize(0)
{}

//Privite method to find position of a given item
template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const
{
	int i = 0;
	int p = hash(x, table.size()); //calls the hash function to find index
	while (table[p].info != EMPTY && table[p].element != x) //do linear proping
	{
		p++;
		if (p >= table.size()) //when p exceeds table size make it 0 ie put to start
			p = 0;
	}

	return p;   //p is either an empty cell or an active cell containing x
}

//Check if an item is stroed in a cell returned by findPos
template <class HashedObj>
bool HashTable<HashedObj>::isActive(int pos) const
{
	return table[pos].info == ACTIVE;
}

//logically removes the item by setting the info to deleted
template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x)
{
	int currentPos = findPos(x);
	if (isActive(currentPos))
	{
		table[currentPos].info = DELETED;
	}
}

//getter to return num of elements stored
template<class HashedObj>
int HashTable<HashedObj>::getSize() const
{
	return currentSize;
}

//find given item
template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x) const
{
	int pos = findPos(x); //get a location returned 

	if (isActive(pos)) //if an item is sotored at that location return it
		return table[pos].element;

	return ITEM_NOT_FOUND; //otherwise return item not found
}

//insterted element to table
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x)
{
	//find x or first empty cell to insert
	int currentPos = findPos(x);
	if (isActive(currentPos)) //dont to anything if location is active 
		return;

	table[currentPos] = HashEntry(x, ACTIVE); //add if not active

	//rehash??
}


//makes the whole list logically empty
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{

	for (int i = 0; i < table.size(); i++) //set every elemet to NULL
	{
		if (isActive(i))
			table[i].info = DELETED;
	}
}
