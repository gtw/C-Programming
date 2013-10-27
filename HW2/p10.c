#include<stdio.h>
#include<stdlib.h>

int  my_strncmp(char *a, char *b, int n);
char *my_strncat(char *dest, char *src, int n);
char *my_strncpy(char *dest, char *src, int n);
char *my_strcat(char *a, char *b);

int main(void)
{
	char * A = "Hello!";
	char * B = "Hello from Chicago";
	char * C = " Excellent. Perfect.";

	char result[1024] = "Hi ";

	printf("Test 1: ");
	printf("%s\n", my_strcat(result, A));

	printf("Test 2: ");
	printf("%s\n", my_strncpy(result, B, 2));

	printf("Test 3: ");
	printf("%s\n", my_strncpy(result, B, 100));

	printf("Test 4: ");
	printf("%s\n", my_strncat(result, C, 10));
	
	printf("Test 5: ");
	printf("%d\n", my_strncmp(A, B, 5));

	printf("Test 6: ");
	printf("%d\n", my_strncmp(A, B, 10));
	
	return 0;

}

int my_strncmp(char *a, char *b, int n){

	int i = 0;

	while(i<n){
		if(*a == *b && *a != '\0'){
			a++;
			b++;
			i++;
		}
		else if(*a == *b && *a == '\0'){
			return 0;
		}
		else if(*a == '\0'){
			return -1;
		}
		else if(*b == '\0'){
			return 1;
		}
		else if(*a > *b){
			return 1;
		}
		else if(*a < *b){
			return -1;
		}
	}
	
	return 0;
	
}

char *my_strncat(char *dest, char *src, int n){

	int i = 0;
	char *dest_cp = dest;

	while(*dest != '\0'){
		dest++;
	}

	while(i< n && *src != '\0'){
		*dest++ = *src++;
		i++;
	}

	if(i < n && *src == '\0'){

		*dest = '\0';

	}

	return dest_cp;
}

char *my_strncpy(char *dest, char *src, int n){

	int i = 0;
	char *dest_cp =dest;

	while(*src != '\0' && i < n){
		*dest++ = *src++;
		i++;
	}

	if(i < n && *src == '\0'){
		*dest = '\0';
	}

	return dest_cp;

}

char *my_strcat(char *a, char *b){

	char *a_cp = a;

	while(*a != '\0')
		a++;

	while(*b != '\0'){
		*a++ = *b++;
	}

	*a = '\0';
	
	return a_cp;

}
