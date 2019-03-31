#ifndef _BALANCED_BINARY_SEARCH_TREE_H_
#define _BALANCED_BINARY_SEARCH_TREE_H_
#include <iostream>
using namespace std;

template <class KeyType, class ItemType>
struct BBST_Node
{
    BBST_Node<KeyType, ItemType>* left;
    BBST_Node<KeyType, ItemType>* right;
    KeyType key;
    ItemType item;
    int depth;

    BBST_Node();
    BBST_Node(KeyType k);
    BBST_Node(KeyType k, ItemType it);
    void new_depth();
};

template <class KeyType, class ItemType>
class BBST
{
private:
    BBST_Node<KeyType, ItemType>* root;

    // private member functions
    BBST_Node<KeyType, ItemType>* LL(BBST_Node<KeyType,ItemType>*tmp);
    BBST_Node<KeyType, ItemType>* LR(BBST_Node<KeyType,ItemType>*tmp);
    BBST_Node<KeyType, ItemType>* RR(BBST_Node<KeyType,ItemType>* tmp);
    BBST_Node<KeyType, ItemType>* RL(BBST_Node<KeyType,ItemType>* tmp);
    BBST_Node<KeyType, ItemType>* add(const KeyType& key, BBST_Node<KeyType,ItemType>* tmp, BBST_Node<KeyType,ItemType>*& nd);
    int dep(BBST_Node<KeyType, ItemType>* n);

public:
    BBST();
    BBST_Node<KeyType, ItemType>* find(KeyType key);
    BBST_Node<KeyType, ItemType>* end();
    ItemType& operator[](const KeyType& key);
};
#endif // !_BALANCED_BINARY_SEARCH_TREE_H_
