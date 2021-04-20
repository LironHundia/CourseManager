//
// Created by רוני on 30/12/2020.
//

#ifndef DS_WET2_HASHTABLE_H
#define DS_WET2_HASHTABLE_H

#include "List.h"
#include "library2.h"

template <class T>
class HashTable{
private:
    List<T>** table;
    int table_size;
    int num_of_elements;
    int hash_func(int element_id);
public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable<T>& hash_table);
    HashTable<T>& operator=(const HashTable<T>& hash_table);
    StatusType add(const T& to_add);
    T* find(int key);
    StatusType remove(int key_to_remove);
    void changeSize();
    void print();
    int getTableSize();
};

#include "HashTableImp.h"

#endif //DS_WET2_HASHTABLE_H
