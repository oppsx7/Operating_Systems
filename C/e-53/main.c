#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

void execute(char *args[],int a[]) {
	
	if(pipe(a) == -1){
		err(1,"Could not pipe");
	}

	const pid_t child = fork();
	if(child == -1){
		err(2, "couldnt fork");
	}
	
	if(child == 0){
		close(a[0]);
		if(dup2(a[1],1) == -1){
			err(3, "Could not dup2");
		}

		if(execvp(args[0], args) == -1){
			err(4, "could not execute command %s",args[0]);
		}
	}

}
int main(int argc, char **argv) {
	if(argc !=2){
		//err
	}

	char *cmd1[] = { "find",argv[1], "-type", "f", "-printf", "%T@:%p" };
	char *cmd2[] = { "sort", "-nr" };
	char *cmd3[] = { "head", "-1" };
	char *cmd4[] = { "cut", "-d:", "-f2" };
	int a[2], b[2], c[2];
	if(pipe(a) == -1 || pipe(b) == -1 || pipe(c) == -1)
		//err
	execute(cmd1, &a);
	close(a[1]);
	execute(cmd2,&b);
	close(b[1]);
	execute(cmd3,&c);
	close(c[1]);
	
	if(execvp(cmd4[0], cmd4) == -1)
		//err

exit(0);
}
