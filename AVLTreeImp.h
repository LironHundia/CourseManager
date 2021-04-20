#include <iostream>
#include "library2.h"
using std::cout;
using std::endl;

template <class T>
static void NodeDestroy(T* current);

template <class T>
static void print_node(T* current);

template <class T>
static void RemoveNode(T* current, T** ptr_to_root);

template <class T>
static void swapTwoSons(T* current, T** ptr_to_root);

template <class T>
static void fixTree(T* current, T** ptr_to_root);

template <class T>
static int checkBF(T* current);

template <class T>
static void checkRollType(T* current, int BF, T** ptr_to_root);

template <class T>
static int calculateHeight(T* current);

template <class T>
static int calculateRank(T* current); //Changed - New function

template <class T>
static void RR_roll(T* current, T** ptr_to_root);

template <class T>
static void LL_roll(T* current, T** ptr_to_root);

template <class T>
static void RL_roll(T* current, T** ptr_to_root);

template <class T>
static void LR_roll(T* current, T** ptr_to_root);

template <class T>
static void max_to_min_rec(T* current, int* courses, int* classes, int total_to_print, int* counter, int from);

template <class T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <class T>
AVLTree<T>::~AVLTree(){
    NodeDestroy(root);
}

template <class T>
void NodeDestroy(T* current){
    if (current == nullptr){
        return;
    }
    NodeDestroy(current->left);
    NodeDestroy(current->right);
    delete current;
}

template <class T>
StatusType AVLTree<T>::add(const T& t, T** new_node_ptr){
    T* new_node = new T(t);
    new_node->right = nullptr;
    new_node->left = nullptr;
    new_node->top = nullptr;
    new_node->height = 0;
    new_node->rank = 1; //Changed
    // check the root
    if (root == nullptr){
        *new_node_ptr = new_node;
        root = new_node;
        return SUCCESS;
    }
    T* current = root;
    while (current != nullptr){
        if (*current == *new_node){ //the new t already exists
            delete new_node;
            return FAILURE;
        }
        else if (*current < *new_node){ // t is going to the right
            if (current->right == nullptr){
                current->right = new_node;
                new_node->top = current;
                fixTree(new_node->top, &root);
                *new_node_ptr = new_node;
                return SUCCESS;
            }
            current = current->right;
        }
        else{ // t is going to the left
            if (current->left == nullptr){
                current->left = new_node;
                new_node->top = current;
                fixTree(new_node->top, &root);
                *new_node_ptr = new_node;
                return SUCCESS;
            }
            current = current->left;
        }
    }
    return FAILURE;
}

template <class T>
void swapTwoSons(T* current, T** ptr_to_root){
    T* next = current->right;
    while (next->left != nullptr){
        next = next->left;
    }
    if (*ptr_to_root == current){
        *ptr_to_root = next;
    }
    // switch the top, right, left and height fields of next and current
    // need to update also the top, right, left fields of the sons and fathers
    T* top_of_current = current->top;
    T* right_of_current = current->right;
    T* left_of_current = current->left;
    T* top_of_next = next->top;
    T* right_of_next = next->right;
    T* left_of_next = next->left;
    // in case next is not the son of current
    if (current->right != next){
        current->top = top_of_next;
        current->right = right_of_next;
        current->left = left_of_next;
        next->top = top_of_current;
        next->left = left_of_current;
        next->right = right_of_current;
        if (top_of_current != nullptr && top_of_current->right == current){
            top_of_current->right = next;
        }
        else if (top_of_current != nullptr && top_of_current->left == current){
            top_of_current->left = next;
        }
        right_of_current->top = next;
        left_of_current->top = next;
        top_of_next->left = current;
        if (right_of_next != nullptr) {
            right_of_next->top = current;
        }
    }
        // in case next is the right son of current
    else{
        current->top = next;
        current->right = right_of_next;
        current->left = nullptr;
        next->top = top_of_current;
        next->right = current;
        next->left = left_of_current;
        if (top_of_current != nullptr && top_of_current->right == current){
            top_of_current->right = next;
        }
        else if(top_of_current != nullptr && top_of_current->left == current){
            top_of_current->left = next;
        }
        left_of_current->top = next;
        if (right_of_next != nullptr){
            right_of_next->top =  current;
        }
    }

    int temp_height = current->height;
    current->height = next->height;
    next->height = temp_height;

    int temp_rank = current->rank; //Changed
    current->rank = next->rank; //Changed
    next->rank = temp_rank; //Changed
}

