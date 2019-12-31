playfair: main.o playfair.o
	g++ -Wall -g main.o playfair.o -o playfair

main.o: main.cpp playfair.h
	g++ -Wall -c main.cpp

playfair.o: playfair.cpp playfair.h
	g++ -Wall -c playfair.cpp