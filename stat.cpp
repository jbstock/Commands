
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

void printInfo(struct stat & s, char * filepath)
{
	cout << "  File: " << "'" << filepath << "'" << endl;
	cout << "  Size: ";
	printf("%6zu",s.st_size);
	cout << "\t\tBlocks: " << s.st_blocks << "\t\tIO Block: " << s.st_blksize << " ";
	if (s.st_mode & S_IFREG) 
		cout << "regular file" << endl;
	else if (s.st_mode & S_IFDIR)
		cout << "directory" << endl;
	else 
		cout << "other" << endl;
	
	cout << "Device: " << s.st_rdev;
	cout << " Inode: " << s.st_ino << "    ";
	cout << "Links: " << s.st_nlink << endl;

	cout << "Access: (";
	printf("%lo", (unsigned long) s.st_mode);
	cout << "/";
	printf((s.st_mode & S_IFDIR) ? "d" : "-");
	printf((s.st_mode & S_IRUSR) ? "r" : "-"); 	
	printf((s.st_mode & S_IWUSR) ? "w" : "-");
	printf((s.st_mode & S_IXUSR) ? "x" : "-");
	printf((s.st_mode & S_IRGRP) ? "r" : "-"); 	
	printf((s.st_mode & S_IWGRP) ? "w" : "-");
	printf((s.st_mode & S_IXGRP) ? "x" : "-");
	printf((s.st_mode & S_IROTH) ? "r" : "-"); 	
	printf((s.st_mode & S_IWOTH) ? "w" : "-");
	printf((s.st_mode & S_IXOTH) ? "x)" : "-)");

	cout << "  Uid: (";
	printf("%ld", (long) s.st_uid);
	struct passwd *puid = getpwuid(s.st_uid);
	cout << "/" << puid->pw_name << ")" << "    ";
	cout << "Gid: (";
	printf("%ld", (long) s.st_gid);
	struct group *gid = getgrgid(s.st_gid);
	cout << "/" << gid->gr_name << ")" << endl;

	printf("Access: %s", ctime(&s.st_atime));
	printf("Modify: %s", ctime(&s.st_mtime));
	printf("Change: %s", ctime(&s.st_ctime));
} //printInfo

int main (int argc, char * argv[]){
	
	if (argc != 2)
	{
		cout << "Invalid input" << endl;
		return EXIT_SUCCESS;
	}

	char * file = argv[1];
	struct stat sb;

	if (stat(file, &sb) == -1)
	{
		perror("Stat");
		return EXIT_FAILURE;
	}

	else
		printInfo(sb, file);

	return EXIT_SUCCESS;
} //main
