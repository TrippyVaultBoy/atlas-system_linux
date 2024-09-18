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

int main(int argc, char *argv[]) {
    DIR *dir = NULL;
    struct dirent *read;
    struct stat fileStat;
    int i = 0;
    int one_flag = 0;
    int a_flag = 0;
    int A_flag = 0;
    int l_flag = 0;
    int directory_count = 0;

    // Parse Flags
    for (i = 1; i < argc; i++) {
        if (_strcmp(argv[i], "-1") || _strcmp(argv[i], "-11111")) {
            one_flag = 1;
        } else if (_strcmp(argv[i], "-a")) {
            a_flag = 1;
        } else if (_strcmp(argv[i], "-A")) {
            A_flag = 1;
        } else if (_strcmp(argv[i], "-l")) {
            l_flag = 1;
        }
    }

    // Count Directories
    for (i = 1; i < argc; i++) {
        if (_strcmp(argv[i], "-1") || _strcmp(argv[i], "-11111") || _strcmp(argv[i], "-a") || _strcmp(argv[i], "-A") || _strcmp(argv[i], "-l"))
			continue;

        if (lstat(argv[i], &fileStat) == -1) {
            fprintf(stderr, "%s: cannot access %s: No such file or directory\n", argv[0], argv[i]);
			continue;
        } else if (S_ISDIR(fileStat.st_mode)) {
            directory_count++;
        }
    }

    // List Directories
    for (i = 1; i < argc; i++) {
        // skip over flags
        if (_strcmp(argv[i], "-1") || _strcmp(argv[i], "-11111") || _strcmp(argv[i], "-a") || _strcmp(argv[i], "-A") || _strcmp(argv[i], "-l"))
			continue;

        // check if file/dir exists
        if (lstat(argv[i], &fileStat) == -1) {
            fprintf(stderr, "%s: cannot access %s: No such file or directory\n", argv[0], argv[i]);
			continue;
        } else if (S_ISREG(fileStat.st_mode)) {
            // print file name
            if (one_flag) {
                printf("%s\n", argv[i]);
            } else {
                printf("%s ", argv[i]);
            }
        } else if (S_ISDIR(fileStat.st_mode)) {
            // open directory
            dir = opendir(argv[i]);
            if (dir == NULL) {
                perror("unable to open directory");
                continue;
            }

            // print directory name
            if (directory_count > 1) {
                if (one_flag) {
					printf("%s:\n", argv[i]);
				} else {
					printf("%s: ", argv[i]);
				}
            }

            // print directory contents
            while ((read = readdir(dir)) != NULL) {
                if (read->d_name[0] == '.' && !a_flag && !A_flag)
                    continue;
                
                if (A_flag && (_strcmp(read->d_name, ".") || _strcmp(read->d_name, "..")))
                    continue;

                if (l_flag) {
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
                    if (one_flag) {
                        printf("%s %d %s %s %ld %s %s\n",
                            perms,
                            fileStat.st_nlink,
                            getpwuid(fileStat.st_uid)->pw_name,
                            getgrgid(fileStat.st_gid)->gr_name,
                            fileStat.st_size,
                            time_str,
                            read->d_name
					    );
                    } else {
                        printf("%s %d %s %s %ld %s %s ",
                            perms,
                            fileStat.st_nlink,
                            getpwuid(fileStat.st_uid)->pw_name,
                            getgrgid(fileStat.st_gid)->gr_name,
                            fileStat.st_size,
                            time_str,
                            read->d_name
					    );
                    }
                } else if (one_flag) {
                    printf("%s\n", read->d_name);
                } else {
                    printf("%s ", read->d_name);
                }
            }
            if (!one_flag)
                printf("\n"); 
            
            closedir(dir);

            if (argc == 1)
                break;
        }
    }
    return 0;
}