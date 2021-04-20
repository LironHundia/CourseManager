#include <iostream>

using std::cout;
using std::endl;

template <class T>
List<T>::List() : head(nullptr), list_size(0) {}

template <class T>
List<T>::~List(){
    T* current = head;
    T* to_delete;
    while (current != nullptr){
        to_delete = current;
        current = current->next;
        delete to_delete;
    }
}

template <class T>
List<T>::List(const List& list) : head(nullptr), list_size(list.list_size){
    if (list.list_size > 0){
        head = new T(*(list.head));
        head->next = nullptr;
        head->prev = nullptr;
    }
    if (list.list_size <= 1){
        return;
    }
    T* other_current = list.head->next;
    T* current = head;
    while (other_current != nullptr){
        current->next = new T(*other_current);
        current->next->prev = current;
        current->next->next = nullptr;
        other_current = other_current->next;
        current = current->next;
    }
}

template <class T>
List<T>& List<T>::operator=(const List& list){
    if (this == &list){
        return *this;
    }
    T* current = head;
    T* to_delete;
    while (current != nullptr){
        to_delete = current;
        current = current->next;
        delete to_delete;
    }
    list_size = list.list_size;
    if (list.list_size > 0){
        head = new T(*(list.head));
        head->next = nullptr;
        head->prev = nullptr;
    }
    if (list.list_size <= 1){
        return *this;
    }
    T* other_current = list.head->next;
    current = head;
    while (other_current != nullptr){
        current->next = new T(*other_current);
        current->next->prev = current;
        current->next->next = nullptr;
        other_current = other_current->next;
        current = current->next;
    }
    return *this;
}

template <class T>
void List<T>::add(const T& to_add){
    T* new_node = new T(to_add);
    if (list_size == 0){ //the list is empty
        head = new_node;
        new_node->next = nullptr;
        new_node->prev = nullptr;
    }
    else {
        new_node->next = head;
        new_node->next->prev = new_node;
        new_node->prev = nullptr;
        head = new_node;
    }
    list_size++;
}

template <class T>
T* List<T>::find(int to_find){
    T* current = head;
    while (current != nullptr){
        if (current->getKey() == to_find){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
void List<T>::remove(int to_remove){
    T* node_to_remove = find(to_remove);
    if (node_to_remove == nullptr){
        return;
    }
    if (node_to_remove->next != nullptr && node_to_remove->prev != nullptr){ //the node is in the middle of the list
        node_to_remove->next->prev = node_to_remove->prev;
        node_to_remove->prev->next = node_to_remove->next;
    }
    else if(node_to_remove->next != nullptr && node_to_remove->prev == nullptr){ //the node is the first node and it has node next to it
        node_to_remove->next->prev = nullptr;
        head = node_to_remove->next;
    }
    else if(node_to_remove->next == nullptr && node_to_remove->prev != nullptr){ //the node is the last node and it has node before itself
        node_to_remove->prev->next = nullptr;
    }
    else { //the node is the only node in the list
        head = nullptr;
    }
    delete node_to_remove;
    list_size--;
}

template <class T>
int List<T>::getListSize(){
    return list_size;
}

template <class T>
void List<T>::listToArray(int* key_array, T** element_array){
    T* current = head;
    int i = 0;
    while (current != nullptr){
        if (i >= list_size){
            cout << "Error in function listToArray" << endl;
        }
        element_array[i] = current;
        key_array[i] = current->getKey();
        current = current->next;
        i++;
    }
}

template <class T>
void List<T>::addWithoutAlloc(T* to_add) {
    if (list_size == 0){ //the list is empty
        head = to_add;
        to_add->next = nullptr;
        to_add->prev = nullptr;
    }
    else {
        to_add->next = head;
        to_add->next->prev = to_add;
        to_add->prev = nullptr;
        head = to_add;
    }
    list_size++;
}

template <class T>
void List<T>::setHeadToNull(){
    head = nullptr;
}

template <class T>
void List<T>::print(){
    T* current = head;
    while (current != nullptr){
        cout << current->getKey() << ", ";
        current = current->next;
    }
    cout << endl;
}