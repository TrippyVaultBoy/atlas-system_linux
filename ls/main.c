#include <stdio.h>
#include <dirent.h>
/**
 * main- program entry point
 *
 * Return: 0 or -1
 */
int main() {
    DIR *dir;
    struct dirent *read;

    dir = opendir("../test");
    if (dir == NULL)
    {
        perror("unable to open directory");
        return -1;
    }

    while ((read = readdir(dir)) != NULL)
    {
        if (read->d_name[0] == '.')
        {
            continue;
        }

        printf("%s ", read->d_name);
    }
    printf("\n");

    closedir(dir);
    return 0;
}