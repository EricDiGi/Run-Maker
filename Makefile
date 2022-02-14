CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

TEST_BINARIES = test/test-1-road test/test-2-route test/test-3-triangle test/test-4-reader test/test-5-path-selection

SRC_BINARIES = road-graph.o road.o route.o file-reader.o

main: main.cpp $(SRC_BINARIES)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY:
clean:
	rm -rf *.dSYM
	rm -rf test/*.dSYM
	$(RM) *.o *.gc* $(TEST_BINARIES) core main test/catch.o

test-all: test-1-road test-2-route test-3-triangle test-4-reader test-5-path-selection

test-1-road: test/catch.o test/test-1-road.cpp road.o
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-2-route: test/catch.o test/test-2-route.cpp route.o road.o
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-3-triangle: test/catch.o test/test-3-triangle.cpp $(SRC_BINARIES)
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-4-reader: test/catch.o test/test-4-reader.cpp $(SRC_BINARIES)
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success

test-5-path-selection: test/catch.o test/test-5-path-selection.cpp $(SRC_BINARIES)
	$(CXX) $(CXXFLAGS) -o test/$@ $^
	test/$@ --success
