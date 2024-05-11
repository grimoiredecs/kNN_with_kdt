CC = g++
CXXFLAGS = -std=c++11 -I .

SRCS = main.cpp kDTree.cpp Dataset.o

all: main

main: $(SRCS)
    $(CC) $(CXXFLAGS) $^ -o $@

clean:
    rm -f main
