#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 500000

// algoritmo de ordenação insertion sort
void insertion_sort(int* array, int array_size) {
	int i, j, temp;

	for(i = 1; i < array_size; i++){
    	temp = array[i];
    	j = i-1;
    	while((temp < array[j]) && (j >= 0)){
    		array[j+1] = array[j];
          	j = j-1;
      	}
      	array[j+1] = temp;
  	}
}


// função que exxibe o array
void print_array(int *array, int array_size) {
	int i;
	for (int i = 0; i < array_size; i++) {
		printf(" %d ", array[i]);
	}
	printf("\n");
}


// função que lê os dados do array
void read_array(int* array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++) {
		scanf("%d", &array[i]);
	}
}

int main() {

	clock_t start_time, end_time;
	int array_size;	 

	//lê o tamanho do array
	scanf("%d", &array_size);
	//cria o vetor
	int array[array_size];
	// lê os dados do array
	read_array(array, array_size);

	// faz a análise do tempo gasto
	start_time = clock();
	insertion_sort(array, array_size); // executa o algoritmo insertion sort
	end_time = clock();

	// calcula o tempo total gasto
	double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	printf("Tempo gasto pelo algoritmo Insertion Sort %f\n", total_time);

	return 0;
}
