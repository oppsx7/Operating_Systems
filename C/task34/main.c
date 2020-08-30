#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
int main(int argc, char* argv[]){

int fd1 = open(argv[1], O_RDONLY);
int fd2 = open(argv[2], O_RDONLY);
int fd3 = open(argv[3], O_CREAT | O_TRUNC | O_WRONLY, 0644 );
int fd4 = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644 );

struct triple {
	uint16_t offset;
	uint8_t length;
	uint8_t trash;
}__attribute__((packed)) w;

struct triple w1 = { 0, 0, 0};
uint8_t letter;
uint16_t counter=0;
while(read(fd2, &w, sizeof(w))){ //CHECK
	uint8_t buff[w.length];
	if(lseek(fd1, w.offset, SEEK_SET) == -1){
		err(1, "lseek failed");
	}
	read(fd1, &buff, w.length); //CHECK
	if(buff[0] >= 'A' && buff[0] <= 'Z'){
		write(fd3, &buff, w.length); //CHECK
		w.offset = counter;
		write(fd4, &w, sizeof(w)); //CHECK 	
		counter += w.length;
	}
	
}

}

