#ifndef FILESYS_H
#define FILESYS_H

#include"sdisk.h"
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;


/*-----------Program Interface (Using Inheritance)------------*/
class Filesys: public Sdisk
{
public:
Filesys(string diskName, int numberofblocks, int blocksize);
int fsclose();
int fssynch();
int newfile(string file);
int rmfile(string file);
int getfirstblock(string file);
int addblock(string file, string block);
int delblock(string file, int blocknumber);
int readblock(string file, int blocknumber, string& buffer);
int writeblock(string file, int blocknumber, string buffer);
int nextblock(string file, int blocknumber);
int getrootsize();//accessor function
int getfatsize();//accessor functions
bool checkblock(string file, int blocknumber);
vector<string> ls();//returns the vector containing the filenames.
vector<string> block(string buffer, int b);
private:
int rootsize;           // maximum number of entries in ROOT
int fatsize;            // number of blocks occupied by FAT
vector<string> filename;   // filenames in ROOT
vector<int> firstblock; // firstblocks in ROOT
vector<int> fat;             // FAT
};

#endif
