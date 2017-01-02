
#include <sys/stat.h>
#include <sys/types.h>
#include <features.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <bitset>
#include <string.h>
#include <fstream>
#include <math.h>
#include <errno.h>

using std::cout;
using std::endl;
using std::setbase;
using std::ifstream;
using std::bitset;

#define READ 4;
#define WRITE 2;
#define EXEC 1;	

int main(int argc, char **argv){
		
	int aflags = 0;
	//s = 1
	//o = 2
	int bflags = 0;
	//u = 1, g = 3, o = 5, ug = 4, uo = 6, ugo = 9, a = 9, go = 8	
	int o = -1;
	int permissions = 0;
	char * file = argv[3];
	char * arg = argv[1];
	if ((strcmp(arg, "-sym") == 0))
		aflags = 1;
	else if ((strcmp(arg, "-oct") == 0))
		aflags = 2;
	else
	{
		cout << "Invalid option" << endl;
		return EXIT_FAILURE;
	}
	
	if (aflags == 0)
	{
		return EXIT_FAILURE;
	}
	else if (aflags == 1)
	{
		//+-=
		char operation;
		char * flags = argv[2];	
		int length = sizeof(flags)/sizeof(char);
		for (int i = 0; i < length - 1; ++i)
		{	
			if (flags[i] == 'u')
				bflags += 1;
			if (flags[i] == 'g')
				bflags += 3;
			if (flags[i] == 'o')
				bflags += 5;
			if (flags[i] == 'a')
				bflags = 9;
			if (flags[i] == '+')
				operation = '+';
			else if (flags[i] == '-')
				operation = '-';
			else if (flags[i] == '=')
				operation = '=';
			if (flags[i] == 'r')
				permissions = permissions | READ;
			if (flags[i] == 'w')
				permissions = permissions | WRITE;
			if (flags[i] == 'x')
				permissions = permissions | EXEC;		
		}
		struct stat sb;
		stat(file, &sb);	
			
		if (operation == '=')
		{
			if (bflags == 1)
			{	
				int permmask = (7 << 3) | (7);
				permmask = permmask & sb.st_mode;
				permissions = permissions<<6 | permmask;
			}
			else if (bflags == 3)
			{
				int permmask = (7 << 6) | 7;
				permmask = permmask & sb.st_mode;
				permissions = (permissions << 3 | permmask);
			}
			else if (bflags == 5)
			{	
				int permmask = (7 << 6) | 7 << 3;
				permmask = permmask & sb.st_mode;
				permissions = (permissions | permmask);
			}
			else if (bflags == 4)
			{
				int permmask = 7;
				permmask = permmask & sb.st_mode;
				permissions = (permissions << 6 | permissions << 3 | permmask);
			}
			else if (bflags == 6)
			{
				int permmask = 7 << 3;
				permmask = permmask & sb.st_mode;
				permissions = (permissions << 6 | permissions | permmask);
			}
			else if (bflags == 9)
				permissions = (permissions << 6) | (permissions << 3) | (permissions);	
			else if (bflags == 8)
			{
				int permmask = 7 << 6;
				permmask = permmask & sb.st_mode;
				permissions = (permissions << 3 | permissions | permmask);
			}
		}

	if (operation == '+')
		{
			if (bflags == 1)
				permissions = (permissions << 6 | (sb.st_mode));
			else if (bflags == 3)
				permissions = (permissions << 3 | (sb.st_mode));
			else if (bflags == 5)
				permissions = (permissions | (sb.st_mode));
			else if (bflags == 4)
				permissions = ((permissions << 6) | (permissions << 3) | (sb.st_mode));
			else if (bflags == 6)
				permissions = ((permissions << 6) | (permissions) | (sb.st_mode));
			else if (bflags == 9)
				permissions = ((permissions << 6) | (permissions << 3) | (permissions) | (sb.st_mode));
			else if (bflags == 8)
				permissions = ((permissions << 3) | (permissions) | (sb.st_mode));	
		}
		if (operation == '-')
		{
			if (bflags == 1)
				permissions = (~(permissions << 6) & (sb.st_mode));
			else if (bflags == 3)
				permissions = (~(permissions << 3) & (sb.st_mode));
			else if (bflags == 5)
				permissions = (~(permissions) & (sb.st_mode));
			else if (bflags == 4)
				permissions = (~((permissions << 6) | (permissions << 3)) & (sb.st_mode));
			else if (bflags == 6)
				permissions = (~((permissions << 6) | (permissions)) & (sb.st_mode));
			else if (bflags == 9)
				permissions = (~((permissions << 6) | (permissions << 3) | (permissions)) & (sb.st_mode));
			else if (bflags == 8)
			{
				permissions = (~((permissions << 3) | (permissions)) & (sb.st_mode));	
			}
		}
	}
	else if (aflags == 2)
	{	
		//Octal
		char * p;
		o = strtol(argv[2], &p, 10);
		if (( o/100 > 7 || o < 0))
		{
			cout << "Invalid input" << endl;
			return EXIT_FAILURE;
		}
		int p1 = 1;
		int p2 = 1;
		int p3 = 1;
		int n = 0;
		p1 = o %10;
		if (o > 10)
			p2 = o/10%10;
		if (o > 100)
			p3 = o/100%10;
		if (p1 > 7 || p2 >7 || p3 > 7)
		{
			cout << "Invalid input" << endl;
		}
		
		while (o > 0)
		{
			permissions += ((pow(8,n++)) * ( o % 10));	
			o /=10;
		}
	}

	if (!ifstream(file))
	{
		if (errno == ENOENT)
		{
			//cout << "Error: " << strerror(errno) <<endl;
			perror("File");
			return EXIT_FAILURE;
		}
	}
	int f = chmod(file, permissions);
	
	if (f == -1)
	{
		perror("chmod error:");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
} //main
