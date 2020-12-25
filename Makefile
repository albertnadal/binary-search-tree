CXX=g++
CFLAGS=-std=c++14 -O3
LDFLAGS=
EXEC=bst

all: bst.o
	$(CXX) ${CFLAGS} $(LDFLAGS) main.cpp -o $(EXEC)

bst.o: bst.cpp
	$(CXX) -c $(CFLAGS) bst.cpp

clean:
	rm -f $(EXEC) *.o *.gch
