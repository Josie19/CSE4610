#ifndef TABLE_H
#define TABLE_H

#include "filesys.h"
#include<fstream>
#include<sstream>
class Table : public Filesys
{
	public:
		Table(std::string diskname, int blocksize, int numberofblocks, std::string flatfile, std::string indexfile);
		int buildtable(std::string inputfile);
		int search(std::string value);
		std::string getfile() { return flatfile; }
		std::string getindexfile() { return indexfile; }
		int getnumberofblocks() { return numberofblocks; }
	private:
		std::string flatfile;
		std::string indexfile;
		Filesys filesystem;
		int numberofblocks;
		int indexsearch(std::string value);
};

#endif