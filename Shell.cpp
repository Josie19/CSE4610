#include "Shell.h"


Shell::Shell(std::string filename, int blocksize, int numberofblocks):Filesys(filename, numberofblocks, blocksize){}

//dir will be listing all the files in the directory
int Shell::dir()
{
	std::vector<std::string> flist = ls();
	for (int i = 0; i < flist.size(); ++i) {
		std::cout << flist[i] << std::endl;
	}
	return 1;
}

//add will add a new file using input from the keyboard
int Shell::add(std::string file)
{
	//8 is the size of a block
	int x = 8;
	if (file.size() > x) {
		file = file.substr(0, x);
	}
	return newfile(file);
}

//deletes the file it is currently at. 
int Shell::del(std::string file)
{
	int block = getfirstblock(file);
	while (block > 0) {
		delblock(file, block);
		block = getfirstblock(file);
	}
	return rmfile(file);
}

//lists the content of the file. 
int Shell::type(std::string file)
{
	int block = getfirstblock(file);
	string buffer;
	while (block > 0) {
		string t;
		int error = readblock(file, block, t);
		buffer += t;
		block = nextblock(file, block);
	}
	std::cout << buffer << std::endl;
	return 1;
}

//copies file1 to file2 and thats it. 
int Shell::copy(std::string file1, std::string file2)
{
	int code = getfirstblock(file1);
	if (code == -1) {
		return 0;
	}

	int code2 = getfirstblock(file2);
	if (code2 == -1) {
		std::cout << "file 2 exists" << std::endl;
		return 0;
	}

	int code3 = newfile(file2);
	if (code3 == 0) {
		std::cout << "no space in root directory" << std::endl;
		return 0;
	}

	int iblock = code; // first block
	while (iblock != 0) {
		std::string b;
		getblock(0, b);
		int code4 = addblock(file2, b);
		if (code4 == 1) {
			std::cout << "no space left" << std::endl;
			del(file2);
			return 0;
		}
		iblock = nextblock(file1, iblock);
	}

	return 1;
}

int Shell::clobber(string file)
{
    int iblock = getfirstblock(file);

    // Non-recursive
    /*
    if (iblock == -1)
    {
        cout << "no such file";
        return 0;
    }
    while(iblock != 0)
    {
        delblock(file, iblock);
        int iblock2 = nextblock(file, iblock);
        iblock = iblock2;
    }
    */

    // Recursive
    if (iblock == -1)
    {
        cout << "no such file";
        return 0;
    }
    else
    {
        if (iblock != 0)
        {
            delblock(file, iblock);
            cout << "Deleting block " << iblock << " from file " << file << endl;
            int iblock2 = nextblock(file, iblock);
            iblock = iblock2;
            clobber(file);
        }
    }
    
    rmfile(file);   

    return 1;
}