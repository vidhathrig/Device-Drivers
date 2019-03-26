#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE "/dev/new_dev"

int main()
{
	int i,fd;
	char ch, write_buf[100],read_buf[100];
	fd = open(DEVICE,O_RDWR);

	if(fd==-1)
	{
		printf("File does not exist or has been locked by other process\n");
		exit(-1);
	}

	printf("Enter command: r-read from device w- write to device\n");
	scanf(" %c",&ch);

	switch(ch)
	{
		case 'w':
			printf("Enter data\n");
			scanf(" %[^\n]",write_buf);
			write(fd,write_buf,sizeof(write_buf));
			break;

		case 'r':
			read(fd,read_buf,sizeof(read_buf));
			printf("%s\n",read_buf);
			break;
	}

	close(fd);

	return 0;
}