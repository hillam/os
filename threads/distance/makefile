PROGRAM = distance
FILES = master.cpp point_utils.cpp

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
	g++ $(FILES) -o $(PROGRAM).o
    
clean:
	rm -f *.zip
	rm -f *.o