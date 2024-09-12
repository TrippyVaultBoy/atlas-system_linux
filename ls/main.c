#include <stdio.h>
#include <dirent.h>
/**
 * main- program entry point
 *
 * Return: 0 or -1
 */
int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *read;
    int i;

    for (i = 1; i < argc; i++) {
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

    closedir(dir);
    return 0;
}