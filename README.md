# DataStructures

A header-only C++ library implementing common data structures as generic, reusable templates inside the `DS` namespace. Each structure is split into a `.hpp` declaration file and a `.tpp` implementation file, keeping interfaces clean and easy to read.

---

## Table of Contents

- [Structures](#structures)
    - [Vector](#vector)
    - [List](#list)
    - [AVL Tree](#avl-tree)
- [Project Structure](#project-structure)
- [Usage](#usage)
- [API Reference](#api-reference)
    - [DS::vector\<T\>](#dsvectort)
    - [DS::list\<T\>](#dslistt)
    - [DS::avl\<T\>](#dsavlt)

---

## Structures

### Vector

A dynamic array (`DS::vector<T>`) that grows automatically. Supports random access, insertion and removal at both ends or at arbitrary indices, bulk operations, and memory management utilities.

### List

A singly-linked list (`DS::list<T>`) with a `ListNode<T>` node type. Supports push/pop at both ends, bulk operations, and move semantics throughout.

### AVL Tree

A self-balancing binary search tree (`DS::avl<T>`) backed by `DS::TreeNode<T>`. Maintains O(log n) height at all times via left/right rotations. Supports search, insert, remove, min/max queries, predecessor/successor lookups, and height queries.

---

## Project Structure

```
DataStructures/
├── vector/
│   ├── vector.hpp       # Class declaration
│   └── vector.tpp       # Template implementation
├── list/
│   ├── list.hpp         # Class & ListNode declaration
│   └── list.tpp         # Template implementation
├── avl/
│   ├── avl.hpp          # Class declaration
│   ├── avl.tpp          # Template implementation
│   ├── TreeNode.hpp     # Node struct declaration
│   └── TreeNode.tpp     # Node template implementation
└── .gitignore
```

---

## Usage

Since the library is header-only, simply include the relevant `.hpp` file in your project. No build step is required.

```cpp
#include "vector/vector.hpp"
#include "list/list.hpp"
#include "avl/avl.hpp"

int main() {
    // Dynamic array
    DS::vector<int> v;
    v.pushBack(10);
    v.pushBack(20);
    v.insert(1, 15);       // v = [10, 15, 20]

    // Singly-linked list
    DS::list<std::string> l;
    l.pushBack("hello");
    l.pushFront("world");
    l.print();

    // Self-balancing BST
    DS::avl<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    bool found = tree.search(3);   // true
    int  minVal = tree.getMin();   // 3
    tree.remove(5);

    return 0;
}
```

Requires **C++17** or later (uses `[[nodiscard]]` attributes and structured bindings).

---

## API Reference

### `DS::vector<T>`

#### Constructors & Assignment

| Signature | Description |
|-----------|-------------|
| `vector()` | Default constructor — empty vector |
| `vector(int n, const T& val)` | Fill constructor — `n` copies of `val` |
| `vector(const vector<T>&)` | Copy constructor |
| `vector(vector<T>&&) noexcept` | Move constructor |
| `operator=(const vector<T>&)` | Copy assignment |
| `operator=(vector<T>&&) noexcept` | Move assignment |

#### Element Access

| Signature | Description |
|-----------|-------------|
| `T& operator[](int i)` | Access element at index `i` |
| `const T& operator[](int i) const` | Const access at index `i` |
| `T& front()` | Reference to the first element |
| `T& back()` | Reference to the last element |

#### Modifiers

| Signature | Description |
|-----------|-------------|
| `void pushBack(const T&)` | Append one element |
| `void pushBack(const T&, int n)` | Append `n` copies of an element |
| `void pushBack(const vector<T>&)` | Append all elements from another vector |
| `void popBack()` | Remove the last element |
| `void popBack(int n)` | Remove the last `n` elements |
| `void pushFront(const T&)` | Prepend one element |
| `void pushFront(const T&, int n)` | Prepend `n` copies of an element |
| `void pushFront(const vector<T>&)` | Prepend all elements from another vector |
| `void popFront()` | Remove the first element |
| `void popFront(int n)` | Remove the first `n` elements |
| `void insert(int i, const T&)` | Insert one element at index `i` |
| `void insert(int i, const T&, int n)` | Insert `n` copies at index `i` |
| `void insert(int i, const vector<T>&)` | Insert all elements of a vector at index `i` |
| `void remove(int i)` | Remove element at index `i` |
| `void remove(int i, int n)` | Remove `n` elements starting at index `i` |
| `void clear()` | Remove all elements |
| `void shrinkToFit()` | Release excess capacity |

#### Capacity

| Signature | Description |
|-----------|-------------|
| `int size() const` | Number of elements |
| `int capacity() const` | Allocated capacity |
| `bool empty() const` | `true` if size is 0 |

---

### `DS::list<T>`

#### `DS::ListNode<T>`

Each node stores a `T val` and a `ListNode<T>* next` pointer. Supports copy/move construction and assignment.

#### Constructors & Assignment

| Signature | Description |
|-----------|-------------|
| `list()` | Default constructor — empty list |
| `list(const list<T>&)` | Copy constructor |
| `list(list<T>&&) noexcept` | Move constructor |
| `operator=(const list<T>&)` | Copy assignment |
| `operator=(list<T>&&) noexcept` | Move assignment |

#### Modifiers

| Signature | Description |
|-----------|-------------|
| `void pushBack(T&&)` | Append via move |
| `void pushBack(const T&, int n = 1)` | Append `n` copies (default 1) |
| `void pushBack(const list<T>&)` | Append all elements from another list |
| `void popBack()` | Remove the last element |
| `void popBack(int n)` | Remove the last `n` elements |
| `void pushFront(T&&)` | Prepend via move |
| `void pushFront(const T&, int n = 1)` | Prepend `n` copies (default 1) |
| `void pushFront(const list<T>&)` | Prepend all elements from another list |
| `void popFront()` | Remove the first element |
| `void popFront(int n)` | Remove the first `n` elements |
| `void clear()` | Remove all nodes and free memory |

#### Capacity & Utilities

| Signature | Description |
|-----------|-------------|
| `int size() const` | Number of elements |
| `bool empty() const` | `true` if size is 0 |
| `void print() const` | Print list contents to stdout |

---

### `DS::avl<T>`

A self-balancing BST. `T` must support `<` and `==` (or equivalent comparison operators).

#### `DS::TreeNode<T>`

Internal node storing `T val`, pointers to `left`, `right`, and parent (`p`), and an `int height`. Copy/move construction and assignment are deleted — nodes are managed exclusively by the tree.

#### Constructors & Assignment

| Signature | Description |
|-----------|-------------|
| `avl()` | Default constructor — empty tree |
| `avl(const avl<T>&)` | Deep copy constructor |
| `avl(avl<T>&&) noexcept` | Move constructor |
| `operator=(const avl<T>&)` | Deep copy assignment |
| `operator=(avl<T>&&) noexcept` | Move assignment |

#### Queries

| Signature | Description |
|-----------|-------------|
| `bool search(const T&) const` | Returns `true` if the value exists in the tree |
| `T getMin() const` | Returns the minimum value |
| `T getMax() const` | Returns the maximum value |
| `T getPredecessor(const T&) const` | Returns the in-order predecessor of a value |
| `T getSuccessor(const T&) const` | Returns the in-order successor of a value |
| `int getHeight() const` | Returns the height of the tree |

#### Modifiers

| Signature | Description |
|-----------|-------------|
| `void insert(const T&)` | Insert a value and rebalance |
| `void remove(const T&)` | Remove a value and rebalance |
