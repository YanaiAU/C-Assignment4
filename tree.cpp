
// idfyanai@gmail.com

#include "tree.h"

template<typename T, size_t K>
Tree<T, K>::Tree() : root(nullptr) {}

template<typename T, size_t K>
Tree<T, K>::~Tree() {
    delete_tree(root);
}

template<typename T, size_t K>
void Tree<T, K>::add_root(const T& value) {
    if (root) delete_tree(root);
    root = new TreeNode<T>(value);
}

template<typename T, size_t K>
void Tree<T, K>::add_sub_node(TreeNode<T>* parent, const T& value) {
    if (parent->children.size() < K) {
        parent->children.push_back(new TreeNode<T>(value));
    } else {
        throw std::out_of_range("Maximum number of children reached");
    }
}

template<typename T, size_t K>
TreeNode<T>* Tree<T, K>::get_root() const {
    return root;
}

template<typename T, size_t K>
void Tree<T, K>::delete_tree(TreeNode<T>* node) {
    if (!node) return;
    for (auto child : node->children) {
        delete_tree(child);
    }
    delete node;
}

template<typename T, size_t K>
Tree<T, K>::PreOrderIterator::PreOrderIterator(TreeNode<T>* root) {
    if (root) stack.push(root);
}

template<typename T, size_t K>
bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !stack.empty() != !other.stack.empty();
}

template<typename T, size_t K>
TreeNode<T>& Tree<T, K>::PreOrderIterator::operator*() const {
    return *stack.top();
}

template<typename T, size_t K>
TreeNode<T>* Tree<T, K>::PreOrderIterator::operator->() const {
    return stack.top();
}

template<typename T, size_t K>
typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
    TreeNode<T>* node = stack.top();
    stack.pop();
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
        stack.push(*it);
    }
    return *this;
}

template<typename T, size_t K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_pre_order() {
    return PreOrderIterator(root);
}

template<typename T, size_t K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_pre_order() {
    return PreOrderIterator(nullptr);
}

template<typename T, size_t K>
Tree<T, K>::PostOrderIterator::PostOrderIterator(TreeNode<T>* root) {
    if (root) push_children(root);
}

template<typename T, size_t K>
bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !output.empty() != !other.output.empty();
}

template<typename T, size_t K>
TreeNode<T>& Tree<T, K>::PostOrderIterator::operator*() const {
    return *output.top();
}

template<typename T, size_t K>
TreeNode<T>* Tree<T, K>::PostOrderIterator::operator->() const {
    return output.top();
}

template<typename T, size_t K>
typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
    output.pop();
    return *this;
}

template<typename T, size_t K>
void Tree<T, K>::PostOrderIterator::push_children(TreeNode<T>* node) {
    stack.push(node);
    while (!stack.empty()) {
        TreeNode<T>* curr = stack.top();
        stack.pop();
        output.push(curr);
        for (auto child : curr->children) {
            stack.push(child);
        }
    }
}

template<typename T, size_t K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_post_order() {
    return PostOrderIterator(root);
}

template<typename T, size_t K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_post_order() {
    return PostOrderIterator(nullptr);
}

template<typename T, size_t K>
Tree<T, K>::BFSIterator::BFSIterator(TreeNode<T>* root) {
    if (root) queue.push(root);
}

template<typename T, size_t K>
bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) const {
    return !queue.empty() != !other.queue.empty();
}

template<typename T, size_t K>
TreeNode<T>& Tree<T, K>::BFSIterator::operator*() const {
    return *queue.front();
}

template<typename T, size_t K>
TreeNode<T>* Tree<T, K>::BFSIterator::operator->() const {
    return queue.front();
}

template<typename T, size_t K>
typename Tree<T, K>::BFSIterator& Tree<T, K>::BFSIterator::operator++() {
    TreeNode<T>* node = queue.front();
    queue.pop();
    for (auto child : node->children) {
        queue.push(child);
    }
    return *this;
}

template<typename T, size_t K>
typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs_scan() {
    return BFSIterator(root);
}

template<typename T, size_t K>
typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs_scan() {
    return BFSIterator(nullptr);
}

template<typename T, size_t K>
Tree<T, K>::DFSIterator::DFSIterator(TreeNode<T>* root) {
    if (root) stack.push(root);
}

template<typename T, size_t K>
bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator& other) const {
    return !stack.empty() != !other.stack.empty();
}

template<typename T, size_t K>
TreeNode<T>& Tree<T, K>::DFSIterator::operator*() const {
    return *stack.top();
}

template<typename T, size_t K>
TreeNode<T>* Tree<T, K>::DFSIterator::operator->() const {
    return stack.top();
}

template<typename T, size_t K>
typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
    TreeNode<T>* node = stack.top();
    stack.pop();
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
        stack.push(*it);
    }
    return *this;
}

template<typename T, size_t K>
typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs_scan() {
    return DFSIterator(root);
}

template<typename T, size_t K>
typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs_scan() {
    return DFSIterator(nullptr);
}

template<typename T, size_t K>
void Tree<T, K>::myHeap() {
    if (!root) return;

    std::priority_queue<T, std::vector<T>, std::greater<T>> minHeap;
    DFSIterator it = begin_dfs_scan();
    DFSIterator end = end_dfs_scan();

    for (; it != end; ++it) {
        minHeap.push((*it).value);
    }

    std::queue<TreeNode<T>*> queue;
    queue.push(root);
    while (!queue.empty() && !minHeap.empty()) {
        TreeNode<T>* node = queue.front();
        queue.pop();
        node->value = minHeap.top();
        minHeap.pop();
        for (auto child : node->children) {
            queue.push(child);
        }
    }
}

template class Tree<int, 3>;
template class Tree<std::string, 3>;

template class Tree<int, 4>;
template class Tree<std::string, 4>;
