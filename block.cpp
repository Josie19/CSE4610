#include<string>
#include<vector>

using namespace std;

vector<string> block(string buffer, int b)//int b is blocksize
{
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