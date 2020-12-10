TestFile: main.o sdisk.o filesys.o Shell.o Table.o
	g++ main.o sdisk.o filesys.o Shell.o Table.o -o test
Table.o: Table.cpp
	g++ -c Table.cpp
Shell.o: Shell.cpp
	g++ -c Shell.cpp
sdisk.o: sdisk.cpp
	g++ -c sdisk.cpp
filesys.o: filesys.cpp
	g++ -c filesys.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o
