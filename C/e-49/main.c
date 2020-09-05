#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>

int main(int argc, char** argv) {

if(argc != 2){
}

const char *file = argv[1];
const ssize_t fd_check = open(file, O_RDONLY);
if(fd_check == -1){
}

close(fd_check);

int a[2];
if(pipe(a) == -1){
}

const pid_t child_cat = fork();
if (child_cat == -1){
}
if(child_cat == 0){
	if(dup2(a[1], 1) == -1)
		err(5, "could not dup2");


	if(execl("/bin/cat","cat",file,  (char*)NULL) == -1){
	}
}
close(a[1]);

if(dup2(a[0], 0) == -1){
}

if(execlp("sort", "pesho_sort", (char *)NULL) == -1){
}

exit(0);
}
