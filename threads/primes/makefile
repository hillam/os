PROGRAM = primes

all: run
run: zip
zip: build
build: clean

run:
	./$(PROGRAM).o

zip:
	rm -f $(PROGRAM).zip
	zip $(PROGRAM).zip *.cpp *.h makefile

build:
	g++ -pthread -std=c++11 main.cpp -o $(PROGRAM).o
    
clean:
	rm -f *.zip
	rm -f *.o
