#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(int argc, char *argv[]){

	struct tm due_date;
	due_date.tm_sec = 0;
	due_date.tm_min = 0;
	due_date.tm_hour = 17;
	due_date.tm_mday = 9;
	due_date.tm_mon = 11;
	due_date.tm_year = 113;
	due_date.tm_wday = 1;

	printf("%s", asctime(&due_date));

	return 0;
}
