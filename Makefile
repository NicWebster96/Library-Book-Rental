CXX = g++ -std=c++17 -Wall

all: clean
	${CXX} checkoutMMap.cpp -o checkoutMMap_test
	./checkoutMMap_test

clean:
	rm -f checkoutMMap_test
