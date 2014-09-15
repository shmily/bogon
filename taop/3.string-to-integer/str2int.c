
#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN 32

int main(void)
{
	printf("max int: %d %x\n", (int)((unsigned)~0 >> 1), (int)((unsigned)~0 >> 1));

	int min_int = ((unsigned)~0 >> 1) - 1;

	printf("min int: %d %x, %d %x\n", min_int, min_int, (0-min_int), (unsigned)(0-min_int));
}
