#include<sstream>
#include<vector>
#include<string>
#include"filesys.h"
#include"sdisk.h"

using namespace std;

Filesys::Filesys(){}

/*------interface implementation-------*/
Filesys::Filesys(string diskname, int numberofblocks, int blocksize):Sdisk(diskname, numberofblocks, blocksize){
    //create fat and root
    string buffer;
    string next_in_line;

    //declare the size of root and fat
    rootsize = getblocksize() / 12;
	fatsize = (5 * getnumberofblocks()) / getblocksize() + 1;
	getblock(1, buffer);

    //next, we determine if a file within the indicated filesystem exists in the indicated block
    if(buffer[0] == '#'){//filesystem does not exist on sDisk so create one here
        for (int i = 0; i < rootsize; i++) {
			filename.push_back("xxxxxxxx");//8 Xs = 8 bits = 1 byte of information per digit
			firstblock.push_back(0);
		}
        /*
        filename     firstblock
        ==========   =========
        |xxxxxxxx|   |   0   |   
        =========    ========= 
        */
		fat.push_back(2+fatsize);
		fat.push_back(-1);

        /*
        filesystem on Sdisk
        ==========   ===========
        |    2   |   |   FAT 0 |   
        =========    ============ 
        */
		for (int i = 0; i < fatsize; ++i) {//continue to 3rd index of filesystem table
			fat.push_back(-1);
		}

		for (int i = fatsize + 2; i < numberofblocks; i++) {
			fat.push_back(i + 1);
		}
		fat[fat.size() - 1] = 0;//make end-of-file, or block list, zero

		fssynch();
		cout << "Succesfully Created New File" << endl;
    }
    else{
        istringstream fstream1;
        istringstream fstream2;

        ostringstream string_output;
		string buffer1;
		getblock(0, buffer1);
		fstream1.str(buffer1);//take a snapshot and store in first buffer

		for (int i = 0; i < rootsize; ++i) {
			string m;
			int x;
			fstream1 >> m >> x;
			filename.push_back(m);
			firstblock.push_back(x);
		}

		string currBuffer;

		for (int i = 0; i <= fatsize; i++) {
			string temp;
			getblock(i, temp);
			currBuffer += temp;
		}

		fstream2.str(currBuffer);
		for (int i = 0; i < numberofblocks; ++i) {
			int z = 0;
			fstream2 >> z;
			fat.push_back(z);
		}
	}
    fssynch();
}

int Filesys::fsclose()
{
    fssynch();
    return 1;
}

int Filesys::fssynch()
{
	string buffer, fat_buffer;
	ostringstream output; //fat stream
	ostringstream root_stream;
	
	for (int i = 0; i < rootsize; ++i) {
		root_stream << filename[i] << " " << firstblock[i] << " ";
	}

	/*getting fat*/
	for (int i = 0; i < fat.size(); i++) {
		output << fat[i] << " ";
	}

	buffer = root_stream.str();
	fat_buffer = output.str();
	vector<string> root_creation;
	vector<string> fat_creation;

	root_creation = block(buffer, getblocksize());
	fat_creation = block(fat_buffer, getblocksize());

	putblock(0, root_creation[0]);


	for (int i = 1; i <= fat_creation.size(); ++i) {
		putblock(i, fat_creation[i - 1]);
	}

    return 1;
}

/**********************************************************
 * New file will check to see if the file is already 
 * created, if it is not then go ahead and create the
 * file. if it is there then say the file already exists. 
**********************************************************/
int Filesys::newfile(string file)
{
	//cout << rootsize << endl;//for testing purposes. making sure we have matching file in root
    
    //file exists, confirm with message
	for (int i = 0; i < filename.size(); i++) {
		if (filename[i] == file) {
			cout << "file already exists" << endl;
			return 0;
		}
	}
//file doesn't exist, create and add to sdisk
	for (int i = 0; i < filename.size(); i++) {
		if (filename[i] == "xxxxxxxx") {
			filename[i] = file;
			fssynch();
			return 1;
		}
	}
    return 0;
}

/********************************************************
 * Remove file will be responsible for removing the file
 * if needed. if the file is not there, then do not do 
 * anything since the file does not exist. 
********************************************************/
int Filesys::rmfile(string file)
{
	for (int i = 0; i < rootsize; i++) {
		if (filename[i] == file) {
			if (firstblock[i] != 0) {
				cout << "file is not empty" << endl;
				return 0;
			} else {
				filename[i] == "xxxxxxxx";
				fssynch();
				return 1;
			}
		}
	}
    return 0;
}

