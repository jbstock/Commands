
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cstring>

using std::cout;
using std::endl;

int main (int argc, char * argv[]){

	if (argc != 3)
	{
		cout << "Invalid input" << endl;
		return EXIT_FAILURE;
	}
	bool dir = false;
	char * fileToMove = argv[1];
	char * fileDest = argv[2];
	//char * fileDest2 = new char[fileToMove.length + fileDest.length +1];
	int fd;
	int fd2;
	int fd3;
	struct stat sb;
	if (stat(fileDest, &sb) == 0)
	{
		if (sb.st_mode & S_IFDIR)
		{
			dir = true;
		}
	}
	cout << dir;
	fd = open(fileToMove, O_RDONLY);
	if (fd == -1)
	{
		perror("FILE");
		return EXIT_FAILURE;
	}
	
	if (dir == false)
	{
		fd2 = open(fileDest, O_RDONLY);
		if (fd2 != -1)
		{
			cout << fileDest << " already exists" << endl;
		}
	}

	else if (dir == true)
	{
		if (strcmp(fileDest, "..") == 0)
		{
			char * check2 = new char [4];
			check2[0] = '.';
			check2[1] = '.';
			check2[2] = '/';
			check2[3] = '\0';
			char * filepath2 = (char *) malloc(1 + std::strlen(check2) + std::strlen(fileToMove));
			strcpy(filepath2, check2);
			strcat(filepath2, fileToMove);
			cout <<filepath2;
			fd3 = rename(fileToMove, filepath2);
			delete [] filepath2;
			if (fd3 == -1)
			{
				perror("Rename");
				return EXIT_FAILURE;
			}
			else 
				return EXIT_SUCCESS;
		}
		char * filepath = (char *) malloc(1 + std::strlen(fileDest) + std::strlen(fileToMove));
		strcpy(filepath, fileDest);
		strcat(filepath, fileToMove);
		fd3 = rename(fileToMove, filepath);
		if (fd3 == -1)
		{
			perror("Rename");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int fd4 = rename(fileToMove, fileDest);
	if (fd4 == -1)
	{
		perror("Rename");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
} //main
