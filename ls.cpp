
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

using std::cout;
using std::endl;

void printPermissions(struct stat & s, char * filepath)
{
	printf((s.st_mode & S_IFDIR) ? "d" : "-");
	printf((s.st_mode & S_IRUSR) ? "r" : "-"); 	
	printf((s.st_mode & S_IWUSR) ? "w" : "-");
	printf((s.st_mode & S_IXUSR) ? "x" : "-");
	printf((s.st_mode & S_IRGRP) ? "r" : "-"); 	
	printf((s.st_mode & S_IWGRP) ? "w" : "-");
	printf((s.st_mode & S_IXGRP) ? "x" : "-");
	printf((s.st_mode & S_IROTH) ? "r" : "-"); 	
	printf((s.st_mode & S_IWOTH) ? "w" : "-");
	printf((s.st_mode & S_IXOTH) ? "x. " : "-. ");
	
	cout << s.st_nlink << " ";
	struct passwd *puid = getpwuid(s.st_uid);
	cout << puid->pw_name << " ";
	struct group *gid = getgrgid(s.st_gid);
	cout << gid->gr_name << " ";
	printf("%6zu", s.st_size);
	char * time = ctime(&s.st_mtime);
	for (int i = 3; i < 16; ++i)
		cout << time[i];
	cout << " " << filepath;
	cout << endl;
}

int main (int argc, char * argv[]){
	
	//char buffer[BUF_SIZE];
	
	if (argc == 1)
	{
		DIR *current;
		struct dirent *dp;
		struct stat sb;

		if ((current = opendir (".")) == NULL)
		{
			perror ("Can't open directory");
			return EXIT_FAILURE;
		}
		else
		{
			if (stat(".", &sb) == -1)
			{
				perror("Stat");
				return EXIT_FAILURE;
			}
			while ((dp = readdir(current)) != NULL)
			{
				if (stat(dp->d_name, &sb) == -1)
				{
					perror("Stat");
					return EXIT_FAILURE;
				}
				printPermissions(sb, dp->d_name);
			}
		}
	} //if (no file, assume pwd)

	if (argc == 2)
	{
		char * path = argv[1];
		struct stat sb;
		if (stat(path, &sb) == -1)
		{
			perror("Stat");
			return EXIT_FAILURE;
		}
		else
		{
			printPermissions(sb, path);
		}
	} //if (file)
	
	return EXIT_SUCCESS;

} //main
