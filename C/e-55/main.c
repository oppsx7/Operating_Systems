#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
int main(int argc, char** argv) {

	if(argc != 2){
		//err
	}
	char *file = argv[1];
	char *fifo = "fifoo";
	mkfifo(fifo,0644);
	int fd_fifo = open(fifo, O_WRONLY);
	if(fd_fifo == -1){
		//err
	}
	if(dup2(fd_fifo, 1) == -1){
		//err
	}
	close(fd_fifo);
	if(execlp("cat", "cat", file, (char*)NULL) == -1){
		//err
	}

}
