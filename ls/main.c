#include <stdio.h>
#include <dirent.h>

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

        if (read->d_name[0] == '.' && (read->d_name[0] == '\n' || read->d_name[1] == '.'))
        {
            continue;
        }

        printf("%s\n", read->d_name);
    }

    closedir(dir);
    return 0;
}