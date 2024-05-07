#include <stdio.h>
#include <math.h>
#include <time.h>

#include "function.h"
#include "helpers.h"

int main(int argc, char *argv[]) {
	
	double a = 0;
	double b = 4;
	unsigned long long int n = 3000000000;
	unsigned int chosen_algorithm = 0; //0 = rect, 1 = trap, 2 = para
	
	double result;
	struct timespec start_time;
	struct timespec end_time;
	double time_taken;
	
	clock_gettime(CLOCK_MONOTONIC, &start_time);
	
	if (chosen_algorithm == 2) {
		
		if (n % 2 == 0)
			result = approx_by_para(a, b, n, f);
		else {
			
			printf("Il numero di intervalli (n) non può essere dispari");
			return 0;
		}
	}	

	else if (chosen_algorithm) //if not 2 and true means 1 since it can't get any value above 2
		result = approx_by_trap(a, b, n, f);
		
	else //else it is 0
		result = approx_by_rect(a, b, n, f);
	
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	
	time_taken = calc_time_taken(&start_time, &end_time);
	
	printf("Risultato: %lf\n", result);
	printf("Tempo Impiegato: %lf s\n", time_taken);
	
	system("pause");
}
