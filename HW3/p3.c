#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void test_function( double x, double * f, double * f_prime );
double NR( double x0, void (*test_function)( double x, double * f, double * f_prime ), double precision);
void test_function( double x, double * f, double * f_prime );

int main(void)
{
	double x0 = -2.7e4;
	double precision = .0000001; 

	double root = NR( x0, test_function, precision );

	printf("%f\n", root);
	
	return 0;
}

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
			printf("X_New: %f X_Old: %f\n", x_new, x_old);
			return x_new;
		}
		else
			printf("X_New: %f X_Old: %f\n", x_new, x_old);
			iter++;
	}
	printf("NO ROOT FOUND\n");
	return -1;
	
}

void test_function( double x, double * f, double * f_prime) {
	
	*f = x*x*x;
	*f_prime = 3*x*x;
}
