#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char** argv){

char* duration = argv[1];
if(duration[1] != '\0'){
err(1, "Input an integer between 0-9");
}
int sec = duration[0];
char *args[12];
int counter = 0;
int i = 2;
for(;i<argc;i++){
	args[counter++] = argv[i];
}

args[counter]= NULL; 
char *log = "run.log";

ssize_t fd_log = open(log, O_CREAT | O_TRUNC | O_RDWR, 0644);
if(fd_log == -1){
	err(2, "cant open logfile");
}

int condcounter = 0;
while(condcounter != 2){
time_t start;
const pid_t child = fork();

if(child == -1){
	err(3, "cant fork");
}

if(child == 0){
	time_t tempStart = time(NULL);
	start = tempStart;
	write(fd_log, start, sizeof(start));
	write(fd_log, " ", 2);
	execvp(args[0], args);
}
int status;
wait(&status);

int execstatus;
if(WIFEXITED(status)){
	execstatus = WEXITSTATUS(status);
} else {
execstatus = 1;
}
time_t end = time(NULL);
write(fd_log,end, sizeof(end));
write(fd_log, " ", 2);
write(fd_log, execstatus, sizeof(execstatus));
write(fd_log, "\n", 3);
int difference = start - end;
if(execstatus != 0 && difference < sec){
	condcounter++;
} else {
	condcounter = 0;
}
}
exit(0);
}
