#ifndef AVL_CPP
#define AVL_CPP

#include "avl.tpp"
#include <algorithm>
#include <stdexcept>

template <typename T>
DS::avl<T>::avl()
    : _root(nullptr) {}

template <typename T>
DS::avl<T>::avl(const DS::avl<T> &other)
    : _root(copy(other._root)) {}

template <typename T>
DS::avl<T>::avl(DS::avl<T> &&other) noexcept
    : _root(other._root) {
    other._root = nullptr;
}

template <typename T>
DS::avl<T> &DS::avl<T>::operator=(const DS::avl<T> &rhs) {
    if (this != &rhs) {
        clear(_root);
        _root = nullptr;
        _root = copy(rhs._root);
    }
    return *this;
}

template <typename T>
DS::avl<T> &DS::avl<T>::operator=(DS::avl<T> &&rhs) noexcept {
    if (this != &rhs) {
        clear(_root);
        _root = rhs._root;
        rhs._root = nullptr;
    }
    return *this;
}

template <typename T>
DS::TreeNode<T> *DS::avl<T>::copy(DS::TreeNode<T> *node) {
    if (!node) return nullptr;
    DS::TreeNode<T> *newNode = new TreeNode<T>(node->val);
    newNode->height = node->height;
    newNode->left = copy(node->left);
    if (newNode->left) newNode->left->p = newNode;
    newNode->right = copy(node->right);
    if (newNode->right) newNode->right->p = newNode;
    return newNode;
}

template <typename T>
DS::avl<T>::~avl() {
    clear(_root);
}

template <typename T>
bool DS::avl<T>::search(const T &val) const {
    return search(_root, val) != nullptr;
}

template <typename T>
DS::TreeNode<T> *DS::avl<T>::search(DS::TreeNode<T> *root, const T &val) const {
    while (root) {
        if (root->val == val) return root;
        if (val > root->val) root = root->right;
        else root = root->left;
    }
    return nullptr;
}

template <typename T>
void DS::avl<T>::insert(const T &val) {
    if (!_root) {
        _root = new TreeNode<T>(val);
        return;
    }
    DS::TreeNode<T> *curr = _root;
    DS::TreeNode<T> *prev = nullptr;
    while (curr) {
        if (val == curr->val) return; // duplicates are ignored
        prev = curr;
        curr = (val > curr->val) ? curr->right : curr->left;
    }
    DS::TreeNode<T> *node = new TreeNode<T>(val);
    node->p = prev;
    if (val > prev->val) prev->right = node;
    else prev->left = node;
    balance(prev);
}

template <typename T>
void DS::avl<T>::remove(const T &val) {
    DS::TreeNode<T> *nodeToDelete = search(_root, val);
    if (nodeToDelete)
        remove(nodeToDelete);
}

template <typename T>
void DS::avl<T>::remove(DS::TreeNode<T> *node) {
    if (!node) return;
    DS::TreeNode<T> *y = node;
    if (node->left && node->right)
        y = getMax(node->left);
    DS::TreeNode<T> *x = y->left ? y->left : y->right;
    if (x)
        x->p = y->p;
    if (!y->p)
        _root = x;
    else if (y == y->p->left)
        y->p->left = x;
    else
        y->p->right = x;
    DS::TreeNode<T> *startBalance = y->p;
    if (y != node)
        node->val = y->val;
    delete y;
    balance(startBalance);
}

template <typename T>
T DS::avl<T>::getMin() const {
    if (!_root) throw std::out_of_range("getMin() on empty tree");
    return getMin(_root)->val;
}

template <typename T>
T DS::avl<T>::getMax() const {
    if (!_root) throw std::out_of_range("getMax() on empty tree");
    return getMax(_root)->val;
}

template <typename T>
T DS::avl<T>::getPredecessor(const T &val) const {
    DS::TreeNode<T> *curr = _root;
    DS::TreeNode<T> *predecessor = nullptr;
    while (curr) {
        if (curr->val < val) {
            predecessor = curr;
            curr = curr->right;
        } else
            curr = curr->left;
    }
    if (!predecessor) throw std::out_of_range("no predecessor exists");
    return predecessor->val;
}

template <typename T>
T DS::avl<T>::getSuccessor(const T &val) const {
    DS::TreeNode<T> *curr = _root;
    DS::TreeNode<T> *successor = nullptr;
    while (curr) {
        if (curr->val > val) {
            successor = curr;
            curr = curr->left;
        } else
            curr = curr->right;
    }
    if (!successor) throw std::out_of_range("no successor exists");
    return successor->val;
}

template <typename T>
int DS::avl<T>::getHeight() const {
    return height(_root);
}

template <typename T>
DS::TreeNode<T> *DS::avl<T>::getMin(DS::TreeNode<T> *node) const {
    while (node->left) node = node->left;
    return node;
}

template <typename T>
DS::TreeNode<T> *DS::avl<T>::getMax(DS::TreeNode<T> *node) const {
    while (node->right) node = node->right;
    return node;
}

template <typename T>
void DS::avl<T>::clear(DS::TreeNode<T> *node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
int DS::avl<T>::height(const DS::TreeNode<T> *node) {
    return node ? node->height : 0;
}

template <typename T>
void DS::avl<T>::updateHeight(DS::TreeNode<T> *node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
}

template <typename T>
int DS::avl<T>::getBF(const DS::TreeNode<T> *node) const {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

template <typename T>
void DS::avl<T>::balance(DS::TreeNode<T> *node) {
    if (!node) return;
    updateHeight(node);
    const int bf = getBF(node);
    if (bf > 1) {
        if (getBF(node->left) >= 0)
            rightRotate(node);
        else {
            leftRotate(node->left);
            rightRotate(node);
        }
    } else if (bf < -1) {
        if (getBF(node->right) <= 0)
            leftRotate(node);
        else {
            rightRotate(node->right);
            leftRotate(node);
        }
    }
    balance(node->p);
}

template <typename T>
void DS::avl<T>::leftRotate(DS::TreeNode<T> *x) {
    DS::TreeNode<T> *y = x->right;
    x->right = y->left;
    if (y->left) y->left->p = x;
    y->p = x->p;
    if (!x->p) _root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
    updateHeight(x);
    updateHeight(y);
}

template <typename T>
void DS::avl<T>::rightRotate(DS::TreeNode<T> *x) {
    DS::TreeNode<T> *y = x->left;
    x->left = y->right;
    if (y->right) y->right->p = x;
    y->p = x->p;
    if (!x->p) _root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->right = x;
    x->p = y;
    updateHeight(x);
    updateHeight(y);
}

#endif //AVL_CPP
