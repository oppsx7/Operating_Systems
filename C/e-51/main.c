#include <unistd.h>
#include <err.h>

int main(int argc, char **argv){

int a[2];

if(pipe(a) == -1) {
	err(1, "couldnt pipe");
}

const pid_t child = fork();

if(child == -1){
	err(2, "couldnt fork");
}

if(child == 0 ){
	close(a[0]);
	if(dup2(a[1],1) == -1){
		err(3, "cant dup2");
	}

	if(execlp("cut","cut", "-d:", "-f7", "/private/etc/passwd", (char*)NULL) == -1)
	err(4, "couldnt execlp");
}

close(a[1]);

int b[2];

if(pipe(b) == -1)
	err(5, "could not pipe");

const pid_t child_sort = fork();

if(child_sort == -1)
	err(6,"couldnt fork");
if(child_sort == 0){
	close(b[0]);
	if(dup2(b[1],1) == -1)
		err(7,"couldnt dup2");



exit(0);
}
