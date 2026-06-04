#ifndef VECTOR_TPP
#define VECTOR_TPP

namespace DS {
    template <typename T>
    class vector {
    private:
        T *_ptr;
        int _capacity;
        int _size;
    public:
        vector();
        vector(int, const T &);
        vector(const DS::vector<T> &);
        vector(DS::vector<T> &&) noexcept;
        DS::vector<T> &operator=(const DS::vector<T> &);
        DS::vector<T> &operator=(DS::vector<T> &&) noexcept;
        T &operator[](int);
        const T &operator[](int) const;
        ~vector();
        void pushBack(const T &);
        void pushBack(const T &, int);
        void pushBack(const DS::vector<T> &);
        void popBack();
        void popBack(int);
        void pushFront(const T &);
        void pushFront(const T &, int);
        void pushFront(const DS::vector<T> &);
        void popFront();
        void popFront(int);
        void insert(int, const T &);
        void insert(int, const T &, int);
        void insert(int, const DS::vector<T> &);
        void remove(int);
        void remove(int, int);
        void clear();
        void shrinkToFit();
        [[nodiscard]] int size() const;
        [[nodiscard]] int capacity() const;
        [[nodiscard]] bool empty() const;
        T &front();
        T &back();
    };
}

#endif //VECTOR_TPP
