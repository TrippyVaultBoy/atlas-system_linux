#include "_getline.h"

char *_getline(const int fd)
{
    char buffer[READ_SIZE];
    size_t total_size = 0;
    size_t buffer_size = READ_SIZE;
    char *line = NULL;
    ssize_t bytes_read;

    if (fd < 0)
    {
        return NULL;
    }

    line = malloc(buffer_size);
    if (line == NULL)
    {
        return NULL;
    }

    while (1)
    {
        bytes_read = read(fd, buffer, READ_SIZE);
        if (bytes_read <= 0)
        {
            free(line);
            return NULL;
        }

        if (total_size + bytes_read >= buffer_size)
        {
            buffer_size *= 2;
            line = realloc(line, buffer_size);
            if (line == NULL)
            {
                return NULL;
            }
        }

        memcpy(line + total_size, buffer, bytes_read);
        total_size += bytes_read;

        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                line[total_size - bytes_read + i] = '\0';  // Null-terminate the line
                return line;
            }
        }
    }

    line[total_size] = '\0';
    return line;
}