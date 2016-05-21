/******************************************************************
Author: Girish Srinivas 
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

void read(int);

long array[100000], sumThread[100000];
double sumVar[100000];
long size;
//double sum = 0, sum_var = 0;

int main(void)
{
	int threads, elapsed;
	double sumTotal = 0, mean = 0, varience = 0, sd = 0, var = 0;
	struct timeval start_time, stop_time;

	printf("\nEnter the sample size of random numbers: ");
	scanf("%d" ,&size);

	printf("\nEnter the number of threads: ");
	scanf("%d", &threads);

	read(size);

	omp_set_num_threads(threads);

	gettimeofday(&start_time, NULL);
	//first parallel blocks starts...
	#pragma omp parallel
	{
		int th = omp_get_num_threads();
		int id = omp_get_thread_num();
		long n, start, end, sum = 0;

		n = size / th;
		start = id * n;
		if (id != (threads - 1))
		{
			end = start + n;
		}
		else
		{
			end = size;
		}

		for (int i = start; i < end; i++)
		{
			sum = sum + array[i];
		}
		sumThread[id] = sum;
		//printf("\nSum of thread %d is %ld\n", id, sumThread[id]);

	}// first parallel block ends...

	for (int i = 0; i < threads; ++i)
	{
		sumTotal = sumTotal + sumThread[i];
	}

	mean = sumTotal / size;

	printf("The total sum is: %f\n", sumTotal);
	printf("The Mean is: %f\n", mean);

	//second parallel block started...
	#pragma omp parallel
	{
		int th = omp_get_num_threads();
		int id = omp_get_thread_num();
		long n, start, end;
		double subvar = 0, temp = 0;

		n = size / th;
		start = id * n;
		if (id != (threads - 1))
		{
			end = start + n;
		}
		else
		{
			end = size;
		}

		for (int i = 0; i < end; ++i)
		{
			temp = array[i] - mean;
			subvar = subvar + (temp * temp);
		}

		sumVar[id] = subvar;
		//printf("\nSub varience of thread %d is %f\n", id, subvar);
	}
	//second parallel block ended....

	for (int i = 0; i < threads; ++i)
	{	
		var = var + sumVar[i];
	}

	varience = var / size;
	sd = sqrt(varience);

	gettimeofday(&stop_time, NULL);
	elapsed = (stop_time.tv_sec*1000000 + stop_time.tv_usec) - (start_time.tv_sec*1000000 + start_time.tv_usec);

	printf("varience is: %f\n", varience);
	printf("Standard Deviation is: %f\n", sd);
	printf("\nElapsed time: %d microseconds\n", elapsed);

	return 0;
}

void read(int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % 10000;
	}

	for (int i = 0; i < size; ++i)
	{
		printf("%d\t", array[i]);
	}
}