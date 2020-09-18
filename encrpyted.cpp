#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

/*
Simulating the inner workings of a SSD or Hard disk drive (HDD)
All while adding a single layer of security by encrptying the file contents being written to it
*/

/*-----------program interface (class definition)------------*/
class Sdisk{
    public:
    Sdisk(string diskName, int blocknumber, int blocksize);//constructor takes disk name, blocksize, and blocknumber
    int getblock(int blocksize, string& buffer);//find the blocksize and pass as reference the buffer
    int putblock(int blocksize, string buffer);//insert size of block in bytes
    int getnumberofblocks();//accessor function
    int getblocksize();//accessor function 
    private:
    //static int salt;key value to initiate encryption/decryption process
    string diskName;//name of software disk
    int getblocksize;//store block size in bytes
    int getnumberofblocks;//stores number of blocks on disk

};

/*-----------instantiate functions------------*/
//Create a txt file with bn*bs number of characters...blocksize sized blocks...numberblocks number of blocks
/*
    base case: bs = 1 then Block 0 has blocks of size 1 Byte...1x2 table constructed in Sdisk
    blocksize -> Byte = bs - (i)*bs - 1);
    numberblocks -> Block = bn - 1;
*/
Sdisk::Sdisk(string dn,int bn,int bs)
{
    diskName = dn;
    getblocksize = bs;
    getnumberofblocks = bn;
    ifstream infile;//file handle
    infile.open(diskName.c_str());//file opened
    /*alternative approach would enter while(infile.good()), 
    then have if(diskName != "./CSE4610/CSE4610"), and else reads txt and stores values in bn and bs*/
    if(!infile.is_open())
    {
        ofstream newdisk;
        newdisk.open(diskName.c_str());//use the parameter to name the unnamed new disk
        cout << "Enter number of blocks to be placed on the Sdisk: ";//this might output to both the CLI and txt file...
        infile >> getblocksize;
        cout << "Enter desired block size in bytes: ";
        infile >> getnumberofblocks;
        newdisk << getnumberofblocks << getblocksize;
        newdisk.close();
        infile.close();
    }//closing output and  input streams
    else{
        infile >> getblocksize >> getnumberofblocks;//read first line for bn and bs
        infile.close();
    }
}//we should have the block size and number of blocks variables at this point

int Sdisk::getblock(int blocksize, string& buffer){
 //allocate blocknumber and store into buffer   
}
/*-----------driver function------------*/
int main(){

}