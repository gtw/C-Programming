#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int my_memcpy(void *target, void *source, size_t nbytes);

int main(int argc, char * argv[])
{
	char test1[40] = "A rather long string";
	char * test2 = &test1[3];
	char test3[40];

	int res;

	res = my_memcpy( test2, test1, strlen(test1) + 1 );
	printf("test 1 return status: %d\n", res);
	
	res = my_memcpy( test1, test2, strlen(test2) + 1 );
	printf("test 2 return status: %d\n", res);
	
	res = my_memcpy( test3, test1, strlen(test1) + 1 );
	printf("test 3 return status: %d\n", res);

	if( strcmp(test1, test3) == 0 )
		printf("test 4 was a success\n");
	
	return 0;

}

int my_memcpy(void *target, void *source, size_t nbytes)
{
	unsigned long tar		= (unsigned long)target;
	unsigned long src		= (unsigned long)source;
	char *c_target			= (char*)target;
	char *c_source 			= (char*)source;
	int  i 				= 0;
	
	if((tar <= src && tar + nbytes >= src)||
		(src <= tar && src + nbytes >= tar )){
		
		return -1;
		
	}
	
	else{
	
		for(i=0;i<nbytes;i++){
			*(c_target++)=*(c_source++);
		}
	}
	
	return 0;
}
