#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double NR( double x0, void (*test_function)( double x, double * f, double * f_prime ), double precision);

double NR( double x0, void (*test_function)( double x, double * f, double * f_prime), double precision){

	int iter = 0;
	double x_new = x0;
	double x_old = x0;
	double f, f_prime;

	while(iter < 10000){
		x_old = x_new;
		test_function( x_new, &f , &f_prime );
		x_new = x_new - ((1.0/f_prime)*f);
		if( fabs(x_old - x_new) < precision/2.0 ){
			return x_new;
		}
		else
			iter++;
	}
	printf("NO ROOT FOUND\n");
	return -1;
	
}
