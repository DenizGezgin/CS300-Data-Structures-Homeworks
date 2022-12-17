//Created by: Deniz Can Gezgin on 13.11.2021
//This is generic class to store items of given type in a hash table 
//Size of table and a sentinal ITEM_NOT_FOUND must be given in constraction
//Classes must provide their own hash function they can be add to the end


#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <String>
#include <vector>

//using namespace std;

template <class HashedObj>
class HashTable 
{
public:
	explicit HashTable(const HashedObj& notFound, int size = 8209); //constractor

	const HashedObj& find(const HashedObj& x) const; //Returns the given object from hash table
	void makeEmpty(); //makes list empty
	void insert(const HashedObj& x); //puts new item to list
	void remove(const HashedObj& x); //removes given item from list
	int getSize() const; //returns number of elements stored in list

private:
	enum EntryType { ACTIVE, EMPTY, DELETED };

	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj &e = HashedObj(), EntryType t = EMPTY)
			:element(e), info(t) {}
	};

	int size; //4095
	int currentSize;
	std::vector<HashEntry> table;
	const HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPosition) const;
	int findPos(const HashedObj& x) const;


};

//Hash function for generic string class
int hash(std::string key, int size) 
{
	char currentChar;
	int hashVal = 0;
	for (int i = 0; i < key.size(); i++)
	{
		currentChar = key[i];
		hashVal += (unsigned int)currentChar;
	}
	return hashVal%size;
}

//hash function for codded string appanded to end 
//hashes on string part by total ascii value count
int hash(const CodedString& myString, int tableSize)
{
	std::string key = myString.getString();
	unsigned char currentChar;
	int hashVal = 0;
	for (int i = 0; i < key.size(); i++)
	{
		currentChar = key[i];
		hashVal += (unsigned int)currentChar;
	}
	return (hashVal % tableSize);
}

#include "HashTable.cpp"

#endif // !_HASH_TABLE
