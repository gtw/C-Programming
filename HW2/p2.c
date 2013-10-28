#include<math.h>
#include<stdlib.h>
#include<stdio.h>

void extrema(float *arr, int arr_size, float *mean, float *stdev);

int main(int argc, char *argv[]){

	int i;
	float 	f_stdev = 	0; 
	float 	f_mean = 	0;
	float 	*stdev = 	&f_stdev;
	float 	*mean =		&f_mean;
	
	float *f_array = (float*)malloc(sizeof(float)*(argc-1));
	
	for(i=0;i<argc-1;i++){
		f_array[i] = atof(argv[i+1]);
	}
	
	extrema(f_array, argc-1, mean, stdev);
	
	printf("Mean : %.2f\nStandard Deviation : %.2f\n", *mean, *stdev);
	
	return 0;
}
 
void extrema(float *arr, int arr_size, float *mean, float *stdev){

	int i;
	float variance = 0;

	/* I calculate variance and then take its sqrt to find stddev */
	/* reset mean and stdev to 0 in instances where they may already be populated*/

	*mean = 0.0;
	*stdev = 0.0;
	variance = 0.0;
	
	for(i=0;i<arr_size;i++){
		*mean+= arr[i];
	}

	/* I wait to divide by arr_size to limit the compounding
	of errors inherint to floating point arithmetic.  Waiting
	to do a single division should be more accurate */

	*mean = *mean/arr_size;
	
	for(i=0;i<arr_size;i++){
		variance+= ((arr[i]-*mean)*(arr[i]-*mean))/arr_size;
	}

	/* Taken from the math.h library. K&R appendix B explains
	that these functions are only defined for double, hence
	the cast to double and subsequent cast back to float */
	
	*stdev = (float)pow((double)variance,.5);
}
