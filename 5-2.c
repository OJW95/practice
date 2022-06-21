#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void do_wc(const char* path);

int main(int argc, char** argv)
{
	if (argc < 2) {
		fprintf(stderr, "%s : No file name", argv[0]);
		exit(1);
	}
	for (int i = 1; i < argc; i++) {
		do_wc(argv[i]);
	}

	exit(0);
}

#define BUFF_SIZE 2048

static void do_wc(const char* path)
{
	int fd;
	unsigned char buf[BUFF_SIZE];
	int n;

	fd = open(path, O_RDONLY);
	if (fd < 0) {
		perror(path);
		exit(1);
	}
	while(1) {
		int count = 0;
		n = read(fd, buf, sizeof buf);
		if (n < 0) {
			perror(path);
			exit(1);
		}
		if (n == 0) break;
		if (n > 0) {
			for (int i = 0; i < n; i++) {
				if (buf[i] == '\n')
					count += 1;
			}
			printf("LINE SIZE : %d\n", count);
		}
	}
}


