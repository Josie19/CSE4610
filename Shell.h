#ifndef SHELL_H
#define SHELL_H
#include "filesys.h"

class Shell : public Filesys
{
	public:
		Shell(std::string filename, int blocksize, int numberofblocks);
		int dir(); //list all files
		int add(std::string file);
		int del(std::string file);
		int type(std::string file);
		int copy(std::string file1, std::string file2); 
        int clobber(std::string file);
};

#endif