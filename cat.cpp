
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>

#define BUF_SIZE 1024

using std::cout;
using std::endl;

int main (int argc, char * argv[]){

	ssize_t input;
	char buffer[BUF_SIZE];

	if (argc > 1)
	{
		for (int i = 1; i <= argc - 1; ++i)
		{
			int fd = open(argv[i], O_RDONLY);
			if (fd == -1)
			{	
				perror("Open");
				return EXIT_FAILURE;
			}
			else
			{
				while ((input = read (fd, &buffer, BUF_SIZE)) > 0)
				{
					write (1, buffer, input);				
				}
			}
			int f = close(fd);
			if (f == -1)
			{
				perror("Close");
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
} //main
