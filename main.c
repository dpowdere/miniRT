#include <stdio.h>

int main()
{
	int i = 1;

	printf("%d\n", *(char *)&i);
	return 0;
}
