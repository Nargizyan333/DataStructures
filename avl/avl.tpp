#ifndef AVL_TPP
#define AVL_TPP

#include "TreeNode.tpp"

namespace DS {
    template <typename T>
    class avl {
    private:
        DS::TreeNode<T> *_root;
        DS::TreeNode<T> *copy(DS::TreeNode<T> *);
        DS::TreeNode<T> *search(DS::TreeNode<T> *, const T &) const;
        DS::TreeNode<T> *getMin(DS::TreeNode<T> *) const;
        DS::TreeNode<T> *getMax(DS::TreeNode<T> *) const;
        void clear(DS::TreeNode<T> *);
        void remove(DS::TreeNode<T> *);
        static int height(const DS::TreeNode<T> *);
        static void updateHeight(DS::TreeNode<T> *);
        [[nodiscard]] int getBF(const DS::TreeNode<T> *) const;
        void leftRotate(DS::TreeNode<T> *);
        void rightRotate(DS::TreeNode<T> *);
        void balance(DS::TreeNode<T> *);
    public:
        avl();
        avl(const DS::avl<T> &);
        avl(DS::avl<T> &&) noexcept;
        DS::avl<T> &operator=(const DS::avl<T> &);
        DS::avl<T> &operator=(DS::avl<T> &&) noexcept;
        ~avl();
        [[nodiscard]] bool search(const T &) const;
        void insert(const T &);
        void remove(const T &);
        [[nodiscard]] T getMin() const;
        [[nodiscard]] T getMax() const;
        [[nodiscard]] T getPredecessor(const T &) const;
        [[nodiscard]] T getSuccessor(const T &) const;
        [[nodiscard]] int getHeight() const;
    };
}

#include "avl.cpp"

#endif //AVL_TPP
