#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
kDTree::kDTree(int k)
{
    this->k = k;
    root = nullptr;
    cnt = 0;
}
void kDTree::clear(kDTreeNode *node)
{
    if (node == nullptr || node == NULL || !node)
    {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}
kDTree::~kDTree()
{
    clear(root);
}
// overload operator =
const kDTree &kDTree::operator=(const kDTree &other)
{
    if (this == &other)
    {
        return *this;
    }
    clear(root);
    k = other.k;
    root = other.root;
    return *this;
}
// copy constructor
kDTree::kDTree(const kDTree &other)
{
    k = other.k;
    root = other.root;
}

void kDTree::inorderRec(kDTreeNode *node) const
{
    if (node == nullptr || node == NULL || !node)
    {
        return;
    }
    inorderRec(node->left);

    cout << this->root->data[0];
    for (int i = 1; i < this->root->data.size(); i++)
    {
        cout << " " << this->root->data[i];
    }
    inorderRec(node->right);
}
void kDTree::inorderTraversal() const
{
    inorderRec(root);
}

void kDTree::preorderRec(kDTreeNode *node) const
{
    if (node == nullptr || node == NULL || !node)
    {
        return;
    }
    cout << this->root->data[0];
    for (int i = 1; i < this->root->data.size(); i++)
    {
        cout << " " << this->root->data[i];
    }
    preorderRec(node->left);
    preorderRec(node->right);
}
void kDTree::preorderTraversal() const
{
    preorderRec(root);
}

void kDTree::postorderRec(kDTreeNode *node) const
{
    if (node == nullptr || node == NULL || !node)
    {
        return;
    }
    postorderRec(node->left);
    postorderRec(node->right);
    cout << this->root->data[0];
    for (int i = 1; i < this->root->data.size(); i++)
    {
        cout << " " << this->root->data[i];
    }
}

void kDTree::postorderTraversal() const
{
    postorderRec(root);
}

int kDTree::heightRec(kDTreeNode *node) const
{
    if (node == nullptr || node == NULL || !node)
    {
        return 0;
    }
    int leftHeight = heightRec(node->left);
    int rightHeight = heightRec(node->right);
    return 1 + max(leftHeight, rightHeight);
}
int kDTree::height() const
{
    return heightRec(root);
}
int kDTree::nodeCount() const
{
    return this->cnt;
}
int kDTree::leafCountRec(kDTreeNode *node) const
{
    if (node == nullptr || node == NULL || !node)
    {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
        return 1;
    }
    return leafCountRec(node->left) + leafCountRec(node->right);
}
int kDTree::leafCount() const
{
    return leafCountRec(root);
}
