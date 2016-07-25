#include <stdio.h>
#include <stdlib.h>

// aloca um array
int* create_array(int array_size) {
	int* array = (int*)malloc(array_size * sizeof(int));
	return array;
}

// aloca uma matriz
int** create_matrix(int rows, int columns){ 
	int i;	 
	int **matrix = (int**)malloc(rows * sizeof(int*));	 
	for (i = 0; i < rows; i++){ 
	    matrix[i] = (int*) malloc(columns * sizeof(int));
	}
	return matrix; 
}

// desaloca uma matriz
void destroy_matrix(int** matrix, int rows, int columns) {
	int i;
	for (i = 0; i < rows; i++) {
		free(matrix[i]);		
	}
	free(matrix);
}

// o vetor(array) de inteiros
void read_array(int* array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++) {
		scanf("%d", &array[i]);
	}
}


void show_result(char* message, int sum_A, int sum_B, long count) {
	printf("------ %s -----\n", message);
	printf("Soma de A: %d\n", sum_A);
	printf("Soma de B : %d\n", sum_B);
	printf("Numero de operaçoes: %ld\n", count);
}

// função auxiliar para interlacar os vetores
void merge(int *A, int a, int *B, int b, int *C) {
	int i, j, k;
	i = j = k = 0;

	while (i < a && j < b) {
		if (A[i] >= B[j]) {
			C[k++] = A[i++];
		}
		else {
			C[k++] = B[j++];
		}
	}

	while (i < a) {
		C[k++] = A[i++];
	}

	while (j < b) {
		C[k++] = B[j++];
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
	for (i = 0; i < n1; i++) { // move todos os elementos para A1
		A1[i] = array[i];
	}

	for (i = 0; i < n2; i++) { // move o resto dos elementos para A2
		A2[i] = array[i + n1];
	}

	merge_sort(A1, n1); //faz a chamada recursiva
	merge_sort(A2, n2);

	merge(A1, n1, A2, n2, array); // intercala os vetores divididos
	free(A1);
	free(A2);
}

void partition_guloso(int* array, int array_size) {
	int sum_A = 0, sum_B = 0;
	long count = 0;

	int i;	
	for (i = 0; i < array_size; i++) {
		if (sum_A <= sum_B)
		{
			sum_A += array[i];
		}
		else {
			sum_B += array[i];

		}
		count++;
	}

	show_result("Resultado", sum_A, sum_B, count);
}

// acha a soma total do vetor de inteiros 
int total_sum(int* array, int array_size) {
	int i;
	int sum = 0;
	for(i = 0; i < array_size; i++) {
		sum += array[i];
	}
	return sum;
}

void dinamic_program(int* array, int array_size) {

	int k = total_sum(array, array_size);
	int n = array_size;
	int** m = create_matrix(k/2, n);

	

	destroy_matrix(m, k/2, n);
}

int main() {

	int array_size; // n
	scanf("%d", &array_size);

	int* array = create_array(array_size);
	read_array(array, array_size);

	merge_sort(array, array_size);

	partition_guloso(array, array_size);

	printf("A soma total: %d\n", total_sum(array, array_size));

	free(array);
	return 0;
}
