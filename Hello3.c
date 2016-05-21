#include <stdio.h>
#include <omp.h>

void printHello(char);
void printThread(char);

int main(int argc, char *argv[])
{
 	int threads;
 	int iam; //Id of thread
  	int np; //Number of threads
  	char ch = 'c';
 	printf("Enter the number of threads: ");
 	scanf("%d", &threads);
	omp_set_num_threads(threads);

	printf("First parallel block started....\n");
	/* Start Forking Threads */
	#pragma omp parallel //private (iam, np)
	{ 
		printHello(ch);
	}	
	printf("Second parallel block startd...\n");
	#pragma omp parallel //private (iam, np)
	{ 
		printThread(ch);
	}	

	/* End by joining threads */
	return 0;
}

void printHello(char ch)
{
	int np=omp_get_num_threads(); //Total Number of Threads
		
	int iam=omp_get_thread_num(); //My Rank
 	printf("\n 'Hello' from thread %d out of %d with character: %c\n", iam,np,ch);

}


void printThread(char ch)
{
	int np=omp_get_num_threads(); //Total Number of Threads
		
	int iam=omp_get_thread_num(); //My Rank
 	printf("\n 'World' from thread %d out of %d with character: %c\n", iam,np, ch);
}