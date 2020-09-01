

int main(int argc, char **argv) {
	if(argc !=2) {
		errx(1,"Invalid number of arguments");
	}

	char *file = argv[1];
	struct stat st;
	
	if(stat(file,&st) == -1) {
		errx(2, "could not stat file %s", file);
	}

	if(!(st.st_mode & S_IREAD) || !(st.st_mode & S_IWRITE)){
		errx(3, "file %s not readable or not writable", file);
	}

	uint64_t counting[256] = { 0 };
	uint16_t level[256];
	for(uint16_t i = 0; i < 256; i++){
		level[j]=1;
	}

	ssize_t fd = open(file, 0_RDWR);
	if(fd == -1){
		err(4,"error while opening file %s", file);
	}
	
	ssize_t read_sz;
	uint8_t b;

	if(read_sz == -1){
                const int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(5, "error whiler reading file %s", file);
        }
	
	while((read_sz = read(fd, &b, sizeof(b))) == sizeof(b)){
		counting[b]++;
		if(counting[b] == UINT64_MAX){
			counting[b] = 0;
			level[b]++;
		}
	}

	if(lseek(fd, 0, SEEK_SET) == -1){
		const int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(6, "error while lseek file %s", file);
	}
	
	uint16_t i = 0;
		
	for(; i < 256; i++){
		while(level[i]--){
			b = i;
			while(counting[i]--){
				if(write(fd, &b, sizeof(b)) != sizeof(b)){
					const int olderrno = errno;
					close(fd);
					errno = olderrno;
					err(7, "error while writing into file %s", file);
				}
			}
			counting[i] = UINT64_MAX;
		}
	}

	close(fd);
	exit(0);
}
