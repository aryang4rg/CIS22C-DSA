#include <iostream>

#include "HashTable.h"
#include "Student.h"

using namespace std;

int key_to_index(const Student &key, int size);

int main()
{

    Student list[] = {{"tom", 2.5}, {"bob", 3.2}, {"boc", 3.2}, {"mia", 3.9}, {"jack", 4.0},
        {"john", 3.9}, {"zoe", 3.5}, {"ann", 3.1}, {"obb", 2.2}, {"bbo", 3.3}, {"ccm", 1.5}, {"",0}};

	HashTable<Student> hash = HashTable<Student>();

    // build hash from array
    for (int i = 0; list[i].getName() != ""; i++)
    {
       hash.insert(list[i], key_to_index);
    }

    // test search
    Student target[] = {{"zoe", 0}, {"mia", 0}, {"linda", 0}, {"bob", 0}, {"boc", 0}, {"obb", 0}, {"bbo", 0}, {"ccm", 0}, {"", 0}};

    for (int i = 0; target[i].getName() != ""; i++)
    {
        Student item;  // will store a copy of the item found in the hash table
        int nc;        // number of collisions if found, -1 if not found

        nc = hash.search(item, target[i], key_to_index);
        if (nc != -1)
            cout << item.getName() << " " << item.getGpa() << " (" << nc << " collisions!)" << endl;
        else
            cout << target[i].getName() << " not found!" << endl;
    }

    cout << "Load Factor: " << hash.getLoadFactor() << endl;

    // Add a new item to the hash table: reject duplicates
    cout << "Test hash search/insert" << endl;

    Student found; // will store a copy of the item found in the hash table
    string name;   // name to insert
    double gpa;    // gpa to insert
    cout << "Enter name or Q to quit: ";
    cin >> name;
    while ( name != "Q" )
    {
		Student key = Student();
		key.setName(name);
        if (hash.search(found, key, key_to_index) != -1)
            cout << endl << "Duplicate key: " << found.getName() << " - rejected! " << endl;
        else
        {
            cout << "Enter gpa ";
            cin >> gpa;
			Student toInsert = Student();
			toInsert.setGpa(gpa);
			toInsert.setName(name);
			hash.insert(toInsert, key_to_index);
        }
        cout << "Enter name: ";
        cin >> name;
    }
    cout << "Load Factor: " << hash.getLoadFactor() << endl;

    // test delete
    cout << "Test delete" << endl;
    cout << "Enter name or Q to quit: ";
    cin >> name;
    while ( name != "Q" )
    {
        Student itemOut, found, key(name, 0);
        if (hash.remove(itemOut, key, key_to_index))
            cout << endl << itemOut.getName() << " " << itemOut.getGpa() << " - deleted!" << endl;

        cout << "Load Factor: " << hash.getLoadFactor() << endl;

        cout << "Enter name or Q to quit: ";
        cin >> name;
    }

    // test search
     cout << "Test search" << endl;
     cout << "Enter name or Q to quit: ";
     cin >> name;
     while ( name != "Q" )
     {
         Student found, key(name,0);

         if ((hash.search(found, key, key_to_index)) != -1)
             cout << endl << "Found: " << found.getName() << " " << found.getGpa() << endl;
         else
             cout << endl << name << " not found!" << endl;
         cout << "Enter name or Q to quit: ";
         cin >> name;
     }

    return 0;
}

/*~*~*~*
 Hash function: takes the key and returns the index in the hash table
 *~**/
int key_to_index(const Student &key, int size)
{
    string k = key.getName();
    int sum = 0;
    for (int i = 0; k[i]; i++)
        sum += k[i];
    return sum % size;
};
