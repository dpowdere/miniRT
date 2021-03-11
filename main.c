#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	extern int errno;

	errno = 0;
	perror("miniRT");
	open("asldkfjlaksjdfla", 0);
	printf("strerror:: %s\n", strerror(errno));
	perror("miniRT");
	printf("strerror:: %s\n", strerror(errno));
	return 0;
}
