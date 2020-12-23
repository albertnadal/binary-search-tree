GXX=g++
EXEC=bst

all:
	$(GXX) -O3 -std=c++14 main.cpp -o $(EXEC)

clean:
	rm -f $(EXEC)
