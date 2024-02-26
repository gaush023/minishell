#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;
	int newfd;
	const char *text = "Hello, World!\n";

	fd = open("test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	newfd = dup(fd);
	if (newfd == -1) {
		perror("dup");
		return 1;
	}
	write(newfd, text, 13);
	if (newfd == -1) {
		perror("write");
		return 1;
	}
	printf("fd = %d, newfd = %d\n", fd, newfd);

	close(fd);
	close(newfd);

	return 0;
}
