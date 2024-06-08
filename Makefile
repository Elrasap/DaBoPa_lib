CXX = g++
Wall: CFLAGS := $(CFLAGS) -Wall

INCL = src/include
INT_INCL = src/internal_include

demo: test test/run

test/run: test/run.o test/matrix.o
	$(CXX) $^ -o $@

test:
	mkdir -p test

test/run.o:
	$(CXX) -I $(INCL) -c demo/main.cpp -o $@

test/matrix.o:
	$(CXX) -I $(INT_INCL) -c src/matrix/matrix.cpp -o $@

run: demo
	test/run

clean:
	rm -f test/*

Wall: demo
	echo $(CFLAGS)
