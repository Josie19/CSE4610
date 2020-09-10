#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

/*--------------------class definition-----------------------*/
class PasswordFile
{
	public:
		PasswordFile(string filename);//constructor opens password file
		void addpw(string new_user, string new_pass);//adds a new user and password
		bool checkpw(string usr, string passwd);//checks for an existing user/password combo in password file
	private:
		string filename;//the name of the password file
		vector<string> user;//username read from file
		vector<string> password;//password read from the file
		void synch();//writes the user/pw vectors to the password file
};

/*----------------member function implementations------------*/
PasswordFile::PasswordFile(string filename)
{
	string u,p;
	ifstream infile;//file handle
	infile.open(filename.c_str());//open password file
	infile >> u >> p;//program reads in the first pair of username/pwd
	while(infile.good())
	{
		user.push_back(u);
		password.push_back(p);
		infile >> u >> p;
	}
}

void PasswordFile::synch()
{
	ofstream outfile;//file handle
	outfile.open(filename.c_str());
	for(int i = 0;i < user.size();i++)
	{
		cout << user[i] << " " << password[i] << " " << endl;
	}
}

 void PasswordFile::addpw(string new_user,string new_pass)
{
	for(int i = 0; i < user.size();i++)
	{
		if(new_user == user[i])
		{
			cout << "user exists" << endl;
			return;
		}
	}
	user.push_back(new_user);
	password.push_back(new_pass);
	synch();
}
bool PasswordFile::checkpw(string usr, string passwd)
{
	for(int i = 0; i < user.size();i++)
	{
		if(user[i] == usr)
		{
			if(password[i] == passwd)
			{
				cout << "User name and password combo exists\n";
				return true;
			}
		}
	}
	return 0;
}
/*-------------------driver function-------------------------*/
int main()
{
	PasswordFile passfile("passwords.txt");
	passfile.addpw("jmagallanes","1qaz2wsx");
	cout << passfile.checkpw("madams","apple") << endl;
	return 0;
}
