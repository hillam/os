PROGRAM = matrices
FILES = main.cpp Matrix.cpp FileReader.cpp StringFunctions.cpp

all: run
run: zip
zip: build
build: clean

run:
	./create.o
	./$(PROGRAM).o

zip:
	rm -f $(PROGRAM).zip
	zip $(PROGRAM).zip *.cpp *.h makefile

build:
	g++ -pthread -std=c++11 $(FILES) -o $(PROGRAM).o
	g++ -std=c++11 create.cpp -o create.o
    
clean:
	rm -f *.zip
	rm -f *.o
	rm -f *.matrix
