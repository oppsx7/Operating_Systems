#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){

char *cmd;
if(argc == 2){
cmd = argv[1];
} else {
cmd = "echo";
}

if(strlen(cmd) > 4) {
	err(1, "string length must be 4 maximum");
}

ssize_t reader;
char sym;
int counter = 0;
int tempCounter = 0;
char **args;
char *argument = "";
memset(args[0],0,sizeof(args[0]));
memset(args[1],0,sizeof(args[1]));

args[1] = "";
while((reader = read(0, &sym, sizeof(sym))) != -1) {
	write(1, "watafak" + sym, sizeof(sym));
	if(sym == '\\' || sym == ' ') {
		if(sym == '\\')
			lseek(0, 1 ,SEEK_CUR); 
		if(counter > 4){
			err(1, "string length must be four atmost");
		}
		counter = 0;
		fprintf(stdout, argument);
		args[tempCounter] = argument;
		fprintf(stdout, args[0]);
		memset(argument, 0, sizeof(argument));
		tempCounter++;
		if(tempCounter == 2){
			const pid_t child = fork();
			if(child == -1){
				//err
			}
			
			if(child == 0){
				if(execlp(cmd, cmd,args[0], args[1], (char*)NULL) == -1){
					//err
				}
			}
			
			tempCounter = 0;
			args[0] = "";
			args[1] = "";
		}

	} else {
		write(1,"watafakk" + sym, sizeof(sym));
		strcat(argument, &sym);
		write(1, "bzamina\n", 10);
		counter++;
	}
}

if(args[0] != "") {
	execlp(cmd, cmd, args[0], (char*)NULL);
}

exit(0);
}
