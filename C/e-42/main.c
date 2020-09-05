#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

ssize_t contains(char buf, char *set){
	ssize_t i = 0;
	while(set[i] != '\0'){
		if(set[i] == buf) return i;
		++i;
	}
	return -1;
}

int main(int argc, char **argv) {

if(argc != 3){
	errx(1, "Invalid number of args");
}

char b;
if(strcmp(argv[1],"-d") == 0){
char * str = argv[2];
ssize_t rd1 = -1;
ssize_t wr = -1;
while((rd1 = read(0, &b, sizeof(b))) == sizeof(b)) {
	if(contains(b, str) == -1){
		if((wr = write(1, &b, sizeof(b))) != 1) {
			err(2, "failed to write to STDOUT");
		}
	}
}
exit(0);
}

if(strcmp(argv[1],"-s") ==0){


exit(0);
}
}
