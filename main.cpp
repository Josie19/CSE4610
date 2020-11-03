#include<iostream>
#include<sstream>
#include<vector>
#include<string>
//#include<bits/stdc++.h>
#include"sdisk.h"
#include"filesys.h"

using namespace std;

vector<string> block(string buffer, int b)
{
	//int b is blocksize
    //blocks the buffer into a list of blocks of size b
    int numberofblocks = 0;
    vector<string> blocks;
    //determine the number of blocks
    if(buffer.length()%b == 0)
    {
        numberofblocks = buffer.length()/b;
    }
    else
    {
        numberofblocks = buffer.length()/b+1;
    }

    string tempBlock;
    for(int i = 0;i < numberofblocks; i++)
    {
        tempBlock = buffer.substr(b*i,b);
        blocks.push_back(tempBlock);
    }

    int lastblock = blocks.size()-1;
    for(int i = blocks[lastblock].length(); i < b; i++)
    {
        blocks[lastblock] += "#";
    }

    return blocks;
    
}
/*-----driver function------*/
int main()
{
  //test sdisk and filesys
  Sdisk disk1("disk1",256,128);
  Filesys fsys("disk1",256,128);
  fsys.newfile("file1");
  fsys.newfile("file2");

  string bfile1;
  string bfile2;

  for(int i=1; i<=1024; i++){
      bfile1+="1";
  }

  vector<string> blocks = block(bfile1,128); 

  int blocknumber=0;

  for(int i = 0; i < blocks.size(); i++){
    blocknumber=fsys.addblock("file1",blocks[i]);
  }

  fsys.delblock("file1",fsys.getfirstblock("file1"));

  for(int i=1; i<=2048; i++)
     {
       bfile2+="2";
     }

  blocks=block(bfile2,128); 

  for(int i=0; i< blocks.size(); i++)
     {
       blocknumber=fsys.addblock("file2",blocks[i]);
     }

  fsys.delblock("file2",blocknumber);
  
  return 0;
}