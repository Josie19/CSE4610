#ifndef SDISK_H
#define SDISK_H

#include<string>
#include<sstream>
#include<vector>

using namespace std;
/*
Simulating the inner workings of a SSD or Hard disk drive (HDD)
All while adding a single layer of security by encrptying the file contents being written to it
*/

/*-----------program interface (class definition)------------*/
class Sdisk{
    public:
    Sdisk();
    Sdisk(string diskName, int numberofblocks, int blocksize);//constructor takes disk name, blocksize, and blocknumber; formats the disk
    int getblock(int blocknumber, string& buffer);//find the blocksize and save as reference to the buffer
    int putblock(int blocknumber, string buffer);//insert size of block in bytes to the disk from the buffer
    int getnumberofblocks();//accessor function
    int getblocksize();//accessor function 
    private:
    string diskName;//name of software disk
    int blocksize;//store block size in bytes
    int numberofblocks;//stores number of blocks on disk
};
#endif
//Create a txt file with bn*bs number of characters...blocksize sized blocks...numberblocks number of blocks
/*
    base case: bs = 1 then Block 0 has blocks of size 1 Byte...1x2 table constructed in Sdisk
    blocksize -> Byte = bs - (i)*bs - 1;
    numberblocks -> Block = bn - 1;
*/
