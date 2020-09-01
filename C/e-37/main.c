#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>
#include <errno.h>

int cmp(const void *a, const void *b){
	if( *((uint32_t*)a) > *((uint32_t*)b) ){
		return 1;
	} else if ( *((uint32_t*)a) < *((uint32_t*)b) ){
		return -1;
	return 0;
}


int main(int argc, char **argv){
	if(argc != 3){
		errx(1, "Invalid number of arguments");
	}

	char *bin = argv[1];
	char *sorted = argv[2];

	struct stat st;
	if(stat(bin, &st) == -1){
		errx(2, "error while stat %s", bin);
	}
	
	if(st.st_size %sizeof(uint32_t) != 0){
		errx(3, "file %s is corrupted", bin);
	}

	uint32_t numel = st.st_size / sizeof(uint32_t);

	printf("total uint32_t elements: %u\n", numel);

	uint32_t half = numel/2;
	uint32_t *p = malloc(half * sizeof(uint32_t));
	if(!p){
		err(4, "not enough memory");
	}

	ssize_t fd1 = open(bin, O_RDONLY);
	if(fd1 == -1){
		const int olderrno = errno;
		free(p);
		errno = olderrno;
		err(5, "error while opening file %s", bin);
	}

	ssize_t t1 = open("temp1", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(t1 == -1){
		const int olderrno = errno;
		free(p);
		close(fd1);
		errno = olderrno;
		err(6, "error while opening file temp1");
	}

	ssize_t res = read(fd1, p, half * sizeof(uint32_t));
	if(res != half * sizeof(uint32_t)){
		const int olderrno = errno;
		free(p);
		close(fd1);
		close(t1);
		errno = olderrno;
		err(7, "error while reading file %s", bin);
	}

	qsort(p, half, sizeof(uint32_t), cmp);
	
	res = write(t1, p, half * sizeof(uint32_t));
	if(res != half * sizeof(uint32_t)){
		const int olderrno = errno;
		free(p);
		close(fd1);
		close(t1);
		errno = olderrno;
		err(8, "error while writing to file temp1");
	}
	
	free(p);

	uint32_t rhalf = numel-half;
	
	uint32_t *rp = malloc(rhalf * sizeof(uint32_t));

	if (!rp){
		const int olderrno = errno;
		close(fd1);
		close(t1);
		errno = olderrno;
		err(9, "not enough memory");
	}

	ssize_t t2 = open("temp2", O_CREAT | O_RDWR | O_TRUNC, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);// same as 0644
	if(t2 == -1){
		const int olderrno = errno;
		close(fd1);
		close(t1);
		free(rp);
		errno = olderrno;
		err(10, "error while opening file temp2");
	}

	res = read(fd1, rp, rhalf * sizeof(uint32_t));
	if(res != (ssize_t)(rhalf * sizeof(uint32_t))){
		const int olderrno = errno;
		close(fd1);
		close(t1);
		close(t2);		
		free(rp);
		errno = olderrno;
		err(11, "error while reading file %s", bin);
	}

	qsort(rp, rhalf, sizeof(uint32_t), cmp);

	res = write(t2, rp, rhalf * sizeof(uint32_t));
	if(res != (ssize_t)(rhalf * sizeof(uint32_t))){
		const int olderrno = errno;
		close(fd1);
		close(t1);
		close(t2);
		free(rp);
		errno = olderrno;
		err(12, "error while writing to file temp2");
	}
	
	free(rp);
	close(fd1);

	lseek(t1, 0, SEEK_SET);//check lseek
	lseek(t2, 0, SEEK_SET);//check lseek

	ssize_t fd2 = open(sorted, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if(fd2 == -1){
		const int olderrno = errno;
		close(t1);
		close(t2);
		errno = olderrno;
		err(13, "error while opening file %s", sorted);
	}

	uint32_t a, b;
	size_t d1 = 0, d2 = 0 , d3 = 0;

	ssize_t rd1 = -1, rd2 = -1;
	while(((rd1 = read(t1, &a, sizeof(a))) == sizeof(a)) && ((rd2 = read(t2, &b, sizeof(b))) == sizeof(b))) {
		if(a <= b) {
			write(fd2, &a, sizeof(a));//check write	
			lseek(t2, -1 * sizeof(b), SEEK_CUR);
		} else {
			write(fd2, &b, sizeof(b));//check write
			lseek(t1, -1 *sizeof(a), SEEK_CUR);
		}
		d1++;
	}

	if (rd1 == -1 sizeof(a)){
		write(fd2, &a, sizeof(a));
		d2++;
	}

	if(rd1 == -1 || rd2 == -1){
		const int olderrno = errno;
		close(t1);
		close(t2);
		close(fd2);
		errno = olderrno;
		err(14, "error while reading from temp files");
	}

	printf("combined write: %ld\n", d1);

	while ((rd1 =read(t1, &a, sizeof(a))) == sizeof(a)) {
		write(fd2, &a, sizeof(a)); //check write
		d2++;
	}

	if (rd1 == -1) {
		const int olderrno = errno;
                close(t1);
                close(t2);
                close(fd2);
                errno = olderrno;
                err(15, "error while reading from temp files");
	}

	printf("left A write: %ld\n", d2);

	while ((rd2 = read(t2, &b, sizeof(b))) == sizeof(b)){
		write(fd2, &b, sizeof(b));
		d3++;
	}
	if (rd2 == -1){
		const int olderrno = errno;
                close(t1);
                close(t2);
                close(fd2);
                errno = olderrno;
                err(16, "error while reading from temp files");
	}
	
	printf("left B write: %ld\n", d3);

	unlink("temp1"); //check unlink
	unlink("temp2"); //check unlink

	close(t1);
	close(t2);
	close(fd2);
	exit(0);
}


