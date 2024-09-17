#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
/**
 * main- program entry point
 *
 * Return: 0 or -1
 */
int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *read;
	struct stat fileStat;
    int i;

    for (i = 1; i < argc; i++) {
		if (lstat(argv[i], &fileStat) == -1)
		{
			perror("lstat error");
			return -1;
		}

		if (S_ISREG(fileStat.st_mode))
		{
			printf("%s\n", argv[i]);
			return 0;
		}
		else if (S_ISDIR(fileStat.st_mode))
		{
			if (argc > 2)
				printf("%s:\n", argv[i]);

        	dir = opendir(argv[i]);
        
			if (dir == NULL) {
				perror("unable to open directory");
				return -1;
			}

			while ((read = readdir(dir)) != NULL) {
				if (read->d_name[0] == '.') {
					continue;
				}

				printf("%s ", read->d_name);	
			}
		
			printf("\n");

			if (argc == 1)
				break;
		}
    }

    closedir(dir);
    return 0;
}