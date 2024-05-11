#include "Dataset.hpp"

int main()
{
    Dataset dataset;
    dataset.loadFromCSV("data.csv");
    dataset.printHead();
    dataset.printTail();
    return 0;
}