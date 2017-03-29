#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE "/dev/solidusedevice"

int main(void)
{
	int i ,fd;
	char ch, write_buf[100], read_buf[100];
	fd = open(DEVICE, O_RDWR);
	if(fd == -1)
	{
		printf("file either does not exist or has been locked by another process\n" );
		exit(-1);
	}
	printf("r = read from device\n, w = write to device\n enter command: ");
	scanf("%c", &ch);
	switch(ch)
	{
		case 'w':
			printf("enter data\n");
			scanf(" %[^\n]", write_buf);
			write(fd, write_buf, sizeof(write_buf));
			break;
		case 'r':
			read(fd, read_buf, sizeof(read_buf));
			printf("read %s\n", read_buf);
			break;
		default:
		break;
	}
	close(fd);
	return 0;
}
