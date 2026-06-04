#ifndef TREENODE_TPP
#define TREENODE_TPP

namespace DS {
    template <typename T>
    struct TreeNode {
        T val;
        TreeNode *left;
        TreeNode *right;
        TreeNode *p;
        int height;
        explicit TreeNode(const T &);
        TreeNode(const TreeNode &) = delete;
        TreeNode(TreeNode &&) noexcept = delete;
        TreeNode &operator=(const TreeNode &) = delete;
        TreeNode &operator=(TreeNode &&) noexcept = delete;
    };
}

#include "TreeNode.cpp"

#endif //TREENODE_TPP
