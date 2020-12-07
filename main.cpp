#include<iostream>
#include<sstream>
#include<vector>
#include<string>
//#include<bits/stdc++.h>
#include"sdisk.h"
#include"filesys.h"
#include"Shell.h"
#include"Table.h"

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
/*
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
*/
int main(){
  Sdisk sdisk = Sdisk("sdisk.txt", 256, 128);
    Filesys fsys = Filesys("sdisk.txt", 256, 128);
    Shell shell = Shell("sdisk.txt", 256, 128);
    Table table = Table("sdisk.txt", 256, 128, "flatfile", "indexfile");
    
    table.buildtable("data.txt");

    string s;
    string command="go";
    string op1,op2;
    
    while (command != "quit")
    {
        command.clear();
        op1.clear();
        op2.clear();
        cout << "$";
        getline(cin, s);

        int firstblank = s.find(' ');
        if (firstblank < s.length()) 
            s[firstblank] = '#';

        int secondblank = s.find(' ');
        command = s.substr(0, firstblank);

        if (firstblank < s.length())
            op1 = s.substr(firstblank + 1, secondblank - firstblank - 1);

        if (secondblank < s.length())
            op2 = s.substr(secondblank + 1);

        if (command == "dir")
        {
            // use the ls function
            shell.dir();
        }
        if (command == "search")
        {
            // The variable op1 is the date
            table.search(op1);
            
        }
        if (command == "add")
        {
            // The variable op1 is the new file
            shell.add(op1);
        }
        if (command == "del")
        {
            // The variable op1 is the file
            shell.del(op1);
        }
        if (command == "type")
        {
            // The variable op1 is the file
            shell.type(op1);
        }
        if (command == "copy")
        {
            // The variable op1 is the source file and the variable op2 is the destination file.
            shell.copy(op1, op2);
        }
        if (command == "clobber")
        {
            shell.clobber(op1);
        }  
    }
    return 0;
}
