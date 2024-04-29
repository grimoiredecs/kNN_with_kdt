CC = clang++
CFLAGS = -std=c++11 -I.

SRCS = main.cpp kDTree.cpp
OBJS = $(SRCS:.cpp=.o)

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)
