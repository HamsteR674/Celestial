all: cel 

cel: cel.o
	g++ cel.o -o cel
	rm -rf *.o 

cel.o: cel.cpp 
	g++ -c cel.cpp 

clean: 
	rm -f *.o cel