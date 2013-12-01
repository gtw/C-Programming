#include<stdio.h>
#include<stdlib.h>


void alias(void **p1, void *p2);

int main(int argc, char * argv[]){

	int *p1 , *p2;
	int look_an_address_in_mem = 42;
	
	p2 = &look_an_address_in_mem;

	printf("P1 Before: %p\nP2 Before: %p\n", (void*)p1, (void*)p2);

	alias((void*)&p1,p2);

	printf("P1 After: %p\nP2 After: %p\n", (void*)p1, (void*)p2);
	
	return 0;
}

void alias(void **p1, void *p2){

	*p1 = p2;

}
