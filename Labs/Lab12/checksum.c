#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("Usage: <%s> <filename>", argv[0]);
		return -1;
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd < 0) {
		printf("%s: %s: No such file or directory", argv[0], argv[2]);
		return -1;
	}

	unsigned char buffer[512];
	unsigned int sum = 0;
	int total = 0;
	int i;

	while ((total += read(fd, buffer, sizeof(buffer))) == 512)  
		for (i = 0; i < 512; i++)
			sum += buffer[i];
	
	unsigned int blocks = (total / 512) + (total % 512 > 0);	

	unsigned int shift = 1 << 16;

	unsigned int r = (sum % shift) + (sum / shift);
	unsigned int s = (r % shift) + (r / shift);
	
	printf("%u %u %s\n", s, blocks, argv[1]);

	close(fd);
 
	return 0;
}
