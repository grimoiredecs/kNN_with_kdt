#include "main.hpp"
#include "kDTree.hpp"
#include <algorithm>

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
inline int kDTree::lvlRec(const kDTreeNode *node, const kDTreeNode *cur, int level)
{
    if (node == nullptr || node == NULL || !node)
    {
        return -1;
    }
    if (node == cur)
    {
        return level;
    }
    int left = lvlRec(node->left, cur, level + 1);
    if (left != 0)
    {
        return left;
    }
    return lvlRec(node->right, cur, level + 1);
}
inline int kDTree::lvl(kDTreeNode *node)
{
    return lvlRec(root, node, 0);
}

void kDTree::inorderRec(kDTreeNode *node) const
{
    if (node == nullptr || node == NULL || !node)
    {
        return;
    }
    inorderRec(node->left);

    cout << this->root->data[0];
    for (int i = 0; i < this->root->data.size() - 3; i++)
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
    // cout << this->root->data[0];
    for (int i = 0; i < this->root->data.size(); i++)
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

void kDTree::insert(const vector<int> &point)
{
    if (root == nullptr || root == NULL || !root)
    {
        root = new kDTreeNode(point);
        cnt++;
        return;
    }
    kDTreeNode *cur = root;
    int dim = 0;
    while (true)
    {
        if (point[dim] < cur->data[dim])
        {
            if (cur->left == nullptr || cur->left == NULL || !cur->left)
            {
                cur->left = new kDTreeNode(point);
                cnt++;
                return;
            }
            cur = cur->left;
        }
        else
        {
            if (cur->right == nullptr || cur->right == NULL || !cur->right)
            {
                cur->right = new kDTreeNode(point);
                cnt++;
                return;
            }
            cur = cur->right;
        }
        dim = (dim + 1) % k;
    }
}

// dim = alpha, the dimension of the node to be deleted
// depth is the depth of the node to be replacement
/*
If we are at a node split by α, the target will be in the left subtree. If the left subtree is
NULL, simply return the current node. Otherwise, continue recursively to the bottom of
the left subtree.
*/
kDTreeNode *kDTree::findMin(kDTreeNode *node, int dim, int depth)
{
    if (node == nullptr)
        return nullptr;
    int cd = depth % k;
    if (cd == dim)
    {
        if (node->left == nullptr)
            return node;
        return findMin(node->left, dim, depth + 1);
    }
    kDTreeNode *left = findMin(node->left, dim, depth++);
    kDTreeNode *right = findMin(node->right, dim, depth++);
    kDTreeNode *min = node;
    if (min->data[cd] > left->data[cd])
        min = left;
    else if (min->data[cd] > right->data[cd])
        min = right;

    return min;
}

// depth should be dimension of the to-be-deleted node
kDTreeNode *kDTree::removeRec(kDTreeNode *node, const vector<int> &point, int depth)
{
    if (node == nullptr)
        return nullptr;
    int cd = depth % k;
    if (node->data == point)
    {
        if (node->right != nullptr)
        {
            kDTreeNode *min = findMin(node->right, cd, depth + 1);
            node->data = min->data;
            node->right = removeRec(node->right, min->data, depth + 1);
        }
        else if (node->left != nullptr)
        {
            kDTreeNode *min = findMin(node->left, cd, depth + 1);
            node->data = min->data;
            root->right = root->left;
            root->left = nullptr;
            root->right = removeRec(root->right, min->data, depth + 1);
            //   node->right = removeRec(node->left, min->data, depth + 1);
        }
        else
        {
            delete node;
            cnt--;
            return nullptr;
        }
    }
    else
    {
        if (node->data[cd] > point[cd])
            node->left = removeRec(node->left, point, depth + 1);
        else
            node->right = removeRec(node->right, point, depth + 1);
    }
    return node;
}

void kDTree::remove(const vector<int> &point)
{
    root = removeRec(root, point, 0);
}

bool kDTree::search(const vector<int> &point)
{
    kDTreeNode *cur = root;
    int dim = 0;
    while (true)
    {
        if (cur == nullptr || cur == NULL || !cur)
        {
            return false;
        }
        if (cur->data == point)
        {
            return true;
        }
        if (point[dim] < cur->data[dim])
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
        dim = (dim + 1) % k;
    }
    return false;
}
void kDTree::mergesort(vector<vector<int>> &point, int dim)
{
    vector<vector<int>> res(point.size(), vector<int>(k));
    mergesort(point, res, 0, point.size() - 1, dim);
    point = res;
}
void kDTree::mergesort(vector<vector<int>> &point, vector<vector<int>> &res, int l, int r, int dim)
{
    if (l >= r)
    {
        return;
    }
    int mid = (l + r) / 2;
    mergesort(point, res, l, mid, dim);
    mergesort(point, res, mid + 1, r, dim);
    merge(point, res, l, mid, r, dim);
}
void kDTree::merge(vector<vector<int>> &point, vector<vector<int>> &res, int l, int mid, int r, int dim)
{

    int lend = mid - 1;
    int tmp = l;
    int num = r - l + 1;
    while (l <= lend && mid <= r)
        if (point[l][dim] < point[mid][dim])
            res[tmp++] = std::move(point[l++]);
        else
            res[tmp++] = std::move(point[mid++]);
    while (l <= lend)
        res[tmp++] = std::move(point[l++]);
    while (mid <= r)
        res[tmp++] = std::move(point[mid++]);
    for (int i = 0; i < num; i++, --r)
        point[r] = std::move(res[r]);
}
kDTreeNode *kDTree::buildTreeRec(const vector<vector<int>> &points, int depth, int start, int end)
{
    if (start >= end)
    {
        return nullptr;
    }
    vector<vector<int>> point(points.begin() + start, points.begin() + end + 1);
    mergesort(point, depth % k);
    int median = ceil((start + end) / 2);
    kDTreeNode *node = new kDTreeNode(point[median]);
    node->left = buildTreeRec(points, depth + 1, start, median - 1);
    node->right = buildTreeRec(points, depth + 1, median + 1, end);
    return node;
}

void kDTree::buildTree(const vector<vector<int>> &points)
{
    root = buildTreeRec(points, 0, 0, points.size() - 1);
}
inline double kDTree::distance(const vector<int> &a, const vector<int> &b)
{
    double res = 0;
    for (int i = 0; i < a.size(); i++)
    {
        res += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return static_cast<double>(res);
}
// dfs

kDTreeNode *kDTree::neighborSearch(kDTreeNode *root, const vector<int> &target, int depth)
{

    int dim = depth % this->k;
    kDTreeNode *tmp = root;
    kDTreeNode *min = root;
    bool flag = false;
    if (root->left == nullptr && root->right == nullptr)
    {
        return root;
    }
    if (root->left != nullptr && root->data[dim] > target[dim])
    {
        flag = true;
        min = neighborSearch(root->left, target, depth + 1);
    }
    else if (root->right != nullptr && root->data[dim] <= target[dim])
    {
        flag = false;
        min = neighborSearch(root->right, target, depth + 1);
    }
    else
    {
        double mindis = distance(min->data, target);
        double rootdis = distance(root->data, target);
        double r = 0;
        r = (root->data[dim] - target[dim]);

        if (rootdis < mindis)
        {
            min = root;
            mindis = rootdis;
        }
        if (r <= rootdis)
        {
            if (root->left != nullptr && flag == true)
            {
                min = neighborSearch(root->left, target, depth + 1);
            }
            if (root->right != nullptr && flag == false)
            {
                min = neighborSearch(root->right, target, depth + 1);
            }
        }
        return min;
    }
}

void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *best)
{
    best = neighborSearch(root, target, 0);
    return;
}

inline void merge(vector<vector<int>> &point, vector<vector<int>> &res, int l, int mid, int r, int dim)
{

    int lend = mid - 1;
    int tmp = l;
    int num = r - l + 1;
    while (l <= lend && mid <= r)
        if (point[l][dim] < point[mid][dim])
            res[tmp++] = std::move(point[l++]);
        else
            res[tmp++] = std::move(point[mid++]);
    while (l <= lend)
        res[tmp++] = std::move(point[l++]);
    while (mid <= r)
        res[tmp++] = std::move(point[mid++]);
    for (int i = 0; i < num; i++, --r)
        point[r] = std::move(res[r]);
}

void mergesort(vector<vector<int>> &point, vector<vector<int>> &res, int l, int r, int dim)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        mergesort(point, res, l, mid, dim);
        mergesort(point, res, mid + 1, r, dim);
        merge(point, res, l, mid + 1, r, dim); // Fixed the argument list for the merge function
    }
}
void mergesort(vector<vector<int>> &point)
{
    vector<vector<int>> res(point.size(), vector<int>(2, 0));
    mergesort(point, res, 0, point.size() - 1, 0);
}
void inorderRec(kDTreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorderRec(root->left);
    for (int i = 0; i < root->data.size() - 2; i++)
    {
        cout << " (" << root->data[i] << root->data[i + 1] << ")";
    }
    inorderRec(root->right);
}

int main()
{

    /// fix the merge function
    kDTree tree; //(5, 6), (2, 2), (7, 3), (2, 8), (8, 7), (8, 1), (9, 4), (3, 5)
    vector<vector<int>> points = {{5, 6}, {2, 2}, {7, 3}, {2, 8}, {8, 7}, {8, 1}, {9, 4}, {3, 5}};
    tree.buildTree(points);
    tree.inorderTraversal();

    return 0;
}