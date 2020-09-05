#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char ** argv){
if(argc != 3){
	err(1,"wrong number of args");
}

char *input = argv[1], *output = argv[2];
struct stat st;

if(stat(input, &st) == -1)
	err(2, "cant stat file %s", input);

if(st.st_size != sizeof(uint16_t))
	errx(3, "size not uint16_t");

if(st.st_mode & S_IREAD)
	err(4, "file %s not readable", output);

ssize_t fd = open(input, O_RDONLY);
if(fd == -1)
	err(5, "cant open file %s", input);

ssize_t out = open(output, O_CREAT | O_TRUNC | O_RDWR, 0644);
if(out == -1)
	err(6, "cant create file %s", output);

int counting[0xfff + 1] = { 0 };
ssize_t rd = -1;
uint16_t buf;
while((rd = read(fd, &buf, sizeof(buf))) > 0) {
	uint32_t tempBuf = (uint32_t)(&buf);
		counting[tempBuf]++;
}
for(uint32_t i = 0; i<= 0xffff; i++){
	while(counting[i]--){
		buf = (uint16_t)(i);
		if(write(out, &buf, sizeof(buf)) != sizeof(uint16_t)){
			const int olderrno = errno;
			close(fd);
			close(out);
			errno = olderrno;
			err(8, "couldnot write to file %s", out);
		}
	}
}

close(fd);
close(out);
exit(0);
}

	