template <class T>
void AVLTree<T>::remove(const T& t){
    if (root == nullptr){
        return;
    }
    if (*root == t && root->left == nullptr && root->right == nullptr){
        delete root;
        root = nullptr;
    }
    T* current = root;
    while (current != nullptr){
        if (*current == t){
            if ((current->right != nullptr) && (current->left != nullptr)){ // t has two sons
                swapTwoSons(current, &root);
            }
            // assumption - current has 0/1 sons in this point
            RemoveNode(current, &root);
            return;
        }
        else if (*current < t){
            current = current->right;
        }
        else{
            current = current->left;
        }
    }
    //if we reached here, t doesn't exist
}

template <class T>
void RemoveNode(T* current, T** ptr_to_root){
    if ((current->right == nullptr) && (current->left == nullptr)){ // current has no sons
        if (current->top->right == current){
            current->top->right = nullptr;
        }
        else{
            current->top->left = nullptr;
        }
    }
    else if ((current->right != nullptr) && (current->left == nullptr)){ // current has one right son
        if (current->top != nullptr) { //current is not the root
            if (current->top->right == current) {
                current->top->right = current->right;
            } else {
                current->top->left = current->right;
            }
            //expirimental!!!! the line below:
            current->right->top = current->top;
        }
        else{ //current is the root
            *ptr_to_root = current->right;
            //expirimental!!!! the line below:
            current->right->top = nullptr;
        }
    }
    else if ((current->right == nullptr) && (current->left != nullptr)){ // current has one left son
        if (current->top != nullptr){   //current is not the root
            if (current->top->right == current) {
                current->top->right = current->left;
            } else {
                current->top->left = current->left;
            }
            //expirimental!!!! the line below:
            current->left->top = current->top;
        }
        else{ //current is the root
            *ptr_to_root = current->left;
            //expirimental!!!! the line below:
            current->left->top = nullptr;
        }
    }
    T* top = current->top;
    delete current;
    fixTree(top, ptr_to_root);
}

template <class T>
void AVLTree<T>::print_tree(){
    print_node(root);
}

template <class T>
void print_node(T* current){
    if (current == nullptr){
        return;
    }
    print_node(current->left);
    current->print();
    print_node(current->right);
}

template <class T>
void fixTree(T* current, T** ptr_to_root){
    if (current == nullptr){
        return;
    }
    int height_right = current->right != nullptr ? current->right->height : -1;
    int height_left = current->left != nullptr ? current->left->height : -1;
    current->height = 1 + (height_left < height_right ? height_right : height_left);
    int rank_right = current->right != nullptr ? current->right->rank : 0; //Changed
    int rank_left = current->left != nullptr ? current->left->rank : 0; //Changed
    current->rank = 1 + rank_left + rank_right; //Changed
    int BF = height_left - height_right;
    T* top_of_current = current->top;
    if (BF == 2 || BF == -2){
        //std::cout << "The tree is not balanced. " << std::endl;
        //current->print();
        //std::cout << std::endl;
        checkRollType(current, BF, ptr_to_root);
    }
    fixTree(top_of_current, ptr_to_root);
}

template <class T>
int checkBF(T* current){
    int height_right = current->right != nullptr ? current->right->height : -1;
    int height_left = current->left != nullptr ? current->left->height : -1;
    return height_left - height_right;
}

template <class T>
void checkRollType(T* current, int BF, T** ptr_to_root){
    if (BF == -2){
        int right_BF = checkBF(current->right);
        if (right_BF == 1){
            //cout << "Entering RL_roll" << endl;
            RL_roll(current, ptr_to_root);
        }
        if (right_BF <= 0){
            //cout << "Entering RR_roll" << endl;
            RR_roll(current, ptr_to_root);
        }
    }
    if (BF == 2){
        int left_BF = checkBF(current->left);
        if (left_BF == -1){
            //cout << "Entering LR_roll" << endl;
            LR_roll(current, ptr_to_root);
        }
        if (left_BF >= 0){
            //cout << "Entering LL_roll" << endl;
            LL_roll(current, ptr_to_root);
        }
    }
}

