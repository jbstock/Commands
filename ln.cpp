
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

using std::cout;
using std::endl;

int main(int argc, char * argv[])
{

	if (argc == 3) 
	{
		char * file1 = argv[1];
		char * file2 = argv[2];
		int fd = link(file1, file2);
		if (fd == -1)
		{
			perror("Link");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	} //reg

	if (argc == 4)
	{
		char * arg = argv[1];
		if ((strcmp(arg, "-S")) == 0)
		{
			char * file1 = argv[2];
			char * file2 = argv[3];
			int fd = symlink(file1, file2);
			if (fd == -1)
			{
				perror("SymLink");
				return EXIT_FAILURE;
			}
		}
		else
		{
			cout << "Invalid input" << endl;
		}
	} //sym

	else
	{
		cout << "Invalid input" << endl;
		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
} //main
