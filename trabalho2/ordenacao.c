#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// função que lê os dados do array
void read_array(int* array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++) {
		scanf("%d", &array[i]);
	}
}

// exibe no console os elementos do vetor
void show_array(int* array, int array_size) {
	int i;
	for(i = 0; i < array_size; i++) {
		printf(" %d ", array[i]);
	}
	printf("\n");
}

// cria um vetor com o tamanho que é passado como parametro
int* create_array(int size) {
	int* array = (int*)malloc(size*sizeof(int));
	return array;
}

// função auxiliar para interlacar os vetores
void merge (int *A, int a, int *B, int b, int *C) {
  int i,j,k;
  i = j = k = 0; 

  while (i < a && j < b) {
    if (A[i] <= B[j]) {
	  C[k++] = A[i++];
    }
    else {
      C[k++] = B[j++];
    }
  }

  while (i < a) {
    C[k++]= A[i++];
  }

  while (j < b)  {
    C[k++]= B[j++];
  }
}  

// algoritmo de ordenação Merge Sort
void merge_sort(int* array, int array_size) {
	if (array_size < 2) return;

	// divide o array em dois, A1 e A2
	int n1 = array_size / 2; // numero de elementos para A1
	int n2 = array_size - n1; // numero de elementos para A2

	int* A1 = create_array(n1);
	int* A2 = create_array(n2);
	  
	int i;
	for (i =0; i < n1; i++) { // move todos os elementos para A1
		A1[i] = array[i];
	}

	for (i = 0; i < n2; i++) { // move o resto dos elementos para A2
		A2[i] = array[i+n1];
	}
	 
	merge_sort(A1, n1); //faz a chamada recursiva
	merge_sort(A2, n2); 

	merge(A1, n1, A2, n2, array); // intercala os vetores divididos
	free(A1);
	free(A2);
}

// Algoritmo de ordenação Insertion Sort
void insertion_sort(int* array, int array_size) {
	int i, j, temp;
	for(i = 1; i < array_size; i++) {
		j = i;
		while((j > 0) && (array[j-1]) > array[j]) {
			temp = array[j];
			array[j] = array[j-1];
			array[j-1] = temp;
			j -= 1;
		}
	}
}


int main() {

	clock_t start_time, end_time;
	int array_size;	 
	double total_time;

	//lê o tamanho do array
	scanf("%d", &array_size);
	//cria o vetor
	int array[array_size];
	// lê os dados do array
	read_array(array, array_size);

	//--------------- INSERTION SORT--------------

	// // faz a análise do tempo gasto
	// start_time = clock();
	// insertion_sort(array, array_size); // executa o algoritmo insertion sort
	// end_time = clock();

	// // calcula o tempo total gasto
	// total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	// printf("Tempo gasto pelo algoritmo Insertion Sort %f\n", total_time);


	//-------------- MERGE SORT ------------------

	// faz a análise do tempo gasto
	start_time = clock();
	merge_sort(array, array_size); // executa o algoritmo insertion sort
	end_time = clock();

	// calcula o tempo total gasto
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	printf("Tempo gasto pelo algoritmo Merge Sort %f\n", total_time);

	return 0;
}
