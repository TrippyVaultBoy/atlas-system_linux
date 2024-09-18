#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/**
 *
 */
bool _strcmp (const char *str1, const char *str2)
{
	while (*str1 && *str2) {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return (*str1 == *str2);
}

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
	int directory_count = 0;
	int hidden_files = 0;

	for (i = 1; i < argc; i++)
	{
		if (_strcmp(argv[i], "-1"))
		{
			one_column = 1;
		}

		if (_strcmp(argv[i], "-a"))
		{
			hidden_files = 1;
		}
	}

	for (i = 1; i < argc; i++)
	{
		if (_strcmp(argv[i], "-1") || _strcmp(argv[i], "-a"))
			continue;
		
		if (lstat(argv[i], &fileStat) == 1)
		{
			fprintf(stderr, "%s: cannot access %s: No such file or directory\n", argv[0], argv[i]);
			continue;	
		}

		if (S_ISDIR(fileStat.st_mode))
			directory_count++;
	}

    for (i = 1; i < argc; i++) {
		if (_strcmp(argv[i], "-1") || _strcmp(argv[i], "-a"))
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
			if (directory_count > 1)
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
				if (read->d_name[0] == '.' && hidden_files == 0) {
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
			closedir(dir);
			if (argc == 1)
				break;
		}
    }
    return 0;
}