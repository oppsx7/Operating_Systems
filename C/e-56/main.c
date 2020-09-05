#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <stdbool.h>

int main(int argc, char** argv){

if(argc != 3 ) {
	err(1, "Wrong number of files");
}

char *file = argv[1], *dest = argv[2];

//ssize_t fd1 = open(file, O_RDONLY);
ssize_t fd2 = open(dest, O_CREAT | O_TRUNC | O_RDWR, 0644);
if(fd2 == -1){
	err(2, "Cant open file");
}

int a[2];
if( pipe(a) == -1){
	err(1, "cant pipe");
}
const pid_t child = fork();
if( child == -1){
	err(3, "cant fork");
}

if(child == 0){
	close(a[0]);
	if(dup2(a[1],1) == -1){
		err(5, "cant dup2");
	}
	if(execlp("xxd", "xxd","-p", file, (char*)NULL) == -1){
		err(4, "cant exec command");
	}
}
wait(NULL);
close(a[1]);
if(dup2(a[0],0) == -1){
	err(6, "cant dup2");
}
ssize_t reader;
char buf;
bool flag = 0;
while((reader = read(a[0], &buf, sizeof(buf))) > 0) {
	if(buf == 0x55){
		continue;
	} else if(buf == 0x7D) {
		flag = 1;
	} else {
		if(flag){
			char coded = buf ^ 0x20;
			write(fd2, &coded, sizeof(coded));
			flag = 0;
		} else {
			write(fd2, &buf, sizeof(buf));
		}
	}
}

exit(0);
}
