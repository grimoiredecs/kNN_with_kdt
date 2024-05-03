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
