/* sculltest.c
* A simple example of a C program to test some of the
* operations of the "/dev/scull" device (a.k.a "scull0"),
* and the 
*/
 
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int main() 
{
	int fd, result, len;
	char buf[10];
	const char *str;
	if ((fd = open ("/dev/scull", O_WRONLY)) == -1) 
	{
		perror("open failed");
		return -1;
	}
	str = "abcde"; 
	len = strlen(str);
	if ((result = write (fd, str, len)) != len)
	{
		perror("write failed");
		return -1;
	}
	close(fd);
	if ((result = read (fd, &buf, sizeof(buf))) != len) 
	{
		perror("read failed");
		return -1;
	} 
	buf[result] = '\0';
	if (strncmp (buf, str, len)) 
	{
		fprintf (stdout, "failed: read back \"%s\"\n", buf);
	}
	else 
	{
		fprintf (stdout, "passed\n");
	}
	close(fd);
	
/*	str = "xyz"; 
	len = strlen(str);
	if ((fd = open ("/dev/scullpipe", O_RDWR)) == -1) 
	{
		perror("open failed");
		return -1;
	}
	if ((result = write (fd, str, len)) != len) 
	{
		perror("write failed");
		return -1;
	}
	if ((result = read (fd, &buf, sizeof(buf))) != len) 
	{
		perror("read failed");
		return -1;
	}
	buf[result] = '\0';
	if (strncmp (buf, str, len)) 
	{
		fprintf (stdout, "failed: read back \"%s\"\n", buf);
	} 
	else 
	{
		fprintf (stdout, "passed\n");
	}
	close(fd);	*/
	return 0;
}

