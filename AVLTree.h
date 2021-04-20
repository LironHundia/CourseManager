//
// Created by רוני on 31/12/2020.
//

#ifndef DS_WET2_AVLTREE_H
#define DS_WET2_AVLTREE_H

#include "library2.h"

template <class T>
class AVLTree{
private:
    T* root;
public:
    AVLTree();
    ~AVLTree();
    StatusType add(const T& t, T** new_node_ptr);
    void remove(const T& t);
    void print_tree();
    T* find(const T& t);
    void test(const T& t);
    T* find_max();
    void max_to_min(T* max, int* courses, int* classes, int* counter, int total_to_print); // the return value is "how much we have printed during the function"
    T* select(int i);
};

#include "AVLTreeImp.h"

#endif //DS_WET2_AVLTREE_H
