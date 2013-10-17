#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int input = atoi(argv[1]);
	int a = 255;
	int b = a<<8;
	int c = a<<16;
	int d = a<<24;
	int final = ((input&a)<<24)|((input&b)<<8)|((input&c)>>8)|((input&d)>>24);
	printf("%d\n",final);

	return 0;
}
