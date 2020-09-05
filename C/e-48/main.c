#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

void writer(ssize_t &descriptor, uint32_t length){
	ssize_t rd_f1 = -1;
      	off_t ls = lseek(fd1, octet.d1, SEEK_SET);
        //check lseek
	uint32_t b;
	if((rd_f1 = read(fd1, b, sizeof(octet.l1))) == -1){
                //close everything
        }
        write(fd6, b, sizeof(b));

}
int main (int argc, char ** argv) {

if (argc != 7) {
	err(1,"Wrong number of arguments");
}

char * source = argv[1], *f1 = argv[2], *f2 = argv[3], *f3 = argv[4], *f4 = argv[5], *container = argv[6];

struct stat st1, st2, st3, st4, st5;
if(stat(source, &st1) == -1 || stat(f1, &st2) == -1 || stat(f2, &st3) == -1 || stat(f3, &st4) == -1 || stat(f4,&st5) == -1){
	err(2, "Cant stat");
}
if(st1.st_size % sizeof(uint16_t) != 0){
	err(3, "Wrong size of file %s", source);
}
if(st2.st_size % sizeof(uint32_t) != 0) {
	err(4, "Wrong size of file %s", f1);
}
if(st3.st_size % sizeof(uint8_t) != 0) {
	err(5, "wrong size of file %s", f2);
}
if(st4.st_size % sizeof(uint16_t) != 0) {
	err(6, "wrong size of ifle %s", f3);
}
if(st5.st_size % sizeof(uint64_t) != 0) {
	err(7, "wrong size of file %s", f4);
}
if((st1.st_mode & S_IREAD)) // others aswell
	err(8, "File not readable");

ssize_t fd1 = open(source, O_RDONLY);
ssize_t fd2 = open(f1, O_RDONLY);
ssize_t fd3 = open(f2, O_RDONLY);
ssize_t fd4 = open(f3, O_RDONLY);
ssize_t fd5 = open(f4, O_RDONLY);
ssize_t fd6 = open(container, O_CREAT | O_TRUNC | O_RDWR, 0644);

struct octal {
	uint32_t d1;
	uint32_t l1;
	uint32_t d2;
        uint32_t l2;
	uint32_t d3;
        uint32_t l3;
	uint32_t d4;
        uint32_t l4;
}__attribute__((packed)) octet;

ssize_t reader;
uint16_t buf;
if((reader = read(fd1,buf, sizeof(buf))) == -1) {
	const int olderrno = errno;
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
	close(fd6);
	errno = olderrno;
	err(9, "Cant read sourcefile");
}
ssize_t rd = -1;
while((rd = read(fd1, octet, sizeof(octet))) > 0) {
	ssize_t rd_f1 = -1;
	off_t ls = lseek(fd1, octet.d1, SEEK_SET);
	//check lseek
	uint32_t b;
	writer(fd1, octet.d1, 
