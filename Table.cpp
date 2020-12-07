#include "Table.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "filesys.h"
using namespace std;
Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile):Filesys(diskname, numberofblocks, blocksize)
{
    
    // Create flatfile in filesys
    newfile(flatfile);
    this->flatfile = flatfile;
    

    // Create indexfile in filesys
    newfile(indexfile);
    this->indexfile = indexfile;
    

    cout << "Table created" << endl;
}

int Table::buildtable(string inputfile)
{
	ifstream infile;
	infile.open(inputfile.c_str());
	string record;
	int count = 0;
	getline(infile, record);

	vector<string> key;
	vector<string> iblock;

	ostringstream outstream;

	while (getline(infile, record)) {
        cout << "Checkpoint!" << endl;
		string primarykey = record.substr(0, 5);
		vector<string> oblock = block(record, getblocksize());
		int blockid = addblock(flatfile, oblock[0]);
        cout << "blockid: " << blockid << endl;
		outstream << primarykey << " " << blockid << " ";
		count++;
		if (count == 4) {
            cout << "Checkpoint 1" << endl;
			vector<string> o2block = block(outstream.str(), getblocksize());
			addblock(indexfile, o2block[0]);
			count = 0;
            outstream.str("");
            cout << "Checkpoint 2" << endl;
		}
        cout << "record: " << record << endl;
        cout << "Checkpoint 3" << endl;
	}

	return 1;
}

int Table::search(std::string value)
{
	istringstream istream;

	int blockid = indexsearch(value);
	
	if (blockid == -1) {
		return 0;
	}

	while (blockid != 0) {
		std::string buff;
		readblock(indexfile, blockid, buff);

		std::string k; 
        int b;
		istream.str(buff);

		for (int i = 0; i <= 4; ++i) {
			istream >> k >> b;
			if (k == value) {
				return b;
			}
		}
		blockid = nextblock(indexfile, blockid);
	}
    return 0;
}

int Table::indexsearch(string value)
{
    istringstream instream;
    int blockid = getfirstblock(indexfile);

    // check if blockid is -1
    while (blockid != 0)
    {
        string buffer;
        readblock(indexfile, blockid, buffer);
        
        string k;
        int b;
        
        instream.str(buffer);
        
        for (int i = 1; i <= 4; i++)
        {
            instream >> k >> b;
            if (k == value)
            {
                return b;
            }
        }

        blockid = nextblock(indexfile, blockid);
    }
    
    return 1;
}