template <class T>
int calculateHeight(T* current){
    if (current == nullptr){
        return -1;
    }
    int height_right = current->right != nullptr ? current->right->height : -1;
    int height_left = current->left != nullptr ? current->left->height : -1;
    return 1 + (height_left < height_right ? height_right : height_left);
}

template <class T>
int calculateRank(T* current){ //Changed - New function
    if (current == nullptr){
        return 0;
    }
    int rank_right = current->right != nullptr ? current->right->rank : 0;
    int rank_left = current->left != nullptr ? current->left->rank : 0;
    return 1 + rank_left + rank_right;
}

template <class T>
void LL_roll(T* current, T** ptr_to_root){
    T* B = current;
    T* A = current->left;

    //updating the parent of current
    if (B->top == nullptr) { // B is the root
        *ptr_to_root = A;
        A->top = nullptr;
    }
    else{ // B is not the root
        if (B->top->right == B){ // B is the right son of his parent
            B->top->right = A;
        }
        else{  // B is the left son of his parent
            B->top->left = A;
        }
        A->top = B->top;
    }

    // update pointers
    T* AR = A->right;
    A->right = B;
    B->left = AR;
    B->top = A;
    if (AR != nullptr){
        AR->top = B;
    }

    // update heights
    B->height = calculateHeight(B);
    A->height = calculateHeight(A);

    //update ranks
    B->rank = calculateRank(B); //Changed
    A->rank = calculateRank(A); //Changed
}

template <class T>
void RR_roll(T* current, T** ptr_to_root){
    T* B = current;
    T* A = current->right;

    //updating the parent of current
    if (B->top == nullptr) { // B is the root
        *ptr_to_root = A;
        A->top = nullptr;
    }
    else{ // B is not the root
        if (B->top->right == B){ // B is the right son of his parent
            B->top->right = A;
        }
        else{  // B is the left son of his parent
            B->top->left = A;
        }
        A->top = B->top;
    }

    // update pointers
    T* AL = A->left;
    A->left = B;
    B->right = AL;
    B->top = A;
    if (AL != nullptr){
        AL->top = B;
    }

    // update heights
    B->height = calculateHeight(B);
    A->height = calculateHeight(A);

    //update ranks
    B->rank = calculateRank(B); //Changed
    A->rank = calculateRank(A); //Changed
}

template <class T>
void RL_roll(T* current, T** ptr_to_root){
    T* C = current;
    T* A = C->right;
    T* B = A->left;

    //updating the parent of current
    if (C->top == nullptr) { // C is the root
        *ptr_to_root = B;
        B->top = nullptr;
    }
    else{ // C is not the root
        if (C->top->right == C){ // C is the right son of his parent
            C->top->right = B;
        }
        else{  // C is the left son of his parent
            C->top->left = B;
        }
        B->top = C->top;
    }

    T* BL = B->left;
    T* BR = B->right;
    // update A's pointers
    A->left = B->right;
    A->top = B;
    // update C's pointers
    C->right = B->left;
    C->top = B;
    // update B's pointers
    B->right = A;
    B->left = C;
    // update BL's and BR' parents
    if (BL != nullptr){
        BL->top = C;
    }
    if (BR != nullptr){
        BR->top = A;
    }

    // update heights
    A->height = calculateHeight(A);
    C->height = calculateHeight(C);
    B->height = calculateHeight(B);

    //update ranks
    A->rank = calculateRank(A); //Changed
    C->rank = calculateRank(C); //Changed
    B->rank = calculateRank(B); //Changed
}

