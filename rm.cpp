
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::string;

int main (int argc, char * argv[]){

	bool recursive = false;
	int indexStart = 1;

	if (argc == 1)
	{
		cout << "Invalid input" <<endl;
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "-R") == 0)
	{
		recursive = true;
		indexStart = 2;
		cout << "recursive" << endl;
	}

	for (int i = indexStart; i < argc; ++i)
	{
		
		char * path = argv[i];
		struct stat sb;
		if (stat(path, &sb) == -1)
		{
			perror("Stat");
			return EXIT_FAILURE;
		}
		cerr << "Are you sure you want to remove " << path << "? (type yes) ";
		string input;
		string yes = "yes";
		getline(cin,input);
		if (recursive == false)
		{
			if (yes.compare(input) == 0)
			{
				if (!(sb.st_mode & S_IFDIR))
				{
					int fd = unlink(path);
					if (fd != 0)
					{
						perror("Unlink");
						return EXIT_FAILURE;
					}
					else
					{
						cout << path << " deleted successfully" << endl;
						continue;
					}
				}
			}
		} //if not -R
		else 
		{
			if (sb.st_mode & S_IFDIR)
			{
				DIR * dirpath;
				struct dirent *dp;
				if ((dirpath = opendir(path)) == NULL)
				{
					perror("Open directory");
					return EXIT_FAILURE;
				}
				else
				{
					while ((dp = readdir(dirpath)) != NULL)
					{
						if (stat(dp->d_name, &sb) == -1)
						{
							perror("Stat");
							return EXIT_FAILURE;
						}
						char * path2 = dp->d_name;
						cerr << "Are you sure you want to remove " << dirpath << "/" << path2 << "? (type yes) ";
						string input2;
						getline(cin,input2);
						if(yes.compare(input2) == 0)
						{
							int fd = unlink(path2);
							if (fd != 0)
							{
								perror("Unlink");
								return EXIT_FAILURE;
							}
							else 
							{
								cout << dirpath << "/" << path2 << " deleted successfully" << endl;
								continue;
							}
						}
					}
				}			
			}
		} // if -R
	}

	return EXIT_SUCCESS;
} //main
