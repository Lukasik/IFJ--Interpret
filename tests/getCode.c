#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char*argv[])
{
	char* start=strchr(argv[1], '-')+1;
	char* end=strchr(argv[1], '.');

	while(start != end) putchar(*start++);
}
