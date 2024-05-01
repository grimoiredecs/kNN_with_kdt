#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

// x = 0;   y = 1
struct kDTreeNode
{
    vector<int> data;
    kDTreeNode *left;

    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;
    int cnt;

public:
    kDTree(int k = 2);
    ~kDTree();
    kDTreeNode *findMedian(vector<vector<int>> &pointList, int l, int r, int dim);
    inline int lvlRec(const kDTreeNode *node, const kDTreeNode *cur, int level);
    inline int lvl(kDTreeNode *node);
    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);
    void clear(kDTreeNode *node);
    void inorderRec(kDTreeNode *node) const;
    void inorderTraversal() const;
    void preorderRec(kDTreeNode *node) const;
    void preorderTraversal() const;
    void postorderRec(kDTreeNode *node) const;
    void postorderTraversal() const;
    int heightRec(kDTreeNode *node) const;
    int height() const;
    int nodeCountRec(kDTreeNode *node) const;
    int nodeCount() const;
    int leafCountRec(kDTreeNode *node) const;
    int leafCount() const;

    void insert(const vector<int> &point);
    vector<int> successor(const kDTreeNode *node);
    kDTreeNode *removeRec(kDTreeNode *node, const vector<int> &point, int depth);
    void remove(const vector<int> &point);
    kDTreeNode *findMin(kDTreeNode *node, int dim, int depth);
    bool search(const vector<int> &point);
    void mergesort(vector<vector<int>> &point, int dim);
    void mergesort(vector<vector<int>> &point, vector<vector<int>> &res, int l, int r, int dim);
    inline void merge(vector<vector<int>> &point, vector<vector<int>> &res, int l, int mid, int r, int dim);
    void buildTree(const vector<vector<int>> &pointList);
    void nearestNeighbour(const vector<int> &target, kDTreeNode *best);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);
    kDTreeNode *buildTreeRec(const vector<vector<int>> &pointList, int l, int r, int depth);
    inline double distance(const vector<int> &a, const vector<int> &b);
    inline void traversed(kDTreeNode *root, int k);
    kDTreeNode *neighborSearch(kDTreeNode *root, const vector<int> &target, int depth);
};

template <class T>
class Heap
{
protected:
    vector<T> elements;

public:
    Heap() {}
    ~Heap() {}

    void push(T item);
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();

private:
    void reheapUp(int position);
    void reheapDown(int position);
    void reheapDown(vector<T> &minHeap, int numberOfElements, int index);
    void reheapUp(vector<T> &minHeap, int numberOfElements, int index);
};
class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    int numClasses;
    kDTree *tree;

public:
    kNN(int k = 5);
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

// Please add more or modify as needed
