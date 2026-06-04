#ifndef TREENODE_TPP
#define TREENODE_TPP

#include "TreeNode.hpp"

template <typename T>
DS::TreeNode<T>::TreeNode(const T &val)
    : val(val), left(nullptr), right(nullptr), p(nullptr), height(1) {}

#endif //TREENODE_TPP
