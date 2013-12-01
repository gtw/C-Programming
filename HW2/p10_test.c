#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){

	char a[20] = "SHORT";
	float f1;
	char b[20] = "LONGLONGLONG";
	float f2;

	char a2[6] = "short";
	float f3;
	char b2[20] = "longlonglong";
	float f4;

	printf("%s\n", strncpy(a,b,6));
	printf("%s\n", a);
	printf("%s\n", strncpy(a2,b2,7));
	printf("%s\n", a2);

	return 0;
}
