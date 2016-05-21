/******************************************************************
Author: Girish Srinivas
*******************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//function prototypes.....
void maxNumberThread(int);
void read(int);
long maxNumber(int);

//Shared global variables....
long max[100000], array[100000];
long size;

//main() thread starts....
int main(void)
{
	int threads, elapsed;
	long maxNum;
	struct timeval start_time, stop_time;

	printf("\nEnter the size of the array: ");
	scanf("%ld", &size);

	printf("\nEnter the number of threads: ");
	scanf("%d", &threads);

	read(size);

	omp_set_num_threads(threads);

	gettimeofday(&start_time, NULL);
	//parallel block starts.....
	#pragma omp parallel
	{
		maxNumberThread(threads);
	}
	//parallel blocks ends......

	maxNum = maxNumber(threads);
	gettimeofday(&stop_time, NULL);
	elapsed = (stop_time.tv_sec*1000000 + stop_time.tv_usec) - (start_time.tv_sec*1000000 + start_time.tv_usec);

	printf("\nThe max number is: %ld\n", maxNum);
	printf("\nElapsed time: %d microseconds\n", elapsed);

	return 0;
}//main() threads ends.....


void maxNumberThread(int threads)
{
	int th = omp_get_num_threads();
	int id = omp_get_thread_num();
	long start, end, maxN, n;

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

	maxN = array[start];
	for (int i = start + 1; i < end; ++i)
	{
		if(array[i] >= maxN)
		{
			maxN = array[i];
		}
	}
	max[id] = maxN;
	//printf("\nMax value of thread %d with size %ld is %ld\n", id, n, maxN);
}

long maxNumber(int threads)
{
	long m;
	m = max[0];
	for (int i = 1; i < threads; i++)
	{
		if(max[i] >= m)
		{
			m = max[i];
		}
	}
	return m;
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
		printf("%ld\t", array[i]);
	}
}