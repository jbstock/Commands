
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <math.h>
#include <cstring>

using std::cout;
using std::endl;

//from stackoverflow.com/questions/19891962/c-how-to-append-a-char-to-char
char * addASlash(char * array)
{
	size_t len = std::strlen(array);
	char * r = new char [len + 1];
	strcpy(r, array);
	r[len] = '/';

	return r;
} //addASlash

int main (int argc, char * argv[]) {
	
	if (argc > 1)
	{
		if (strcmp(argv[1], "-p") == 0)
		{
			char *dName;
			int mode = 493; //0755 as int
			if (argc > 2)
				dName = argv[2];
			else 
			{
				cout << "Invalid input";
				return 0;
			}
			char * dir;

			dir = strtok(dName, "/");
			int count = 0;
			int f = -1;
			char * x;
			while (dir != NULL && count < 6)
			{
				if (count == 0)
				{	
					x = dir;
					f = mkdir(dir, mode);
					x = addASlash(x);
				}
				else
				{
					strcat(x, dir);
					x = addASlash(x);
					f = mkdir(x,mode);
				}
				if (f != 0)
				{
					perror("mkdir");
					return EXIT_FAILURE;
				}
				dir = strtok(NULL, "/");
				++count;
			}	
		} // -p

		else if (strcmp(argv[1], "-m") == 0)
		{
			
			char * dName;
			int o;
			int mode;
			char * p;
			if (argc > 2)
				o = strtol(argv[2],&p, 10);
			else
			{
				cout << "Invalid input";
				return 0;
			}
			if ((o/100 > 7 || o < 0))
			{
				cout << "Invalid input";
				return 0;
			}
			int p1 = 0;
			int p2 = 0;
			int p3 = 0;
			int n = 0;
			p1 = o% 10;
			if (o>10)
				p2 = o/10%10;
			if (o>100)
				p3 = o/100%10;
			if (p1 > 7 || p2 > 7 || p3 > 7)
			{
				cout << "Invalid input";
				return 0;
			}
			while (o >0)
			{
				mode += ((pow(8,n++)) * (o%10));
				o/=10;
			}
			if (argc == 4)
			{
				dName = argv[3];		
			}
			else
			{
				cout << "Invalid input";
				return 0;
			}
			int f = mkdir(dName, mode);
			if (f != 0)
			{
				perror("mkdir");
				return EXIT_FAILURE;
			}
		} // -m

		else 
		{
			cout << "Invalid input";
			return 0;
		}
	}
	return EXIT_SUCCESS;
} //main
