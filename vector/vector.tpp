#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "vector.hpp"
#include <stdexcept>
#include <algorithm>

template <typename T>
DS::vector<T>::vector()
    : _ptr(nullptr), _capacity(0), _size(0) {}

template <typename T>
DS::vector<T>::vector(const int size, const T &val)
    : _ptr(nullptr), _capacity(0), _size(0) {
    if (size < 0) throw std::invalid_argument("negative size");
    if (size > 0) {
        _ptr = new T[size];
        _capacity = _size = size;
        for (int i = 0; i < _size; ++i)
            _ptr[i] = val;
    }
}

template <typename T>
DS::vector<T>::vector(const DS::vector<T> &other)
    : _ptr(other._capacity ? new T[other._capacity] : nullptr),
      _capacity(other._capacity), _size(other._size) {
    for (int i = 0; i < _size; ++i)
        _ptr[i] = other._ptr[i];
}

template <typename T>
DS::vector<T>::vector(DS::vector<T> &&other) noexcept
    : _ptr(other._ptr), _capacity(other._capacity), _size(other._size) {
    other._ptr = nullptr;
    other._capacity = 0;
    other._size = 0;
}

template <typename T>
DS::vector<T> &DS::vector<T>::operator=(const DS::vector<T> &rhs) {
    if (this != &rhs) {
        T *tmp = rhs._capacity ? new T[rhs._capacity] : nullptr;
        for (int i = 0; i < rhs._size; ++i)
            tmp[i] = rhs._ptr[i];
        delete[] _ptr;
        _ptr = tmp;
        _capacity = rhs._capacity;
        _size = rhs._size;
    }
    return *this;
}

template <typename T>
DS::vector<T> &DS::vector<T>::operator=(DS::vector<T> &&rhs) noexcept {
    if (this != &rhs) {
        delete[] _ptr;
        _ptr = rhs._ptr;
        _capacity = rhs._capacity;
        _size = rhs._size;
        rhs._ptr = nullptr;
        rhs._size = 0;
        rhs._capacity = 0;
    }
    return *this;
}

template <typename T>
T &DS::vector<T>::operator[](const int index) {
    if (index < 0 || index >= _size) throw std::out_of_range("vector index out of range");
    return _ptr[index];
}

template <typename T>
const T &DS::vector<T>::operator[](const int index) const {
    if (index < 0 || index >= _size) throw std::out_of_range("vector index out of range");
    return _ptr[index];
}

template <typename T>
DS::vector<T>::~vector() {
    clear();
}

template <typename T>
void DS::vector<T>::pushBack(const T &val) {
    if (_size == _capacity) {
        if (!_capacity) {
            _capacity = 1;
            _ptr = new T[_capacity];
        } else {
            _capacity *= 2;
            T *tmp = new T[_capacity];
            for (int i = 0; i < _size; ++i)
                tmp[i] = _ptr[i];
            delete[] _ptr;
            _ptr = tmp;
        }
    }
    _ptr[_size++] = val;
}

template <typename T>
void DS::vector<T>::pushBack(const T &val, int count) {
    if (count <= 0) return;
    if (_size + count > _capacity) {
        if (!_capacity) {
            _capacity = count;
            _ptr = new T[_capacity];
        } else {
            _capacity = std::max(_capacity * 2, _size + count);
            T *tmp = new T[_capacity];
            for (int i = 0; i < _size; ++i)
                tmp[i] = _ptr[i];
            delete[] _ptr;
            _ptr = tmp;
        }
    }
    for (int i = 0; i < count; ++i)
        _ptr[_size++] = val;
}

template <typename T>
void DS::vector<T>::pushBack(const DS::vector<T> &other) {
    if (this == &other || !other._size) return;
    if (_size + other._size > _capacity) {
        _capacity = std::max(_capacity * 2, _size + other._size);
        T *tmp = new T[_capacity];
        for (int i = 0; i < _size; ++i)
            tmp[i] = _ptr[i];
        delete[] _ptr;
        _ptr = tmp;
    }
    for (int i = 0; i < other._size; ++i)
        _ptr[_size++] = other._ptr[i];
}

