//
// Created by רוני on 01/01/2021.
//

#ifndef DS_WET2_LIST_H
#define DS_WET2_LIST_H

template <class T>
class List{
private:
    T* head;
    int list_size;

public:
    List();
    ~List();
    List(const List& list);
    List& operator=(const List& list);

    void add(const T& to_add);
    T* find(int to_find);
    void remove(int to_remove);
    int getListSize();
    void listToArray(int* key_array, T** element_array);
    void addWithoutAlloc(T* to_add);
    void setHeadToNull();
    void print();
};

#include "ListImp.h"

#endif //DS_WET2_LIST_H
