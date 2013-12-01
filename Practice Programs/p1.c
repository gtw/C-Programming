#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

	int i;
	time_t current_time;
	time_t fake_time = 100000;
	for(i=0;i<10;i++){
		time_t current_time = time(NULL);
		printf("%s\n",ctime(&current_time));
	}

	printf("%d\n", gmtime(&fake_time)->tm_year);

	
	return 0;
}