template <typename T>
void DS::vector<T>::popBack() {
    if (_size > 0) --_size;
}

template <typename T>
void DS::vector<T>::popBack(int count) {
    while (_size > 0 && count-- > 0) --_size;
}

template <typename T>
void DS::vector<T>::pushFront(const T &val) {
    if (_size == _capacity) {
        if (!_capacity) {
            _capacity = 1;
            _size = 1;
            _ptr = new T[_capacity]{val};
            return;
        } else {
            _capacity *= 2;
            T *tmp = new T[_capacity];
            for (int i = _size - 1; i >= 0; --i)
                tmp[i + 1] = _ptr[i];
            ++_size;
            tmp[0] = val;
            delete[] _ptr;
            _ptr = tmp;
            return;
        }
    }
    for (int i = _size - 1; i >= 0; --i)
        _ptr[i + 1] = _ptr[i];
    ++_size;
    _ptr[0] = val;
}

template <typename T>
void DS::vector<T>::pushFront(const T &val, const int count) {
    if (count <= 0) return;
    if (_size + count > _capacity) {
        if (!_capacity) {
            _capacity = count;
            _size = count;
            _ptr = new T[count]{val};
            return;
        } else {
            _capacity = std::max(_capacity * 2, _size + count);
            T *tmp = new T[_capacity];
            for (int i = _size - 1; i >= 0; --i)
                tmp[i + count] = _ptr[i];
            for (int i = 0; i < count; ++i)
                tmp[i] = val;
            delete[] _ptr;
            _ptr = tmp;
            _size += count;
            return;
        }
    }
    for (int i = _size - 1; i >= 0; --i)
        _ptr[i + count] = _ptr[i];
    for (int i = 0; i < count; ++i)
        _ptr[i] = val;
    _size += count;
}

template <typename T>
void DS::vector<T>::pushFront(const DS::vector<T> &other) {
    if (this == &other) return;
    if (!_size) {
        *this = other;
        return;
    }
    const int n = other._size;
    if (!n) return;
    if (_size + n > _capacity) {
        _capacity = std::max(_size + n, _capacity * 2);
        T *tmp = new T[_capacity];
        for (int i = _size - 1; i >= 0; --i)
            tmp[i + n] = _ptr[i];
        for (int i = 0; i < n; ++i)
            tmp[i] = other._ptr[i];
        delete[] _ptr;
        _ptr = tmp;
        _size += n;
        return;
    }
    for (int i = _size - 1; i >= 0; --i)
        _ptr[i + n] = _ptr[i];
    for (int i = 0; i < n; ++i)
        _ptr[i] = other._ptr[i];
    _size += n;
}

template <typename T>
void DS::vector<T>::popFront() {
    if (_size == 0) return;
    for (int i = 1; i < _size; ++i)
        _ptr[i - 1] = _ptr[i];
    --_size;
}

template <typename T>
void DS::vector<T>::popFront(const int count) {
    if (count <= 0) return;
    if (count >= _size) _size = 0;
    else {
        for (int i = count; i < _size; ++i)
            _ptr[i - count] = _ptr[i];
        _size -= count;
    }
}

template <typename T>
void DS::vector<T>::insert(const int index, const T &val) {
    if (index < 0 || index > _size) throw std::out_of_range("");
    if (index == _size) {
        pushBack(val);
        return;
    }
    if (!index) {
        pushFront(val);
        return;
    }
    if (_size == _capacity) {
        _capacity *= 2;
        T *tmp = new T[_capacity];
        for (int i = 0; i < index; ++i)
            tmp[i] = _ptr[i];
        tmp[index] = val;
        for (int i = index; i < _size; ++i)
            tmp[i + 1] = _ptr[i];
        delete[] _ptr;
        _ptr = tmp;
    } else {
        for (int i = _size - 1; i >= index; --i)
            _ptr[i + 1] = _ptr[i];
        _ptr[index] = val;
    }
    ++_size;
}

