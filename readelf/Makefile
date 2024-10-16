CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

0-hreadelf: readelf.c print_header_32.c print_header_64.c
	$(CC) $(CFLAGS) -o 0-hreadelf readelf.c print_header_32.c print_header_64.c

clean:
	rm -f 0-hreadelf