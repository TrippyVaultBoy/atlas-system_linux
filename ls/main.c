#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *read;

    dir = opendir("../getline");
    if (dir == NULL)
    {
        perror("unable to open directory");
        return -1;
    }

    while ((read = readdir(dir)) != NULL)
    {
        printf("%s\n", read->d_name);
    }

    closedir(dir);
    return 0;
}