#include "List.h"

template <class T>
HashTable<T>::HashTable() : table(new List<T>*[1]), table_size(1), num_of_elements(0) {
    table[0] = nullptr;
}

template <class T>
HashTable<T>::~HashTable(){
    for (int i=0; i<table_size; i++){
        delete table[i];
    }
    delete[] table;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& hash_table) : table(new List<T>*[hash_table.table_size]),
                                                          table_size(hash_table.table_size),
                                                          num_of_elements(hash_table.num_of_elements) {
    for (int i=0; i<table_size; i++){
        if (hash_table.table[i] == nullptr){
            table[i] = nullptr;
        }
        else {
            table[i] = new List<T>(*(hash_table.table[i]));
        }
    }
}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& hash_table){
    if (this == &hash_table){
        return *this;
    }
    for (int i=0; i<table_size; i++){
        delete table[i];
    }
    delete table;
    table = new List<T>*[hash_table.table_size];
    table_size = hash_table.table_size;
    num_of_elements = hash_table.num_of_elements;
    for (int i=0; i<table_size; i++){
        if (hash_table.table[i] == nullptr){
            table[i] = nullptr;
        }
        else {
            table[i] = new List<T>(*(hash_table.table[i]));
        }
    }
    return *this;
}

template <class  T>
int HashTable<T>::hash_func(int element_id){
    return element_id % table_size;
}

template <class T>
StatusType HashTable<T>::add(const T& to_add){ //change param to int key
    if (find(to_add.getKey()) != nullptr){ //to_add already exists
        return FAILURE;
    }
    int index_to_add = hash_func(to_add.getKey());
    if (table[index_to_add] == nullptr){
        table[index_to_add] = new List<T>();
    }
    table[index_to_add]->add(to_add);
    num_of_elements++;
    if (num_of_elements >= table_size){
        changeSize();
    }
    return SUCCESS;
}

template <class T>
T* HashTable<T>::find(int key){
    int index_to_find = hash_func(key);
    if (table[index_to_find] == nullptr){
        return nullptr;
    }
    return table[index_to_find]->find(key);
}

template <class T>
StatusType HashTable<T>::remove(int key_to_remove){
    T* to_remove = find(key_to_remove);
    if (to_remove == nullptr){
        return FAILURE;
    }
    int index_to_remove = hash_func(key_to_remove);
    table[index_to_remove]->remove(key_to_remove);
    num_of_elements--;
    if ((num_of_elements * 4) <= table_size){
        changeSize();
    }
    return SUCCESS;
}

template <class T>
void HashTable<T>::changeSize(){
    int new_size;
    int old_size = table_size;
    if (num_of_elements >= table_size){
        new_size = table_size * 2;
    }
    else if ((num_of_elements * 4) <= table_size){
        new_size = table_size / 2;
    }
    else{
        return;
    }
    List<T>** new_table = new List<T>*[new_size];
    table_size = new_size;
    for (int i=0; i<table_size; i++){
        new_table[i] = nullptr;
    }
    for (int i=0; i<old_size; i++){
        if (table[i] == nullptr){
            continue;
        }
        int current_list_size = table[i]->getListSize();
        if (current_list_size == 0){
            delete table[i];
            continue;
        }
        int* key_array = new int[current_list_size];
        T** element_array = new T*[current_list_size];
        table[i]->listToArray(key_array, element_array);
        for (int j=0; j<current_list_size; j++){
            int index_to_add = hash_func(key_array[j]);
            if (new_table[index_to_add] == nullptr){
                new_table[index_to_add] = new List<T>();
            }
            new_table[index_to_add]->addWithoutAlloc(element_array[j]);
        }
        delete[] key_array;
        delete[] element_array;
        table[i]->setHeadToNull();
        delete table[i];
    }
    delete[] table;
    table = new_table;
}

template <class T>
int HashTable<T>::getTableSize() {
    return table_size;
}

template <class T>
void HashTable<T>::print(){
    cout << "The size of the table is " << table_size << " and it contains " << num_of_elements << " nodes." << endl;
    for (int i=0; i<table_size; i++){
        if (table[i] == nullptr){
            cout << "List number " << i << " : empty" << endl;
        }
        else if (table[i]->getListSize() == 0){
            cout << "List number " << i << " : empty" << endl;
        }
        else {
            cout << "List number " << i << " : ";
            table[i]->print();
        }
    }
}