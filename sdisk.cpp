#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"filesys.h"
#include"sdisk.h"
#include"block.cpp"

using namespace std;

/*------Interface Implementation-------*/
Sdisk::Sdisk(string dn,int bn,int bs)
{
    /*
    diskName = dn;
    blocksize = bs;
    numberofblocks = bn;
    */
   this->diskName = dn;
   this->blocksize = bs;
   this->numberofblocks = bn;

   int numChar = blocksize*numberofblocks;//total number of blocks

    fstream infile;//file handle
    infile.open(diskName.c_str(), ios::in | ios::out);//file opened
    /*correct approach would enter if(!infile.good()), 
    then create disk, then if(infile.good()) confirms the disk exists*/
    if(!infile.good())
    {
        cout << "The disk " << diskName << " doesn't exist.\n";
        infile.close();
        ofstream infile;
        infile.open(diskName.c_str(), ios::out | ios::app);
        cout << "disk" << diskName << "now exists.\n";
        return;
    }

    if(infile.good())
    {
        cout << "disk " << diskName << " exists.\n";
        for(int i =0; i <numChar; i++)
        {
            infile << "#";
        }
        infile.close();
    }
}//we should have a software disk at this point

int Sdisk::getblocksize()
{
    return blocksize;
}//use this to access private data member from friend class

int Sdisk::getnumberofblocks()
{
    return numberofblocks;
}//use this to access private data member from friend class
int Sdisk::getblock(int blocknumber, string& buffer){
 //allocate blocknumber and store into buffer 
    ifstream infile;//file handle
    infile.open(diskName.c_str(), ios::in);

    infile.seekg(blocknumber*blocksize);

    for(int i =0; i < blocksize; i++)
    {
        buffer.push_back(infile.get());//read the character amount
    }
    return 1;
}

int Sdisk::putblock(int blocknumber, string buffer)
{
    ofstream outdisk;
    outdisk.open(diskName.c_str(), ios::in | ios::out);//add reading capabilities with ios::in
    int tNumChar = (blocknumber*blocksize);
    outdisk.seekp(tNumChar);

    outdisk.write(buffer.c_str(), buffer.size());

    outdisk.close();
    return 1;
}