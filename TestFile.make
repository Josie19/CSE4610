TestFile: main.o sdisk.o filesys.o
	g++ main.o sdisk.o filesys.o -o TestFile
sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp
filesys.o: filesys.cpp
	g++ -c filesys.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o
