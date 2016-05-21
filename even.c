/******************************************************************
Author: Girish Srinivas	 
*******************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//function prototypes.....
long maxNumber(int);


//Shared global variables....
long max[100000], array[100000];
long size;

//main() thread starts....
int main(void)
{
	int threads, elapsed;
	long maxNum;

	printf("\nEnter the size of the array: ");
	scanf("%ld", &size);	

	printf("\nEnter the number of threads: ");
	scanf("%d", &threads);

	printf("\nEnter %d numbers into the array:\n", size);
	for (int i = 0; i < size; i++)
	{
		scanf("%ld",&array[i]);
	}

	omp_set_num_threads(threads);

	//parallel block starts.....
	#pragma omp parallel
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

		maxN = 0;
		for (int i = start + 1; i < end; ++i)
		{
			if(array[i] % 2 == 0)
			{
				if(array[i] >= maxN)
				{
					maxN = array[i];
				}
			}
		}
		max[id] = maxN;
		printf("\nMax value of thread %d with size %ld is %ld\n", id, n, maxN);

	}
	//parallel blocks ends......

	maxNum = maxNumber(threads);



	printf("\nThe max Even number is: %ld\n", maxNum);

	return 0;
}//main() threads ends.....



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

