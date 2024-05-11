#include "main.hpp"
#include "kDTree.hpp"
#include <algorithm>

/* TODO: You can implement methods, functions that support your data structures here.
 * */
kDTree::kDTree(int k)
{
    this->k = k;
    root = nullptr;
}
kDTree::~kDTree()
{
    clear(root);
}

void kDTree::clear(kDTreeNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr; // Set the pointer to null after deletion (optional)
}

// overload operator =

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
    if (node == nullptr)
    {
        return;
    }
    inorderRec(node->left);
    for (int i = 0; i < node->data.size(); i++)
    {
        cout << node->data[i] << " ";
    }
    cout << endl;

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

                return;
            }
            cur = cur->left;
        }
        else
        {
            if (cur->right == nullptr || cur->right == NULL || !cur->right)
            {
                cur->right = new kDTreeNode(point);

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

    kDTreeNode *left = findMin(node->left, dim, depth + 1);
    kDTreeNode *right = findMin(node->right, dim, depth + 1);
    kDTreeNode *min = node;

    if (left != nullptr && left->data[cd] < min->data[cd])
        min = left;

    if (right != nullptr && right->data[cd] < min->data[cd])
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
            node->right = node->left;
            node->left = nullptr;
            node->right = removeRec(node->right, min->data, depth + 1);
            //   node->right = removeRec(node->left, min->data, depth + 1);
        }
        else
        {
            delete node;

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
        dim = (dim + 1) % (k - 1);
    }
    return false;
}
void kDTree::merge(vector<vector<int>> &points, vector<vector<int>> &temp, int leftStart, int mid, int rightEnd, int dim)
{
    int i = leftStart;
    int j = mid + 1;
    int k = leftStart;

    while (i <= mid && j <= rightEnd)
    {
        if (points[i][dim] <= points[j][dim])
        {
            temp[k] = points[i];
            i++;
        }
        else
        {
            temp[k] = points[j];
            j++;
        }
        k++;
    }

    while (i <= mid)
    {
        temp[k] = points[i];
        i++;
        k++;
    }

    while (j <= rightEnd)
    {
        temp[k] = points[j];
        j++;
        k++;
    }

    for (i = leftStart; i <= rightEnd; i++)
    {
        points[i] = temp[i];
    }
}

void kDTree::mergeSort(vector<vector<int>> &points, vector<vector<int>> &temp, int leftStart, int rightEnd, int dim)
{
    if (leftStart >= rightEnd)
    {
        return;
    }

    int mid = leftStart + (rightEnd - leftStart) / 2;
    mergeSort(points, temp, leftStart, mid, dim);
    mergeSort(points, temp, mid + 1, rightEnd, dim);
    merge(points, temp, leftStart, mid, rightEnd, dim);
}

kDTreeNode *kDTree::buildTreeRec(const vector<vector<int>> &points, int depth, int start, int end)
{

    if (start > end)
    {
        return nullptr;
    }
    int actual = depth % (this->k);
    if (points.size() == 1 || start == end)
    {
        return new kDTreeNode(points[start]);
    }
    if (points.size() == 0)
    {
        return nullptr;
    }
    vector<vector<int>> point(points.begin() + start, points.begin() + end + 1);
    vector<vector<int>> temp = point;
    mergeSort(point, temp, 0, point.size() - 1, actual);
    int median = (start + end) / 2; // out of bound
    if (start != 0)
    {
        median -= start;
    }
    kDTreeNode *node = new kDTreeNode(point[median]); /// it breaks here
    start = 0;
    end = point.size() - 1;
    median = (start + end) / 2;
    node->left = buildTreeRec(point, depth + 1, start, median - 1);
    node->right = buildTreeRec(point, depth + 1, median + 1, end);

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
    return static_cast<double>(sqrt(res));
}
// dfs

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

// dfs

kDTreeNode *kDTree::nearestNeighborRec(kDTreeNode *node, const vector<int> &queryPoint, int depth)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    double dist = distance(queryPoint, node->data);              // euclid disrance between the query point and the current node
    double diff = queryPoint[depth % k] - node->data[depth % k]; // intersection level
    kDTreeNode *near = diff <= 0 ? node->left : node->right;
    kDTreeNode *far = diff <= 0 ? node->right : node->left;

    kDTreeNode *nearest = nearestNeighborRec(near, queryPoint, depth + 1);
    if (nearest == nullptr || dist < distance(queryPoint, nearest->data))
    {
        nearest = node;
    }

    if (abs(diff) <= distance(queryPoint, nearest->data))
    {
        kDTreeNode *temp = nearestNeighborRec(far, queryPoint, depth + 1);
        if (temp != nullptr && distance(queryPoint, temp->data) < distance(queryPoint, nearest->data))
        {
            nearest = temp;
        }
    }

    return nearest;
}

void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *&best)
{
    kDTreeNode *tmp = nearestNeighborRec(root, target, 0);
    if (tmp == nullptr)
    {
        cout << "The tree is empty." << endl;
        return;
    }
    // Update best with the data from tmp
    best = new kDTreeNode(*tmp);

    cout << "Hello World";
    return;
}

int main()
{

    /// fix the merge function
    kDTree tree(2); //(5, 6), (2, 2), (7, 3), (2, 8), (8, 7), (8, 1), (9, 4), (3, 5) 8 elemetns
    vector<vector<int>> points = {{5, 6}, {2, 2}, {7, 3}, {2, 8}, {8, 7}, {8, 1}, {9, 4}, {3, 5}};
    kDTreeNode *best = nullptr;
    tree.buildTree(points);
    //   tree.inorderTraversal();
    //  tree.remove({7, 3});
    // tree.inorderTraversal();
    tree.nearestNeighbour({9, 3}, best);
    cout << "The nearest neighbour is: " << best->data[0] << " " << best->data[1] << endl;
    tree.remove({7, 3});
    cout << best->data[0] << " " << best->data[1] << endl;

    delete best;
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    return 0;
}