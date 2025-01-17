CXX = g++
Wall: CFLAGS := $(CFLAGS) -Wall

INCL = src/include
INT_INCL = src/internal_include

demo: test test/run

test/run: test/run.o test/matrix.o
	$(CXX) $^ -o $@

test:
	mkdir -p test

test/run.o: demo/main.cpp
	$(CXX) -I $(INCL) -c $< -o $@

test/matrix.o: src/matrix/matrix.cpp
	$(CXX) -I $(INT_INCL) -c $< -o $@

run: demo
	test/run

clean:
	rm -f test/*

Wall: demo
	echo $(CFLAGS)
