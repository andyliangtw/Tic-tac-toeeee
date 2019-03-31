#include "BalancedBinarySearchTree.h"

//=======================================================
// BBST_Node
//=======================================================
template<class KeyType, class ItemType>
BBST_Node<KeyType, ItemType>::BBST_Node()
    : left(nullptr), right(nullptr), depth(0)
{
}

template<class KeyType, class ItemType>
BBST_Node<KeyType, ItemType>::BBST_Node(KeyType k)
    : key(k), left(nullptr), right(nullptr), depth(1)
{
}

template<class KeyType, class ItemType>
BBST_Node<KeyType, ItemType>::BBST_Node(KeyType k, ItemType it)
    : key(k), item(it), left(nullptr), right(nullptr), depth(1)
{
}

template<class KeyType, class ItemType>
void BBST_Node<KeyType, ItemType>::new_depth()
{
    int l = 0, r = 0;
    if(left != nullptr)
        l = left->depth;
    if(right != nullptr)
        r = right->depth;

    if(l < r)
        depth = r;
    else
        depth = l;
}

//=======================================================
// BBST
//=======================================================
template<class KeyType, class ItemType>
BBST<KeyType, ItemType>::BBST() : root(nullptr)
{
}

template<class KeyType,class ItemType>
BBST_Node<KeyType, ItemType>* BBST<KeyType, ItemType>::find(KeyType key)
{
    BBST_Node<KeyType, ItemType>* tmp = root;
    while(tmp != nullptr)
    {
        if(tmp->key == key)
            break;
        else if(tmp->key > key)
            tmp = tmp->left;
        else // tmp->key < key
            tmp = tmp->right;
    }
    return tmp;
}

template<class KeyType, class ItemType>
BBST_Node<KeyType, ItemType>* BBST<KeyType, ItemType>::end()
{
    return nullptr;
}

template<class KeyType, class ItemType>
ItemType& BBST<KeyType, ItemType>::operator[](const KeyType& key)
{
    BBST_Node<KeyType, ItemType>* tmp = root;
    BBST_Node<KeyType, ItemType>* nd = nullptr;
    root = add(key, root, nd);
    return nd->item;
}

template<class KeyType,class ItemType>
BBST_Node<KeyType, ItemType>* BBST<KeyType, ItemType>::LL(BBST_Node<KeyType, ItemType> *tmp)
{
    BBST_Node<KeyType, ItemType>* L = tmp->left;
    tmp->left = L->right;
    tmp->new_depth();
    L->new_depth();
    return L;
}

template<class KeyType,class ItemType>
BBST_Node<KeyType, ItemType>* BBST<KeyType, ItemType>::LR(BBST_Node<KeyType, ItemType> *tmp)
{
    BBST_Node<KeyType, ItemType>* L = nullptr;
    BBST_Node<KeyType, ItemType>* NR = (tmp->left)->right;
    L = tmp->left;
    L->right = (L->right)->left;
    L->new_depth();
    NR->left = L;
    tmp->left = NR->right;
    NR->right = tmp;
    tmp->new_depth();
    NR->new_depth();
    return NR;
}

template<class KeyType,class ItemType>
BBST_Node<KeyType, ItemType>* BBST<KeyType, ItemType>::RR(BBST_Node<KeyType, ItemType> *tmp)
{
    BBST_Node<KeyType, ItemType> *R = tmp->right;
    tmp->right = R->left;
    R->left = tmp;
    tmp->new_depth();
    R->new_depth();
    return R;
}

template<class KeyType,class ItemType>
BBST_Node<KeyType, ItemType>* BBST<KeyType, ItemType>::RL(BBST_Node<KeyType, ItemType> *tmp)
{
    BBST_Node<KeyType, ItemType>* NewRoot = nullptr;
    BBST_Node<KeyType, ItemType>* R = tmp->right;

    NewRoot = R->left;
    R->left = NewRoot->right;
    R->new_depth();
    NewRoot->right = R;
    tmp->right = R->left;
    R->left = tmp;
    tmp->new_depth();
    NewRoot->new_depth();
    return NewRoot;
}

template<class KeyType,class ItemType>
BBST_Node<KeyType, ItemType>* BBST<KeyType, ItemType>::add(const KeyType& key, BBST_Node<KeyType, ItemType>* tmp, BBST_Node<KeyType, ItemType>*& nd)
{
    if(tmp == nullptr)
    {
        nd = new BBST_Node<KeyType, ItemType>(key);
        return nd;
    }
    if(tmp->key == key)
    {
        nd = tmp;
        return tmp;
    }
    else if(tmp->key > key)
    {
        if(tmp->left == nullptr)
            tmp->left = new BBST_Node<KeyType, ItemType>(key);
        
        tmp->left = add(key, tmp->left, nd);
        
        if((dep(tmp->left) - dep(tmp->right)) > 1)
        {
            if(dep((tmp->left)->right) > dep(tmp->left->left))
                return LR(tmp);
            else
                return LL(tmp);
        }
        else
        {
            tmp->new_depth();
            return tmp;
        }
    }
    else // tmp->key < key
    {
        if(tmp->right == nullptr)
            tmp->right = new BBST_Node<KeyType, ItemType>(key);

        tmp->right = add(key,tmp->right,nd);
        if(dep(tmp->right) - dep(tmp->left) >1)
        {
            if(dep(tmp->right->right) < dep(tmp->right->left))
                return RL(tmp);
            else
                return RR(tmp);
        }
        else
        {
            tmp->new_depth();
            return tmp;
        }
    }
}

template<class KeyType, class ItemType>
int BBST<KeyType, ItemType>::dep(BBST_Node<KeyType, ItemType>* n)
{
    if(n == nullptr)
        return 0;
    else
        return n->depth;
}
