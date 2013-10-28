#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){

	char *p;
	printf("p is located at %p\n",(void*)p);
	p = "hello world";
	printf("p is located at %p\n%s\nAddress of the first char is %p\nFirst Char is %c\nSize of first char is %d\n",(void*)p,p,(void*)&p[0],p[0],sizeof(p[0]));
	p[0] = 'p';
/*	printf("%s\n",p);
*/	return 0;
}
