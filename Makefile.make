TestFile: main.o sdisk.o filesys.o block.o
	g++ main.o sdisk.o filesys.o block.o -o TestFile
sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp
filesys.o: filesys.cpp
	g++ -c filesys.cpp
main.o: main.cpp
	g++ -c main.cpp
block.o: block.cpp
	g++ -c block.cpp
clean:
	rm *.o
