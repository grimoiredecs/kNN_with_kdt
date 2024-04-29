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
    void mergesort(vector<vector<int>> &pointList, int l, int r, int dim);
    kDTreeNode *findMedian(vector<vector<int>> &pointList, int l, int r, int dim);
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
    void remove(const vector<int> &point);
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    void nearestNeighbour(const vector<int> &target, kDTreeNode *best);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);
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