CXX = g++ -std=c++17 -Wall

all: clean
	${CXX} checkoutHash.cpp -o checkout_test
	./checkout_test

clean:
	rm -f checkout_test
