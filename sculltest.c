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
    printf("fd = %d\n",fd);
    str = "abcde";
    len = strlen(str);
    printf("len = %d\n",len);
    if ((result = write (fd, str, len)) != len)
    {
        perror("write failed");
        return -1;
    }
    printf("written bytes are = %d\n",result);
    close(fd);
    if ((fd = open ("/dev/scull", O_RDONLY)) == -1)
    {
        perror("open failed");
        return -1;
    }
    printf("fd = %d\n",fd);
    if ((result = read (fd, &buf, sizeof(buf))) != len)
    {
        perror("read failed");
        return -1;
    }
    printf("read bytes are = %d\n",result);
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
    
    return 0;
}
