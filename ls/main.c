#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

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
    DIR *dir = NULL;
    struct dirent *read;
	struct stat fileStat;
    int i;
	int one_flag = 0;
	int directory_count = 0;
	int a_flag = 0;
	int A_flag = 0;
	int l_flag = 0;

	for (i = 1; i < argc; i++)
	{
		if (_strcmp(argv[i], "-1"))
		{
			one_flag = 1;
		}
		else if (_strcmp(argv[i], "-a"))
		{
			a_flag = 1;
		}
		else if (_strcmp(argv[i], "-A"))
		{
			A_flag = 1;
		}
		else if (_strcmp(argv[i], "-l"))
		{
			l_flag = 1;
		}
	}

	for (i = 1; i < argc; i++)
	{
		if (_strcmp(argv[i], "-1") || _strcmp(argv[i], "-a") || _strcmp(argv[i], "-A") || _strcmp(argv[i], "-l"))
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
		if (_strcmp(argv[i], "-1") || _strcmp(argv[i], "-a") || _strcmp(argv[i], "-A") || _strcmp(argv[i], "-l"))
			continue;
		
		if (lstat(argv[i], &fileStat) == -1)
		{
			fprintf(stderr, "%s: cannot access %s: No such file or directory\n", argv[0], argv[i]);
			return -1;
		}

		if (S_ISREG(fileStat.st_mode))
		{
			if (one_flag == 1)
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
				if (one_flag == 1)
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
				if (read->d_name[0] == '.' && a_flag == 0 && A_flag == 0) {
					continue;
				}

				if ((_strcmp(read->d_name, ".") || strcmp(read->d_name, "..") == 0) && A_flag == 1)
				{
                	continue;
            	}

				if (l_flag)
				{
					char perms[11];
					perms[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
                    perms[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
                    perms[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
                    perms[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
                    perms[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
                    perms[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
                    perms[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
                    perms[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
                    perms[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
                    perms[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
					perms[10] = '\0';
                    char time_str[20];
                    struct tm *timeinfo = localtime(&fileStat.st_mtime);
                    strftime(time_str, sizeof(time_str), "%b %d %Y", timeinfo);
					printf("%s %d %s %s %ld %s %s\n",
						perms,
						fileStat.st_nlink,
						getpwuid(fileStat.st_uid)->pw_name,
						getgrgid(fileStat.st_gid)->gr_name,
						fileStat.st_size,
                        time_str,
                        read->d_name
					);

				}
				else if (one_flag == 1)
				{
					printf("%s\n", read->d_name);	
				}
				else
				{
					printf("%s ", read->d_name);	
				}
			}
			if (l_flag == 0)
				printf("\n");
			closedir(dir);
			if (argc == 1)
				break;
		}
    }
    return 0;
}