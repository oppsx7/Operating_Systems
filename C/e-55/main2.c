#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

int main(int argc, char **argv){
	char *fifo = "fifoo";
	mkfifo(fifo, 0644);
	ssize_t fd_fifo = open(fifo, O_RDONLY);
	dup2(fd_fifo, 0);
	close(fd_fifo);
	execlp("sort", "sort", (char*)NULL);

exit(0);
}
