#include "omp.h"


void quickSort_parallel(int* array, int lenArray, int numThreads);
void quickSort_parallel_internal(int* array, int left, int right, int cutoff);



void quickSort_parallel(int* array, int lenArray, int numThreads){

	int cutoff = 1000;

	#pragma omp parallel num_threads(numThreads)
	{	
		#pragma omp single nowait
		{
			quickSort_parallel_internal(array, 0, lenArray-1, cutoff);	
		}
	}	

}



void quickSort_parallel_internal(int* array, int left, int right, int cutoff) 
{
	
	int i = left, j = right;
	int tmp;
	int pivot = array[(left + right) / 2];

	
	{
	  	/* PARTITION PART */
		while (i <= j) {
			while (array[i] < pivot)
				i++;
			while (array[j] > pivot)
				j--;
			if (i <= j) {
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
				i++;
				j--;
			}
		}

	}


	if ( ((right-left)<cutoff) ){
		if (left < j){ quickSort_parallel_internal(array, left, j, cutoff); }			
		if (i < right){ quickSort_parallel_internal(array, i, right, cutoff); }

	}else{
		#pragma omp task 	
		{ quickSort_parallel_internal(array, left, j, cutoff); }
		#pragma omp task 	
		{ quickSort_parallel_internal(array, i, right, cutoff); }		
	}

}




