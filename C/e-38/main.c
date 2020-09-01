#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>

void clo(ssize_t fd1, ssize_t fd2, ssize_t fd3, ssize_t fd4,const int olderrno ){
	if(fd1 != -1) close(fd1);
	if(fd2 != -1) close(fd2);
	if(fd3 != -1) close(fd3);
	if(fd4 != -1) close(fd4);
	errno = olderrno;
}

int main(int argc, char **argv){
if(argc != 5) {
	errx(1,"Wrong number of arguments");
}

char *dat1 = argv[1], *idx1 = argv[2], *dat2 = argv[3], *idx2 = argv[4];

struct stat st;
if(stat(idx1, &st) == -1)
	errx(2, "error while stat file %s", idx1);

struct triple{
	uint16_t displacement;
	uint8_t len;
	uint8_t free;
}__attribute__((packed)) fmt1, fmt2;

if(!(st.st_mode & S_IREAD))
	errx(3, "file %s is not readable", idx1);

if((st.st_size %sizeof(fmt1)) == 0)
	errx(4, "file %s is corrupted", idx1);

ssize_t fd1 = open(dat1, O_RDONLY);
if(fd1 == -1)
	errx(5, "error while opening file %s", dat1);

ssize_t fd2 = open (idx1, O_RDONLY);
if(fd2 == -1){
	clo(fd1, -1, -1, -1, errno);
	err(6, "error while opening file %s", idx1);
}

ssize_t fd3 = open(dat2, O_CREAT | O_RDWR | O_TRUNC, 0644);
if(fd3 == -1){
	clo(fd1, fd2 , -1, -1, errno);
	err(7, "error while opening file %s", dat2);
}
ssize_t fd4 = open(idx2, O_CREAT | O_RDWR | O_TRUNC, 0644);
if(fd4 == -1){
	clo(fd1, fd2, fd3, -1, errno);
	err(8, "error while opening file %s", idx2);
}

fmt2.displacement = 0;
fmt2.len = 0;
fmt2.free = 0;

ssize_t rd2 = -1, rd1 = -1;
while((rd2 = read(fd2, &fmt1, sizeof(fmt1))) == sizeof(fmt1)){
	uint16_t d = fmt1.displacement;
	uint8_t l = fmt1.len;
	
	off_t ls = lseek(fd1, d, SEEK_SET);
	if(ls == -1){
		clo(fd1, fd2, fd3, fd4, errno);
		err(9, "error while lseek file %s", dat1);
	}
	char buf;
	uint8_t cnt = 0, flag_Capital = 0;
	while((rd1 = read(fd1, &buf, sizeof(buf))) == sizeof(buf)){
		cnt++;
		if(flag_Capital == 0){
			if(buf > 'Z' || buf < 'A'){
				break;
			} else {
				flag_Capital = 1;
			}
		}
		ssize_t wr1 = write(fd3, &buf, sizeof(buf));
		if(wr1 == -1){
			clo(fd1, fd2, fd3, fd4, errno);
			err(10,"error while writing into file %s", dat2);
		}
		if(cnt ==l) break;
	}
	if(flag_Capital){

		fmt2.len = l;
		
		ssize_t wr2 = write(fd4, &fmt2, sizeof(fmt2));
		if(wr2 == -1){
			clo(fd1, fd2, fd3, fd4, errno);
			err(11, "error while writing into file %s", idx2);
		}
		fmt2.displacement = fmt2.displacement + l;
	}
}
if(rd2 == -1){
	clo(fd1, fd2, fd3, fd4, errno);
	err(12, "error while reading from file %s", dat1);
}
clo(fd1, fd2, fd3, fd4, 0);
exit(0);
}
