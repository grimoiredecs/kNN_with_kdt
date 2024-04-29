all: main

main: main.cpp kDTree.cpp Dataset.o
    clang++ -o main main.cpp kDTree.cpp Dataset.o -I . -std=c++11

clean:
    rm -f main