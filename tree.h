
// idfyanai@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include <queue>
#include <stack>

template<typename T>
struct TreeNode {
    T value;
    std::vector<TreeNode*> children;
    TreeNode(T val) : value(val) {}
};

template<typename T, size_t K = 2>
class Tree {
    TreeNode<T>* root;
public:
    Tree();
    ~Tree();

    void add_root(const T& value);
    void add_sub_node(TreeNode<T>* parent, const T& value);
    TreeNode<T>* get_root() const;

    class PreOrderIterator;
    class PostOrderIterator;
    class InOrderIterator;
    class BFSIterator;
    class DFSIterator;

    PreOrderIterator begin_pre_order();
    PreOrderIterator end_pre_order();
    PostOrderIterator begin_post_order();
    PostOrderIterator end_post_order();
    BFSIterator begin_bfs_scan();
    BFSIterator end_bfs_scan();
    DFSIterator begin_dfs_scan();
    DFSIterator end_dfs_scan();

    void myHeap();

private:
    void delete_tree(TreeNode<T>* node);
};

template<typename T, size_t K>
class Tree<T, K>::PreOrderIterator {
public:
    PreOrderIterator(TreeNode<T>* root);
    bool operator!=(const PreOrderIterator& other) const;
    TreeNode<T>& operator*() const;
    TreeNode<T>* operator->() const;
    PreOrderIterator& operator++();

private:
    std::stack<TreeNode<T>*> stack;
};

template<typename T, size_t K>
class Tree<T, K>::PostOrderIterator {
public:
    PostOrderIterator(TreeNode<T>* root);
    bool operator!=(const PostOrderIterator& other) const;
    TreeNode<T>& operator*() const;
    TreeNode<T>* operator->() const;
    PostOrderIterator& operator++();

private:
    void push_children(TreeNode<T>* node);
    std::stack<TreeNode<T>*> stack;
    std::stack<TreeNode<T>*> output;
};

template<typename T, size_t K>
class Tree<T, K>::BFSIterator {
public:
    BFSIterator(TreeNode<T>* root);
    bool operator!=(const BFSIterator& other) const;
    TreeNode<T>& operator*() const;
    TreeNode<T>* operator->() const;
    BFSIterator& operator++();

private:
    std::queue<TreeNode<T>*> queue;
};

template<typename T, size_t K>
class Tree<T, K>::DFSIterator {
public:
    DFSIterator(TreeNode<T>* root);
    bool operator!=(const DFSIterator& other) const;
    TreeNode<T>& operator*() const;
    TreeNode<T>* operator->() const;
    DFSIterator& operator++();

private:
    std::stack<TreeNode<T>*> stack;
};

#endif
