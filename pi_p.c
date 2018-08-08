#include <omp.h>
#include <stdio.h>
static long num_steps = 100000;
double step;
int omp_get_num_threads();
int omp_get_thread_num();
int omp_set_num_threads();
double omp_get_wtime();
int main ()
{
	omp_set_num_threads(10);
	int thrnum = omp_get_num_threads();
	int share = num_steps/thrnum; //share of the steps
	double pi, sum=0.0;
	step = 1.0/(double) num_steps;
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int i;
		double x;
		int start = id*share;
		int finish = start + share; 
		for (i=start; i<finish; i++)
		{
			x = (i+0.5)*step;
			sum += 4.0/(1.0+x*x);
		}
	}
	pi = step*sum;
	printf("pi=%.7f\n",pi);
	/*
	int i;
	double x, pi, sum=0.0;
	step = 1.0/(double) num_steps;
	for (i=0; i<num_steps; i++)
	{
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
		pi  = step*sum;
	}
	*/
	return 0;
}