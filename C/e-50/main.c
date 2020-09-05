#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){
if(write(1, "Toshko's prompt: ", 18) != 18)
        err(5, "could not write prompt");

while(1) {

char cmd[1<<5];
	ssize_t read_sz = read(0, &cmd, sizeof(cmd));
	if(read_sz == -1)
		err(2, "could not read from stdin");

cmd[read_sz - 1] = '\0';

if(strcmp(cmd, "exit") == 0) {
break;
}

const pid_t child = fork();

if(child == -1){
//err
}

if(child == 0) {
	if(execlp(cmd, cmd, (char*)NULL) == -1){
		//err
	}
}
if(wait(NULL) == -1)
	err(4, "could not wait");

if(write(1, "Toshko's prompt: ", 18) != 18)
	err(5, "could not write prompt");

}
exit(0);
}
