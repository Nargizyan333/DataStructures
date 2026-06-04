#ifndef LIST_TPP
#define LIST_TPP

#include "list.hpp"
#include <utility>
#include <iostream>

template <typename T>
DS::ListNode<T>::ListNode()
    : val(), next(nullptr) {}

template <typename T>
DS::ListNode<T>::ListNode(const T &val)
    : val(val), next(nullptr) {}

template <typename T>
DS::ListNode<T>::ListNode(const T &val, DS::ListNode<T> *next)
    : val(val), next(next) {}

template <typename T>
DS::ListNode<T>::ListNode(const DS::ListNode<T> &other)
    : val(other.val), next(other.next) {}

template <typename T>
DS::ListNode<T>::ListNode(DS::ListNode<T> &&other) noexcept
    : val(std::move(other.val)), next(other.next) {
    other.val = T{};
    other.next = nullptr;
}

template <typename T>
DS::ListNode<T> &DS::ListNode<T>::operator=(const DS::ListNode<T> &rhs) {
    if (this != &rhs) {
        val = rhs.val;
        next = rhs.next;
    }
    return *this;
}

template <typename T>
DS::ListNode<T> &DS::ListNode<T>::operator=(DS::ListNode<T> &&rhs) noexcept {
    if (this != &rhs) {
        val = std::move(rhs.val);
        next = rhs.next;
        rhs.val = T{};
        rhs.next = nullptr;
    }
    return *this;
}

template <typename T>
DS::list<T>::list()
    : _size(0), _head(nullptr), _tail(nullptr) {}

template <typename T>
DS::list<T>::list(const DS::list<T> &other)
    : _size(other._size), _head(nullptr), _tail(nullptr) {
    if (!other._head) return;
    _head = new ListNode<T>(other._head->val);
    DS::ListNode<T> *curr1 = _head, *curr2 = other._head->next;
    while (curr2) {
        curr1->next = new ListNode<T>(curr2->val);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    _tail = curr1;
}

template <typename T>
DS::list<T>::list(DS::list<T> &&other) noexcept
        : _size(other._size), _head(other._head), _tail(other._tail) {
    other._head = nullptr;
    other._tail = nullptr;
    other._size = 0;
}

template <typename T>
DS::list<T> &DS::list<T>::operator=(const DS::list<T> &rhs) {
    if (this != &rhs) {
        clear();
        _size = rhs._size;
        if (!rhs._head) {
            return *this;
        }
        _head = new ListNode<T>(rhs._head->val);
        DS::ListNode<T> *curr1 = _head, *curr2 = rhs._head->next;
        while (curr2) {
            curr1->next = new ListNode<T>(curr2->val);
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        _tail = curr1;
    }
    return *this;
}

template <typename T>
DS::list<T> &DS::list<T>::operator=(DS::list<T> &&rhs) noexcept {
    if (this != &rhs) {
        clear();
        _head = rhs._head;
        _tail = rhs._tail;
        _size = rhs._size;
        rhs._head = nullptr;
        rhs._tail = nullptr;
        rhs._size = 0;
    }
    return *this;
}

template <typename T>
void DS::list<T>::clear() {
    DS::ListNode<T> *nodeToDelete = nullptr, *curr = _head;
    while (curr) {
        nodeToDelete = curr;
        curr = curr->next;
        delete nodeToDelete;
    }
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
}

template <typename T>
DS::list<T>::~list() {
    clear();
}

template <typename T>
int DS::list<T>::size() const {
    return _size;
}

template <typename T>
bool DS::list<T>::empty() const {
    return _size == 0;
}

template <typename T>
void DS::list<T>::pushBack(T &&val) {
    if (!_tail) {
        _head = new ListNode<T>(std::move(val));
        _tail = _head;
    } else {
        _tail->next = new ListNode<T>(std::move(val));
        _tail = _tail->next;
    }
    ++_size;
}

template <typename T>
void DS::list<T>::pushBack(const T &val, int count) {
    if (count <= 0) return;
    if (!_head) {
        _head = new ListNode<T>(val);
        _tail = _head;
        ++_size;
        --count;
    }
    while (count--) {
        _tail->next = new ListNode<T>(val);
        _tail = _tail->next;
        ++_size;
    }
}

template <typename T>
void DS::list<T>::pushBack(const DS::list<T> &other) {
    if (this == &other) {
        // copy then append to avoid mutating while iterating self
        DS::list<T> tmp(other);
        pushBack(tmp);
        return;
    }
    DS::ListNode<T> *curr = other._head;
    while (curr) {
        if (!_tail) {
            _head = new ListNode<T>(curr->val);
            _tail = _head;
        } else {
            _tail->next = new ListNode<T>(curr->val);
            _tail = _tail->next;
        }
        ++_size;
        curr = curr->next;
    }
}

template <typename T>
void DS::list<T>::popBack() {
    if (!_head) return;
    if (!_head->next) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
        return;
    }
    DS::ListNode<T> *curr = _head;
    while (curr->next->next)
        curr = curr->next;
    delete _tail;
    _tail = curr;
    _tail->next = nullptr;
    --_size;
}

template <typename T>
void DS::list<T>::popBack(int count) {
    if (!_head || count <= 0) return;
    if (count >= _size) {
        clear();
        return;
    }
    int toKeep = _size - count;
    _size -= count;
    DS::ListNode<T> *curr = _head, *nodeToDelete = nullptr;
    while (--toKeep)              // walk to the new tail (was off-by-one safe but fragile)
        curr = curr->next;
    _tail = curr;
    curr = curr->next;
    _tail->next = nullptr;
    while (curr) {
        nodeToDelete = curr;
        curr = curr->next;
        delete nodeToDelete;
    }
}

template <typename T>
void DS::list<T>::pushFront(T &&val) {
    if (!_head) {
        _head = new ListNode<T>(std::move(val));
        _tail = _head;
        _size = 1;
        return;
    }
    _head = new ListNode<T>(std::move(val), _head);
    ++_size;
}

template <typename T>
void DS::list<T>::pushFront(const T &val, int count) {
    if (count <= 0) return;
    if (!_head) {
        _head = new ListNode<T>(val);
        _tail = _head;
        ++_size;
        --count;
    }
    while (count--) {
        _head = new ListNode<T>(val, _head);
        ++_size;
    }
}

template <typename T>
void DS::list<T>::pushFront(const DS::list<T> &other) {
    if (!other._head) return;
    if (!_head) {
        *this = other;
        return;
    }
    auto *tmp = new ListNode<T>(other._head->val);
    DS::ListNode<T> *curr1 = tmp, *curr2 = other._head->next;
    while (curr2) {
        curr1->next = new ListNode<T>(curr2->val);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    curr1->next = _head;
    _head = tmp;
    _size += other._size;
}

template <typename T>
void DS::list<T>::popFront() {
    if (!_head) return;
    DS::ListNode<T> *nodeToDelete = _head;
    _head = _head->next;
    delete nodeToDelete;
    if (!_head) _tail = nullptr;
    --_size;
}

template <typename T>
void DS::list<T>::popFront(int count) {
    if (count <= 0) return;
    if (count >= _size) {
        clear();
        return;
    }
    DS::ListNode<T> *nodeToDelete = nullptr;
    while (count--) {
        nodeToDelete = _head;
        _head = _head->next;
        delete nodeToDelete;
        --_size;
    }
}

template <typename T>
void DS::list<T>::print() const {
    DS::ListNode<T> *curr = _head;
    while (curr) {
        std::cout << curr->val;
        if (curr->next)
            std::cout << " -> ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

#endif //LIST_TPP
