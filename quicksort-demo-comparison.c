#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "omp.h"

#include "quicksort-omp.h"


int lenArr = 262144000; // 262144000 = 1000 MBytes = 1 GByte
int numthreads = 8;



void quickSort(int* arr, int left, int right) 
{
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

  	/* PARTITION PART */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}

	/* RECURSION PART */
	if (left < j){ quickSort(arr, left, j);  }
	if (i< right){ quickSort(arr, i, right); }
}





// Comparator used in qsort()
int cmpfunc (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}



int main(){
	int minMum = 1;
	int maxNum = lenArr;
	int maxNumbersDisplayed = 30;

	double startTime, stopTime;

	int* arr1;
	int* arr2; 
	int* arr3;
	arr1 = (int*) malloc(lenArr*sizeof(int));
	arr2 = (int*) malloc(lenArr*sizeof(int));
	arr3 = (int*) malloc(lenArr*sizeof(int));
	

	//printf("--------------------------------------------------");
	//printf("Info about the program: \n");
	//printf("Datatype of the array: %p", typeof() );
	//printf("Positions in the array: %d", typeof(arr1) );
	printf("\nSize of the array (aprox.): %lu MBytes \n", (lenArr*sizeof(int)/(1024*1024)) );
	printf("TOTAL MEMORY ALLOCATED:  3 x array = (aprox.): %lu MBytes \n\n", (lenArr*sizeof(int)/(1024*1024))*3 );  
	//printf("-------------------------------------------------- \n\n");


	
	// Initialise the array with random numbers
	int i;
	srand(5); // seed
	printf("Initializing the arrays with random numbers...\n");
	for (i=0; i<lenArr; i++){
		// RAND_MAX = 2147483647 = INT_MAX 
		// printf("RAND_MAX %u \n", RAND_MAX );
		arr1[i] = minMum+(rand()%maxNum);
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
		//printf("%d \n", arr1[i] ); 
	}
	printf("Initialization complete\n");



	
	if( lenArr <= maxNumbersDisplayed ){
		printf("\n\nArray BEFORE sorting: \n");
		for( i = 0 ; i < lenArr; i++ ) 
		{
			printf("%d ", arr1[i]);
		}
		printf("\n\n\n");
	}


	printf("\nSorting with serial 'qsort' function of 'stdlib.h' ..."); fflush(stdout);
	startTime = clock();
	qsort(arr1, lenArr, sizeof(int), cmpfunc);
	stopTime = clock();

	
	if( lenArr <= maxNumbersDisplayed ){
		for( i = 0 ; i < lenArr; i++ ) 
		{
			printf("%d ", arr1[i]);
		}
		
	}
	printf("\nSorted in (aprox.): %f seconds \n\n", (double)(stopTime-startTime)/CLOCKS_PER_SEC);




	printf("\nSorting with custom serial QuickSort..."); fflush(stdout);
	startTime = clock();
	quickSort(arr2, 0, lenArr-1);
	stopTime = clock();

	
	if( lenArr <= maxNumbersDisplayed ){
		for( i = 0 ; i < lenArr; i++ ) 
		{
			printf("%d ", arr2[i]);
		}
	}
	printf("\nSorted in (aprox.): %f seconds \n\n", (double)(stopTime-startTime)/CLOCKS_PER_SEC);



	printf("\nSorting with custom PARALLEL QuickSort... "); fflush(stdout);
	startTime = omp_get_wtime();
	quickSort_parallel(arr3, lenArr, numthreads);
	stopTime = omp_get_wtime();


	if( lenArr <= maxNumbersDisplayed ){
		for( i = 0 ; i < lenArr; i++ ) 
		{
			printf("%d ", arr3[i]);
		}
	}
	printf("\nSorted in (aprox.): %f seconds \n\n", (stopTime-startTime));




	printf("\nChecking if the results are correct...\n");
	typedef enum { false, true } bool;
	bool correctResult;

	correctResult=true;
	i = 0;
	while( (correctResult==true) && (i<lenArr) )
	{
		if(arr1[i]!=arr2[i]) { correctResult=false; }
		i++;
	}
	if(correctResult==true){
		printf("The result with 'custom serial QuickSort' is CORRECT\n");
	}else{
		printf("The result with 'custom serial QuickSort' is ¡¡INCORRECT!!\n");
	}

	correctResult = true;
	i = 0;
	while( (correctResult==true) && (i<lenArr) )
	{
		if(arr1[i]!=arr3[i]) { correctResult=false; }
		i++;
	}
	if(correctResult==true){
		printf("The result with 'custom PARALLEL QuickSort' is CORRECT\n\n");
	}else{
		printf("The result with 'custom PARALLEL QuickSort' is ¡¡INCORRECT!!\n");
	}




	printf("\n\n");

	free(arr1);
	free(arr2);
	free(arr3);

	return 0;
}