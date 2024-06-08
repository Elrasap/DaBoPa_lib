CXX = g++
Wall: CFLAGS := $(CFLAGS) -Wall

demo: test test/run

test/run: test/run.o test/matrix.o
	$(CXX) $^ -o $@

test:
	mkdir -p test

test/run.o:
	$(CXX) -c src/frontend/main.cpp -o $@

test/matrix.o:
	$(CXX) -c src/matrix/matrix.cpp -o $@

run: demo
	test/run

clean:
	rm test/*

Wall: demo
	echo $(CFLAGS)
