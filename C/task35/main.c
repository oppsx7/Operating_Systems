#include <err.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc, char* argv[]){

if( argc != 4 ){
	errx(1,"invalid arg number");
}
int fd1 = open(argv[1], O_RDONLY, 0644);
if(fd1 == -1){
	const int olderrno = errno;
	close(fd1);
	errno = olderrno;
	err(2,"cant open");
}

int fd2 = open (argv[2], O_RDONLY, 0644);
if(fd2 == -1){
	const int olderrno = errno;
	close(fd2);
	errno = olderrno;
	err(2,"cant open");
}

struct stat st;

off_t f1_size = st.st_size;

if(stat(fd1, &st) == -1 || stat(fd2, &st) == -1){
	err(3,"cant stat");
}

if(f1_size != st.st_size){
	err(4,"files are different size");
}

struct triple{
	uint16_t offset;
	uint8_t old;
	uint8_t new;
}__attribute__((packed)) t;

int patch = open(argv[3], O_CREAT | O_TRUNC | O_RDWR, 0644);
if(patch == -1){
	const int olderrno = errno;
        close(patch);
        errno = olderrno;
        err(2,"cant open"); 
}

uint8_t a;
uint8_t b;
int rd1 = -1;
int rd2 = -1;
int counter = 0;
while(rd1 == read(fd1, &a, sizeof(a)) > 0  && rd2 == read(fd2, &b, sizeof(b) > 0 )){
	if(a!=b){
		t.offset = counter;
		t.old = a;
		t.new = b;
		if(write(patch, &t, sizeof(t)) == -1){
			const int olderrno = errno;
        		close(patch);
        		errno = olderrno;
        		err(5,"cant write");
		}
	}
	counter++;
}

if(rd1 == -1){
	const int olderrno = errno;
        close(rd1);
        errno = olderrno;
        err(6,"cant read");
}

if(rd2 == -1){
	const int olderrno = errno;
	close(rd2);
	errno = olderrno;
	err(6,"cant read");
}
close(fd1);
close(fd2);
close(patch);

exit(0);
}
