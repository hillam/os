PROGRAM = distance
FILES = master.cpp

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
	clear
	clear
	g++ -pthread -std=c++11 $(FILES) -o $(PROGRAM).o
    
clean:
	rm -f *.zip
	rm -f *.o