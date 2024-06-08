CXX = g++
Wall: CFLAGS := $(CFLAGS) -Wall

test/run: test/run.o test/matrix.o
	$(CXX) $^ -o $@

test/run.o:
	$(CXX) -c src/frontend/main.cpp -o $@

test/matrix.o:
	$(CXX) -c src/matrix/matrix.cpp -o $@

run: test/run
	test/run

clean:
	rm test/*

Wall: test/run
	echo $(CFLAGS)
