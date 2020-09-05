#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv){
ssize_t rd;
char c; 
int counter = 0;
if (strcmp(argv[1],"-c") == 0){
	char *number = argv[2];
	if (strlen(number) == 1){
		while((rd = read(0,&c,sizeof(c)))  > 0){
			counter++;
			if(counter == atoi(number)) {
				fprintf(stdout, "%c\n", c);
			}
		}
	}else {
		int begin = number[0] - '0';
		int end = number[2] - '0';
		while((rd = read(0, &c, sizeof(c))) > 0) {
			counter++;
			if(counter >= begin && counter <= end){
				fprintf(stdout, "%c", c);
			}
		}
	}
} else if(strcmp(argv[1],"-d") == 0){
	char *str = argv[2];
	char delimiter = str[0];
	char *col = argv[4];
	counter = 1;
	if(strlen(col) == 1){
		while((rd = read(0, &c, sizeof(c))) > 0){
			if(c == delimiter) {
				counter++;
			}
			if(counter == atoi(col)) {
			fprintf(stdout, "%c", c);
			}
		}
	} else {
		int begin = col[0] - '0';
                int end = col[2] - '0';
		while((rd = read(0, &c, sizeof(c))) > 0) {
                        if(c == delimiter){
				counter++;
				fprintf(stdout, " ");
				continue;
			}
                        if(counter >= begin && counter <= end){
				fprintf(stdout, "%c", c);
                        }       
                } 
	}
}      
			
exit(0);
}	

