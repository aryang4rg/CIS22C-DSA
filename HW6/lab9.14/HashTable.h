// Specification file for the Hash class
// Written By: A. Student
// Changed by:

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

template <class ItemType>
class HashTable
{
private:
	HashNode<ItemType> *hashAry;
	int hashSize;
	int count;

public:
	HashTable()
	{
		count = 0;
		hashSize = 53;
		hashAry = new HashNode<ItemType>[hashSize];
	}
	HashTable(int n)
	{
		count = 0;
		hashSize = n;
		hashAry = new HashNode<ItemType>[hashSize];
	}
	~HashTable() { delete[] hashAry; }

	int getCount() const { return count; }
	int getSize() const { return hashSize; }
	double getLoadFactor() const { return 100.0 * count / hashSize; }
	bool isEmpty() const { return count == 0; }
	bool isFull() const { return count == hashSize; }

	bool insert(const ItemType &itemIn, int h(const ItemType &key, int size));
	bool remove(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));
	int search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));
};

/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template <class ItemType>
bool HashTable<ItemType>::insert(const ItemType &itemIn, int h(const ItemType &key, int size))
{
	if (count == hashSize)
		return false;

	int hashedKey = h(itemIn, hashSize);
	count++;
	int j = 0;
	for (int i = hashedKey; true; i = (i + 1) % hashSize)
	{
		if (hashAry[i].getOccupied() < 2)
		{
			hashAry[i].setItem(itemIn);
			hashAry[i].setOccupied(2);
			hashAry[i].setNoCollisions(j);
			break;
		}
		j++;
	}

	return true;
}

/*~*~*~*
   Removes the item with the matching key from the hash table
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record
*~**/
template <class ItemType>
bool HashTable<ItemType>::remove(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size))
{
	int hashedKey = h(key, hashSize);
	bool lookedThroughFirstElm = false;
	for (int i = hashedKey; hashAry[i].getOccupied() > 0; i = (i + 1) % hashSize)
	{
		if (lookedThroughFirstElm && i == hashedKey)
		{
			break;
		}
		if (hashAry[i].getItem() == key)
		{
			itemOut = hashAry[i].getItem();
			hashAry[i].setNoCollisions(0);
			hashAry[i].setOccupied(1);
			hashAry[i].setItem(ItemType());
			count--;
			return true;
		}
		lookedThroughFirstElm = true;
	}

	return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template <class ItemType>
int HashTable<ItemType>::search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size))
{
	int hashedKey = h(key, hashSize);
	bool lookedThroughFirstElm = false;

	for (int i = hashedKey; hashAry[i].getOccupied() > 0; i = (i + 1) % hashSize)
	{
		if (lookedThroughFirstElm && i == hashedKey)
		{
			break;
		}

		if (hashAry[i].getItem() == key)
		{
			itemOut = hashAry[i].getItem();
			return hashAry[i].getNoCollisions();
		}

		lookedThroughFirstElm = true;
	}

	return -1;
}

#endif // HASHTABLE_H_
