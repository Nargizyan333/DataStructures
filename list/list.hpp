#ifndef LIST_HPP
#define LIST_HPP

namespace DS {
    template <typename T>
    struct ListNode {
        ListNode();
        explicit ListNode(const T &);
        ListNode(const T &, ListNode<T> *);
        ListNode(const ListNode<T> &);
        ListNode(ListNode<T> &&) noexcept;
        ListNode<T> &operator=(const ListNode<T> &);
        ListNode<T> &operator=(ListNode<T> &&) noexcept;
        T val;
        ListNode *next;
    };

    template <typename T>
    class list {
    private:
        int _size;
        ListNode<T> *_head;
        ListNode<T> *_tail;
    public:
        list();
        list(const list<T> &);
        list(list<T> &&) noexcept;
        list<T> &operator=(const list<T> &);
        list<T> &operator=(list<T> &&) noexcept;
        void clear();
        ~list();
        [[nodiscard]] int size() const;
        [[nodiscard]] bool empty() const;
        void pushBack(T &&);
        void pushBack(const T &, int = 1);
        void pushBack(const list<T> &);
        void popBack();
        void popBack(int);
        void pushFront(T &&);
        void pushFront(const T &, int = 1);
        void pushFront(const list<T> &);
        void popFront();
        void popFront(int);
        void print() const;
    };
}

#include "list.tpp"

#endif //LIST_HPP
