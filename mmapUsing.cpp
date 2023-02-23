#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i=1;
	char *str=NULL;
	printf("hello,world!\n");
	str=(char *)malloc(sizeof(char)*1119);

	sleep(1000);

	return 0;
}