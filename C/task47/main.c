#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>

int main(int argc, char* argv[]){

int a[2];
if (pipe(a) == -1){
	err(1, "cant pipe");
}

pid_t pid = fork();

if(pid == -1){
	err(2,"cant fork");
}

if(pid == 0){
	close(a[0]);
	if(dup2(a[1],1) == -1){
		err(4,"cant dup");
	}
	if(execlp("find","find", "-type", "f", "-printf", "%T@ %P\n",char*(NULL)) == -1){
		err(3,"cant exec find");
	} 
}

close(a[1]);

int b[2];
if(pipe(b) == -1){
	err(1,"cant pipe");
}

pid_t pid2 = fork();

if(pid2 == -1){
	err(2,"cant fork");
}

if(pid2==0){
	close(b[0]);
	if(dup2(b[1],1) == -1){
		err(4,"cant dup");
	}
	if(dup2(a[0],0)==-1){
		err(4,"cant dup");
	}
	if(execlp("sort","sort", "-rn", char*(NULL)) == -1){
		err(5,"cant exec sort");
	}
}

close(b[1]);
if(dup2(b[0],0) == -1){
        err(4,"cant dup");
}
if(execlp("head","head", "-n1" ,char*(NULL)) == -1){
	err(6,"cant exec head");
}

close(b[0]);

exit(0);
}