template <typename T>
void DS::vector<T>::insert(const int index, const T &val, const int count) {
    if (index < 0 || index > _size) throw std::out_of_range("");
    if (count <= 0) return;
    if (index == _size) {
        pushBack(val, count);
        return;
    }
    if (!index) {
        pushFront(val, count);
        return;
    }
    if (_size + count > _capacity) {
        _capacity = std::max(_capacity * 2, _size + count);
        T *tmp = new T[_capacity];
        for (int i = 0; i < index; ++i)
            tmp[i] = _ptr[i];
        for (int i = 0; i < count; ++i)
            tmp[index + i] = val;
        for (int i = index; i < _size; ++i)
            tmp[i + count] = _ptr[i];
        delete[] _ptr;
        _ptr = tmp;
    } else {
        for (int i = _size - 1; i >= index; --i)
            _ptr[i + count] = _ptr[i];
        for (int i = 0; i < count; ++i)
            _ptr[index + i] = val;
    }
    _size += count;
}

template <typename T>
void DS::vector<T>::insert(const int index, const DS::vector<T> &other) {
    if (index < 0 || index > _size) throw std::out_of_range("");
    if (this == &other) return;
    if (!index) {
        pushFront(other);
        return;
    }
    if (index == _size) {
        pushBack(other);
        return;
    }
    const int n = other._size;
    if (!n) return;
    if (_size + n > _capacity) {
        _capacity = std::max(_capacity * 2, _size + n);
        T *tmp = new T[_capacity];
        for (int i = 0; i < index; ++i)
            tmp[i] = _ptr[i];
        for (int i = 0; i < n; ++i)
            tmp[index + i] = other._ptr[i];
        for (int i = index; i < _size; ++i)
            tmp[i + n] = _ptr[i];
        delete[] _ptr;
        _ptr = tmp;
    } else {
        for (int i = _size - 1; i >= index; --i)
            _ptr[i + n] = _ptr[i];
        for (int i = 0; i < n; ++i)
            _ptr[index + i] = other._ptr[i];
    }
    _size += n;
}

template <typename T>
void DS::vector<T>::remove(const int index) {
    if (index < 0 || index >= _size) throw std::out_of_range("");
    for (int i = index + 1; i < _size; ++i)
        _ptr[i - 1] = _ptr[i];
    --_size;
}

template <typename T>
void DS::vector<T>::remove(const int index, const int count) {
    if (index < 0 || index >= _size) throw std::out_of_range("");
    if (count <= 0) return;
    if (index + count >= _size) {
        _size = index;
    } else {
        for (int i = index + count; i < _size; ++i)
            _ptr[i - count] = _ptr[i];
        _size -= count;
    }
}

template <typename T>
void DS::vector<T>::clear() {
    delete[] _ptr;
    _ptr = nullptr;
    _capacity = 0;
    _size = 0;
}

template <typename T>
void DS::vector<T>::shrinkToFit() {
    if (_capacity > _size) {
        _capacity = _size;
        T *tmp = _capacity ? new T[_capacity] : nullptr;
        for (int i = 0; i < _size; ++i)
            tmp[i] = _ptr[i];
        delete[] _ptr;
        _ptr = tmp;
    }
}

template <typename T>
int DS::vector<T>::size() const {
    return _size;
}

template <typename T>
int DS::vector<T>::capacity() const {
    return _capacity;
}

template <typename T>
bool DS::vector<T>::empty() const {
    return !_size;
}

template <typename T>
T &DS::vector<T>::front() {
    if (_size == 0) throw std::out_of_range("front() on empty vector");
    return _ptr[0];
}

template <typename T>
T &DS::vector<T>::back() {
    if (_size == 0) throw std::out_of_range("back() on empty vector");
    return _ptr[_size - 1];
}

#endif //VECTOR_TPP