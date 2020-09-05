#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
//void READ(int fd, const char* from, uint8_t numerate, uint16_t *cnt){
//	char c;
//	ssize_t read_sz;
//
//	int newline = 1;
//
//	while((read_sz = read(fd, &c, 1)) == 1){
//		if(numerate){
int main(int argc, char **argv) {

int counter = 0;
if( strcmp(argv[1], "-n") == 0 ) {
	counter = 1;
}
ssize_t i = counter + 1;

for(;i<argc; i++){
	char* file = argv[i];
	ssize_t fd = -1;

	fd = open(file,O_RDONLY);
	char a;
	ssize_t rd = -1;
	int newLine = 1;
	while((rd=read(fd, &a, sizeof(a))) == sizeof(a)){
		
		if(counter !=0){
			if(newLine){	
				setbuf(stdout, NULL);
				fprintf(stdout,"%d", counter); 
				counter++;
				newLine = 0;
			}  write(1, &a, 1);
		if(a == '\n') newLine = 1;
		} else write(1, &a, 1);

	}
}

exit(0);
}