/*******************************************************
 * returns the first block of the file
*******************************************************/
int Filesys::getfirstblock(string file)
{
	for (int i = 1; i < filename.size(); i++) {
		if (filename[i] == file) {
			return firstblock[i];
		}
	}
    return 1;
}

/*********************************************************
 * adds a block of data stored in the buffer string 
 * to the end of the file and returns the block number. 
*********************************************************/
int Filesys::addblock(string file, string block)
{
	string buffer;
	int first = getfirstblock(file);
	if (first == -1) {
		return 0;
	}

	int allocate = fat[0];
	//checking to see if there are blocks available. 
	if (allocate == 0) {
		//no free blocks
		cout << "no free blocks available" << endl;
		return 0;
	}

    /*
    Lecture 6:
        allocate a block, then free block allocated, and lastley update the freeblock above root (i.e. buffer)
	*/

    fat[0] = fat[fat[0]];
	fat[allocate] = 0;

	//if first is free
	if (first == 0) {
		for (int i = 0; i < rootsize; i++) {
			if (filename[i] == file) {
				//cout << "entering loop" << endl;
				firstblock[i] = allocate;
				putblock(allocate, buffer);
				fssynch();
				return allocate;
			}
		}
		
	} else {
		int block = first;
		while (block != 0) {
			if(fat[block] != 0) { //fat[1] == -1?
				block = fat[block];
			}
			else {
				break;
			}
			fat[block] = allocate;
			putblock(allocate, buffer);
			fssynch();
			return allocate;
		}
	}

	return allocate;
}

/*********************************************************
 * will go to the block number specifically and then 
 * it will remove that block from the file and 
 * synch after. 
*********************************************************/
int Filesys::delblock(string file, int blocknumber)
{
	if (blocknumber == getfirstblock(file)) {
		for (int i = 0; i < filename.size(); ++i) {
			if (filename[i] == file) {
				firstblock[i] = fat[blocknumber];
			}
		}
	}

    int remov = blocknumber;
    if(blocknumber == getfirstblock(file)) {
        for(int i = 0; i < filename.size(); ++i) {
            if(file == filename[i]) {
                if(nextblock(file, blocknumber) != -1) {
                    firstblock[i] = nextblock(file, blocknumber);
                } else {
                    firstblock[i] = fat[remov];
                    break;
                }
            }
        }
    }
    else {
        int iblock = getfirstblock(file);
        while(fat[iblock] != remov) {
            iblock = fat[iblock];
        }
        fat[iblock] = fat[remov];
    }
    fat[remov] = fat[0];
    fat[0] = remov;
	fssynch();
    return 1;
}

/*********************************************************
 * gets the block number and stores it in the buffer and 
 * returns correct or not depending if it is their 
*********************************************************/
int Filesys::readblock(string file, int blocknumber, string& buffer)
{
    if(checkblock(file, blocknumber)) {
    	getblock(blocknumber, buffer);
        return 1;
    }
    return 0;
}

/*********************************************************
 * writes buffer to block number in the correct location. 
*********************************************************/
int Filesys::writeblock(string file, int blocknumber, string buffer)
{
    if(checkblock(file, blocknumber)) {
        putblock(blocknumber, buffer);
        return 1;
    }
    return 0;
}

/*********************************************************
 * returns the number of blocks that follows the 
 * block_number. 
*********************************************************/
int Filesys::nextblock(string file, int block_number)
{
	int block = getfirstblock(file);

	bool correct = true;
	while (correct) {
		if (block == block_number) {
			if (fat[block] == 0) {
				return 0;
			} else {
				return fat[block];
			}
		}
		if (fat[block] == 0) {
			correct = false;
		}

		block = fat[block];
	}

    return -1;
}

/*********************************************************
 * returning rootsize
*********************************************************/
int Filesys::getrootsize()
{
    return rootsize;
}

/*********************************************************
 * returning fat size
*********************************************************/
int Filesys::getfatsize()
{
    return fatsize;
}

bool Filesys::checkblock(string file, int blocknumber)
{
    int iblock = getfirstblock(file);
    while(iblock != 0) {
        if(iblock == blocknumber) {
            return true;
        }
        iblock = fat[iblock];
    }
    return false;
}
 
vector<string> Filesys::ls()
{
	vector<string> flist;
	for (int i = 0; i < filename.size(); ++i) {
		if (filename[i] != "xxxxxxxx") {
			flist.push_back(filename[i]);
		}
	}
	return flist;
}

/*-------block function-------*/
vector<string> Filesys::block(string buffer, int b)
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

