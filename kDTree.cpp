#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
kDTree::kDTree(int k)
{
    this->k = k;
    root = nullptr;
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
kDTreeNode *kDTree::copy(kDTreeNode *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    kDTreeNode *newNode = new kDTreeNode(*node);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
}

const kDTree &kDTree::operator=(const kDTree &other)
{
    if (this != &other)
    {
        clear(root); // delete current tree
        k = other.k;
        root = copy(other.root); // create a deep copy of other's tree
    }
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
int kDTree::nodeCountRec(kDTreeNode *node) const
{
    if (node == nullptr)
        return 0;
    return nodeCountRec(node->left) + nodeCountRec(node->right) + 1;
}
int kDTree::nodeCount() const
{
    return nodeCountRec(root);
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
    return static_cast<double>(res);
}
// dfs

kDTreeNode *kDTree::nearestNeighborRec(kDTreeNode *node, const vector<int> &queryPoint, int depth)
{ // depth == k
    if (node == nullptr)
    {
        return nullptr;
    }

    double dist = distance(queryPoint, node->data); // calcualte distance saved later when we traversed up
    double diff = queryPoint[depth % k] - node->data[depth % k];
    kDTreeNode *near = diff <= 0 ? node->left : node->right;
    kDTreeNode *far = diff <= 0 ? node->right : node->left;

    kDTreeNode *nearest = nearestNeighborRec(near, queryPoint, depth + 1);
    if (nearest == nullptr || dist < distance(queryPoint, nearest->data))
    {
        nearest = node;
    }

    if (abs(diff) < distance(queryPoint, nearest->data))
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
    best = nearestNeighborRec(root, target, 0);
    return;
}

template <typename T>
bool Heap<T>::isEmpty()
{
    bool res = this->elements.empty();
    return res;
}

template <typename T>
bool Heap<T>::contains(const T &item)
{
    for (auto i : this->elements)
    {
        if (i == item)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
T Heap<T>::peek()
{
    if (this->isEmpty())
    {
        return nullptr;
    }
    T ele = this->elements[0];
    return ele;
}

template <typename T>
int Heap<T>::size()
{
    return this->elements.size();
}

template <typename T>
void Heap<T>::reheapUp(int position)
{
    int parent = (position - 1) / 2;
    if (position > 0 && this->elements[position] < this->elements[parent])
    {
        swap(this->elements[position], this->elements[parent]);
        reheapUp(parent);
    }
}

template <typename T>
void Heap<T>::reheapDown(int position)
{
    int left = 2 * position + 1;
    int right = 2 * position + 2;
    int smallest = position;
    if (left < this->elements.size() && this->elements[left] < this->elements[position])
    {
        smallest = left;
    }
    if (right < this->elements.size() && this->elements[right] < this->elements[smallest])
    {
        smallest = right;
    }
    if (smallest != position)
    {
        swap(this->elements[position], this->elements[smallest]);
        reheapDown(smallest);
    }
}

template <typename T>
void Heap<T>::reheapDown(vector<T> &minHeap, int numberOfElements, int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    if (left < numberOfElements && minHeap[left] < minHeap[index])
    {
        smallest = left;
    }
    if (right < numberOfElements && minHeap[right] < minHeap[smallest])
    {
        smallest = right;
    }
    if (smallest != index)
    {
        swap(minHeap[index], minHeap[smallest]);
        reheapDown(minHeap, numberOfElements, smallest);
    }
}

template <typename T>
void Heap<T>::reheapUp(vector<T> &minHeap, int numberOfElements, int index)
{
    int parent = (index - 1) / 2;
    if (index > 0 && minHeap[index] < minHeap[parent])
    {
        swap(minHeap[index], minHeap[parent]);
        reheapUp(minHeap, numberOfElements, parent);
    }
}

template <typename T>
void Heap<T>::push(T item)
{
    this->elements.push_back(item);
    reHeapUp(this->elements.size() - 1);
}

void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList)
{
    kDTree tem(*this);
    kDTreeNode *node = new kDTreeNode(target);
    kDTreeNode *delNode = new kDTreeNode(target);
    int len = min(k, this->nodeCount());
    vector<kDTreeNode *> list;
    for (int i = 0; i < len; i++)
    {
        tem.nearestNeighbour(target, delNode);
        this->nearestNeighbour(delNode->data, node);
        vector<int> label = {node->data[784]};
        kDTreeNode *element = new kDTreeNode(label);
        list.push_back(element);
        tem.remove(delNode->data);
    }
    bestList = list;
}
void kNN::fit(Dataset &X_train, Dataset &y_train)
{
    this->X_train = &X_train;
    this->y_train = &y_train;
    int x_rows;
    int y_rows;
    int x_cols;
    int y_cols;
    X_train.getShape(x_rows, x_cols);
    y_train.getShape(y_rows, y_cols);

    this->numClasses = y_rows;

    vector<vector<int>> points;
    for (auto i : X_train.data)
    {
        vector<int> point;
        for (auto j : i)
        {
            point.push_back(j);
        }
        points.push_back(point);
    }
    tree = new kDTree(this->k);
    tree->buildTree(points);
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    int y_test_rows;
    int y_test_cols;
    y_test.getShape(y_test_rows, y_test_cols);
    int y_pred_rows;
    int y_pred_cols;
    y_pred.getShape(y_pred_rows, y_pred_cols);

    if (y_test_rows != y_pred_rows || y_test_cols != y_pred_cols)
    {
        return -1;
    }
    double correct = 0;
    for (auto i : y_test.data)
    {
        for (auto j : y_pred.data)
        {
            if (i == j)
            {
                correct++;
            }
        }
    }
    return static_cast<double>((correct) / y_test_rows);
}
