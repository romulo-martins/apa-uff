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

// faz uma cópia do array passado por parametro
int* copy_array(int* array , int array_size) {
	int* temp = create_array(array_size);
	int i;
	for(i = 0; i < array_size; i++) {
		temp[i] = array[i];
	}
	return temp;
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

void execute_analisys_insertion_sort(int* array, int array_size) {
	clock_t start_time, end_time; // variaveis para a contagem do tempo	 
	double total_time;

	// faz a análise do tempo gasto
	start_time = clock();
	insertion_sort(array, array_size); // executa o algoritmo insertion sort
	end_time = clock();

	// calcula o tempo total gasto
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("----- Insertion Sort -----\n");
	printf("Tempo gasto: %f\n", total_time);
	// show_array(array, array_size);

}

void execute_analisys_merge_sort(int* array, int array_size) {
	clock_t start_time, end_time; // variaveis para a contagem do tempo	 
	double total_time;

	// faz a análise do tempo gasto
	start_time = clock();
	merge_sort(array, array_size); // executa o algoritmo merge sort
	end_time = clock();

	// calcula o tempo total gasto
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("----- Merge Sort -----\n");
	printf("Tempo gasto: %f\n", total_time);
	//show_array(array, array_size);	
}
 

int main() {

	int array_size;
	scanf("%d", &array_size); //lê o tamanho do array

	// cria o array
	int* array = create_array(array_size);

	// lê os dados do array
	read_array(array, array_size);

	int* array_2 = copy_array(array, array_size); // faz uma cópia do array lido

	// faz a execução do algoritmo insertion sort e verifica o tempo gasto
	execute_analisys_insertion_sort(array, array_size);

	// faz a execução do algoritmo merge sort e verifica o tempo gasto
	execute_analisys_merge_sort(array_2, array_size);

	free(array);
	free(array_2);

	return 0;
}
