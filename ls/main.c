#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *read;
    char dirEntries [] = {};

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