#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//----------- Operações de vetores ----------------------

// aloca um array
int* create_array(int array_size) {
	int* array = (int*)malloc(array_size * sizeof(int));
	return array;
}

// o vetor(array) de inteiros
void read_array(int* array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++) {
		scanf("%d", &array[i]);
	}
}

// mostra os elementos do vetor
void show_array(int* array, int array_size) {
	int i;
	printf("----- Vetor informado -----\n");
	for (i = 0; i < array_size; i++) {
		printf(" %d ", array[i]);
	}	
	printf("\n");
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

//----------- Operações para matrizes --------------------

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

// mostra os elementos da matriz
void show_matrix(int** matrix, int rows, int columns) {
	int i, j;
	printf("----- Matriz informado -----\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			printf(" %d ", matrix[i][j]);
		}
		printf("\n");		
	}	
	printf("\n");
}

//-------------- Algoritmo guloso -----------------------

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


// Algoritmo guloso para achar a melhor soma de sub-vetores
int greedy_algorithm(int* array, int array_size) {
	int sum_A = 0, sum_B = 0;

	// Faz a ordenação reversa para executar o algoritmo guloso
	merge_sort(array, array_size);

	int i;
	for (i = 0; i < array_size; i++) {
		if (sum_A < sum_B) {
			sum_A += array[i];
		}
		else {
			sum_B += array[i];
		}
	}
	return (sum_A - sum_B) == 0;
}


// ------------- Programação dinamica ------------------------

// inicializa os elementos da primeira linha com verdadeiro
void init_top(int** matrix, int columns) {
	int j;
	for (j = 0; j < columns; j++) {
		matrix[0][j] = 1;
	}
}

// inicializa os elementos da primeira coluna da matriz com falso, exceto m[0][0]
void init_leftmost(int** matrix , int rows) {
	int i;
	for (i = 1; i < rows; i++) {
		matrix[i][0] = 0;
	}
}

// algoritmo que realiza a pseudo-solução com programação dinâmica
// OBS: algumas coisas foram feitas de forma redundante apenas para melhorar a legibilidade do codigo
int dinamic_program(int* array, int array_size) {

	int k = total_sum(array, array_size);
	int n = array_size;

	int rows = k/2 + 1;
	int columns = n + 1;
	int** matrix = create_matrix(rows, columns);

	init_top(matrix, columns);
	init_leftmost(matrix , rows);

	int i, j;
	for(i = 1; i < rows; i++) {
		for (j = 1; j < columns; j++)	{
			if(i >= array[j-1]) {
				matrix[i][j] = matrix[i][j-1] || matrix[i-array[j-1]][j-1];	
			}
			else {
				matrix[i][j] = matrix[i][j-1];
			}			
		}
	}

	int answer = matrix[rows-1][columns-1];
	destroy_matrix(matrix, rows, columns);

	return answer;
}

// ------ Análises de tempo para cada algoritmo ----------------------

void print_answer(int answer) {
	if(answer) {
		printf("Pode ser particionado!\n");
	}
	else {
		printf("Não pode ser particionado!\n");
	}
}

void execute_analisys_dynamic(int* array, int array_size) {
	clock_t start_time, end_time; // variaveis para a contagem do tempo	 
	double total_time;

	// faz a análise do tempo gasto
	start_time = clock();
	int answer = dinamic_program(array, array_size); // executa o algoritmo de programação dinâmica
	end_time = clock();

	// calcula o tempo total gasto
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("----- Programação Dinâmica -----\n");
	printf("Tempo gasto: %f\n", total_time);
	print_answer(answer);
}

void execute_analisys_greedy(int* array, int array_size) {
	clock_t start_time, end_time; // variaveis para a contagem do tempo	 
	double total_time;

	// faz a análise do tempo gasto
	start_time = clock();
	int answer = greedy_algorithm(array, array_size); // executa o algoritmo guloso
	end_time = clock();

	// calcula o tempo total gasto
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("----- Algoritmo Guloso -----\n");
	printf("Tempo gasto: %f\n", total_time);
	print_answer(answer);
}


// ------------------ Main ----------------------------
int main() {

	int array_size;
	scanf("%d", &array_size);

	int* array = create_array(array_size);
	read_array(array, array_size);

	// Faz a análise de tempo gasta pela programação dinâmica
	// foi realizado este teste primeiro pois o algoritmo guloso desordena o vetor
	execute_analisys_dynamic(array, array_size);

	// Faz a análise de tempo do algoritmo guloso
	execute_analisys_greedy(array, array_size);	

	free(array);

	return 0;
}