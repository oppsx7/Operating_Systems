#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char ** argv){

if(argc != 4) {
	err(1,"Wrong number of args");
}

char *patch = argv[1], *input = argv[2], *output = argv[3];
struct stat st1, st2;

if((stat(patch,&st1) == -1) || (stat(input,&st2) == -1))
{
	err(2,"cant stat");
}
if(!(st1.st_mode & S_IRUSR) || !(st2.st_mode & S_IRUSR))
{
	err(3,"not readable");
}
ssize_t fd1 = open(patch,O_RDONLY);
ssize_t fd2 = open(input,O_RDONLY);
ssize_t fd3 = open(output,O_CREAT | O_TRUNC | O_RDWR, 0644);

struct header{
	uint32_t magic;
	uint8_t version;
	uint8_t data_ver;
	uint16_t count;
	uint32_t res1;
	uint32_t res2;
}__attribute__((packed)) head;

struct h1{
        uint16_t offset;
        uint8_t old;
	uint8_t new;
}__attribute__((packed)) v1;

struct h2{
        uint32_t offset;
        uint16_t old;
	uint16_t new;
}__attribute__((packed)) v2;

char c;
while((read(fd2,&c,sizeof(c))))
{
	ssize_t wr = write(fd3,c,sizeof(c));
}


ssize_t rd = read(fd1,&head,sizeof(head));
if(head.data_ver == 0x00)
{
	if(st1.st_size % (sizeof(head) + sizeof(v1)) != 0)
		err(4,"wrong size");
	
	while((rd=read(fd1,&v1,sizeof(v1))) == sizeof(v1))
	{
		off_t ls = lseek(fd3,v1.offset,SEEK_SET);
		ssize_t rd_2;
		char b;
		if((rd_2 = read(fd3, &b, 1)) == 1){
			if(v1.old == b){
			ls = lseek(fd3, v1.offset, SEEK_SET);
			write(fd3,v1.new,sizeof(v1.new));
			}
		}
	}
} else
{
	if(st1.st_size % (sizeof(head) + sizeof(v2)) != 0)
                err(4,"wrong size");

        while((rd=read(fd1,&v2,sizeof(v2))) == sizeof(v2))
        {
                off_t ls = lseek(fd3,v2.offset,SEEK_SET);
                ssize_t rd_2;
                char b;
                if((rd_2 = read(fd3, &b, 1)) == 1){
                        if(v2.old == b){
                        ls = lseek(fd3, v2.offset, SEEK_SET);
                        write(fd3,v2.new,sizeof(v2.new));
                        }
                }
        }
}

//close everything + check reads
exit(0);
}