template <class T>
void LR_roll(T* current, T** ptr_to_root){
    T* C = current;
    T* A = C->left;
    T* B = A->right;

    //updating the parent of current
    if (C->top == nullptr) { // C is the root
        *ptr_to_root = B;
        B->top = nullptr;
    }
    else{ // C is not the root
        if (C->top->right == C){ // C is the right son of his parent
            C->top->right = B;
        }
        else{  // C is the left son of his parent
            C->top->left = B;
        }
        B->top = C->top;
    }

    T* BL = B->left;
    T* BR = B->right;
    // update A's pointers
    A->right = B->left;
    A->top = B;
    // update C's pointers
    C->left = B->right;
    C->top = B;
    // update B's pointers
    B->right = C;
    B->left = A;
    // update BL's and BR' parents
    if (BL != nullptr){
        BL->top = A;
    }
    if (BR != nullptr){
        BR->top = C;
    }

    // update heights
    A->height = calculateHeight(A);
    C->height = calculateHeight(C);
    B->height = calculateHeight(B);

    //update ranks
    A->rank = calculateRank(A); //Changed
    C->rank = calculateRank(C); //Changed
    B->rank = calculateRank(B); //Changed
}

template <class T>
T* AVLTree<T>::find(const T& t){
    if (root == nullptr){
        return nullptr;
    }
    T* current = root;
    while (current != nullptr){
        if (*current == t){
            return current;
        }
        else if(*current < t){
            current = current->right;
        }
        else{
            current = current->left;
        }
    }
    return nullptr;
}

template <class T>
void AVLTree<T>::test(const T& t) {
    T* current = root;
    while (current != nullptr){
        if (*current == t){
            if (current->right != nullptr || current->left != nullptr){
                cout << "Error! one of the sons of the leaf is not null" << endl;
            }
            if (current->right == nullptr && current->left == nullptr){
                cout << "The sons are null!" << endl;
            }
            break;
        }
        else if (*current < t) {
            current = current->right;
        }
        else{
            current = current->left;
        }
    }
    //In this point, current should be t, which is leaf
    while (current != nullptr){
        current->print();
        if (current == root){
            cout << "Root!" << endl;
            if (current->top != nullptr){
                cout << "Error! Root's top is not null" << endl;
            }
            if (current->top == nullptr){
                cout << "Yeahhhhh root's top is null" << endl;
            }
        }
        current = current->top;
    }
}


template <class T>
T* AVLTree<T>::find_max() {
    if (root == nullptr){
        return nullptr;
    }
    T* current = root;
    while (current->right != nullptr){
        current = current->right;
    }
    return current;
}


// *** current->add_current_to_arrays(courses+(*counter), classes+(*counter)); should be fixed!!! ***
template <class T>
void AVLTree<T>::max_to_min(T* max, int* courses, int* classes, int* counter, int total_to_print){
    if (max == nullptr){
        return;
    }
    else{
        max->add_current_to_arrays(courses+(*counter), classes+(*counter), counter, total_to_print);
    }
    max_to_min_rec(max->left, courses, classes, total_to_print, counter, 0);
    max_to_min_rec(max->top, courses, classes, total_to_print, counter, -1);
}
// from: 0 - from top       -1 - from right

template <class T>
void max_to_min_rec(T* current, int* courses, int* classes, int total_to_print, int* counter, int from){
    if (*counter == total_to_print || current == nullptr){
        return;
    }
    if (from == 0){ // from top
        // go to right
        max_to_min_rec(current->right, courses, classes, total_to_print, counter, 0);
        //add current to the arrays and increase the counter
        if ((*counter) == total_to_print){
            return;
        }
        current->add_current_to_arrays(courses+(*counter), classes+(*counter), counter, total_to_print);
        // go to left
        max_to_min_rec(current->left, courses, classes, total_to_print, counter, 0);
    }
    else if (from == -1){ // from right
        //add current to the arrays and increase the counter
        current->add_current_to_arrays(courses+(*counter), classes+(*counter), counter, total_to_print);
        // go to left
        max_to_min_rec(current->left, courses, classes, total_to_print, counter, 0);
        // go to top
        max_to_min_rec(current->top, courses, classes, total_to_print, counter, -1);
    }
}

template <class T>
T* AVLTree<T>::select(int i){
    T* current = root;
    int rank_left;
    while (current != nullptr){
        rank_left = calculateRank(current->left);
        if (rank_left == i-1){
            return current;
        }
        else if (rank_left > i-1){
            current = current->left;
        }
        else{
            i = i - rank_left - 1;
            current = current->right;
        }
    }
    return nullptr;
}