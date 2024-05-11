#include "Dataset.hpp"

Dataset::Dataset()
{
}

bool Dataset::loadFromCSV(const char *fileName)
{
    ifstream file(fileName);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            istringstream ss(line);
            string token;
            list<int> row;
            while (getline(ss, token, ','))
            {
                row.push_back(stoi(token));
            }
            data.push_back(row);
        }
        file.close();
        return true;
    }
    return false;
}
Dataset::~Dataset()
{
    cout << "Destructor called" << endl;
}

void Dataset::printHead(int nRows, int nCols) const
{
    int i = 0;
    for (auto row : data)
    {
        if (i >= nRows)
            break;
        int j = 0;
        for (auto col : row)
        {
            if (j >= nCols)
                break;
            cout << col << " ";
            j++;
        }
        cout << endl;
        i++;
    }
}

void Dataset::printTail(int nRows, int nCols) const
{
    int i = 0;
    for (auto it = data.rbegin(); it != data.rend(); it++)
    {
        if (i >= nRows)
            break;
        int j = 0;
        for (auto col : *it)
        {
            if (j >= nCols)
                break;
            cout << col << " ";
            j++;
        }
        cout << endl;
        i++;
    }
}
