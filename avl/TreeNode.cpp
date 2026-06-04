#ifndef TREENODE_CPP
#define TREENODE_CPP

#include "TreeNode.tpp"

template <typename T>
DS::TreeNode<T>::TreeNode(const T &val)
    : val(val), left(nullptr), right(nullptr), p(nullptr), height(1) {}

#endif //TREENODE_CPP
