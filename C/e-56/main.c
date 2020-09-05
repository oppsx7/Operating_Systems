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

ssize_t fd1 = open(file, O_RDONLY);
ssize_t fd2 = open(dest, O_CREAT | O_TRUNC | O_RDWR, 0644);
if(fd1 == -1 || fd2 == -1){
	err(2, "Cant open file");
}

ssize_t reader;
char buf;
bool flag = 0;
while((reader = read(fd1, &buf, sizeof(buf))) > 0) {
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
