#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	/* Initializing Variables */
	//int iam; //Id of thread
  	//int np; //Number of threads

 	int threads = 4;
	omp_set_num_threads(threads);
	//int threads = 10;
	/* Start Forking Threads */
	#pragma omp parallel //private (iam, np)
	{ 
		int np=omp_get_num_threads(); //Total Number of Threads
		//np = threads;
		int iam=omp_get_thread_num(); //My Rank
 		printf("\n Hello from thread %d out of %d \n", iam,np);
	}	
	/* End by joining threads */
	return 0;
}
