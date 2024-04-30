#include "main.hpp"
#include "Dataset.hpp"
#include "kDTree.hpp"

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
