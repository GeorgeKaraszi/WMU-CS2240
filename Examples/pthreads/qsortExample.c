#include <stdio.h>	 /* for fprintf  */
#include <stdlib.h>	 /* for qsort_r  */
#include <pthread.h> /* for yarn?    */


int compf(const void *a, const void *b, void * dummy) 
{

	//a is a void* pointer that points to array
	int first   =  *(*((int**)a));
	int second   = *(*((int**)b));
	return first - second;

}

int main (int argc, char *argv[])
{
	int i;

	//to hold our pointer to many pointers
	int **array;

	//to pass to our qsort_r
	void *dummy;

	if(argc<3)
	{
		fprintf(stderr, "Error: Please enter a space separated list of ints to be sorted " 
			"from the command line. Example: %s 6 9 12\n",argv[0] );
		exit(EXIT_FAILURE);
	}

	//create an array of pointers with amount of args they passed in 
	array = malloc(sizeof(int*)*(argc-1));

	fprintf(stderr, "Before qsort_r\n");
	for(i=0; i<argc-1;i++)
	{
		//array[i] ...if that helps
		*(array+i) = malloc(sizeof(int));


		//store the value of argv in *array[i] 
		*(*(array+i)) = atoi(argv[i+1]);
		
		fprintf(stderr, "*(array+i) &:%p the value in *(*(array+i)):%d\n",*(array+i), *(*(array+i)) );
		//fprintf(stderr, "[%d] %d\n", i, *(*(array+i)));	
	}

	//args: the array to be sorted, the amount of elements in the array, the sizeof those elements,
	//	and a dummy variable
	qsort_r(array,argc-1,sizeof(int*),compf,dummy);
	

	fprintf(stderr, "After qsort_r\n" );
	for(i=0; i<argc-1;i++)
	{
		fprintf(stderr, "*(array+i) &:%p the value in *(*(array+i)):%d\n",*(array+i), *(*(array+i)) );
		//fprintf(stderr, "[%d] %d\n", i, *(*(array+i)));	

		free(*(array+i));

	}

	free(array);

}