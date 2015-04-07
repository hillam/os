all: run
run: zip
zip: build
build: clean

run:
	./Main.o

zip:
	rm -f ProducerConsumer.zip
	zip ProducerConsumer.zip *.cpp *.h *.java makefile

build:
	clear
	clear
	clear
	g++ -pthread -std=c++0x Main.cpp  Buffer.cpp -o Main.o
	javac Main.java
	
clean:
	rm -f *.zip
	rm -f *.o
	rm -f *.class
