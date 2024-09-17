#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
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
	int one_column = 0;

	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-1") == 0)
		{
			one_column = 1;
			break;
		}
	}

    for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-1") == 0)
			continue;
		
		if (lstat(argv[i], &fileStat) == -1)
		{
			fprintf(stderr, "%s: cannot access %s: No such file or directory\n", argv[0], argv[i]);
			return -1;
		}

		if (S_ISREG(fileStat.st_mode))
		{
			if (one_column == 1)
			{
				printf("%s\n", argv[i]);
			}
			else
			{
				printf("%s ", argv[i]);
			}
			
		}
		else if (S_ISDIR(fileStat.st_mode))
		{
			if (argc > 2)
			{
				if (one_column == 1)
				{
					printf("%s:\n", argv[i]);
				}
				else
				{
					printf("%s: ", argv[i]);
				}
			}

        	dir = opendir(argv[i]);
			if (dir == NULL) {
				perror("unable to open directory");
				continue;
			}

			while ((read = readdir(dir)) != NULL) {
				if (read->d_name[0] == '.') {
					continue;
				}

				if (one_column == 1)
				{
					printf("%s\n", read->d_name);	
				}
				else
				{
					printf("%s ", read->d_name);	
				}
			}
			printf("\n");
			if (argc == 1)
				break;
		}
    }

    closedir(dir);
    return 0;
}