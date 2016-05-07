#include <stdio.h>
#include <stdlib.h>

// realiza a busca linear(ou sequencial)
int linear_search(int* vector, int vector_size, int value) {

	int i;
	for (i = 0; i < vector_size; i++) {

		if(vector[i] == value) {
			return i;
		}
	}
	// neste caso não encontrou o valor
	return -1;
}

// realiza a busca binária
int binary_search(int* vector, int vector_size, int value) {

	int low = 0, high = vector_size-1, mid;
    while(low <= high) {

        mid = (low + high)/2;
        if(vector[mid] < value) {
            low = mid + 1;
        }
        else if(vector[mid] == value) {
            return mid;
        }
        else if(vector[mid] > value) {
            high = mid-1;
        }
    }
    // neste caso não encontrou o valor
    return -1;
}

// devolve o ponteiro para o arquivo
FILE* get_file_pointer(char* file_name) {
	FILE* file_pointer;

	//abrindo o arquivo em modo "somente leitura"
	file_pointer = fopen(file_name, "r");

	// verifica se o arquivo conseguiu ser aberto
	if(file_pointer == NULL) {
		printf("Problemas na abertura do arquivo\n");
		exit(EXIT_FAILURE);
	}
	// retorna o ponteiro
	return file_pointer;
}

// função que exibe todos os elementos do arquivo
void show_all_elements(FILE* file_pointer) {
	int SIZE = 100;	
	char line[SIZE];

	// enquanto não for fim de arquivo o looping será executado
	while(fgets(line, SIZE, file_pointer) != NULL) {
		printf("%s", line);
	}

	// fechando arquivo
	fclose(file_pointer);
}

// aloca um vetor do tamanho passado por parametro
int* create_vector(int size) {
	int* vector = (int*)malloc(size*sizeof(int));
	return vector;
}

// lê o vetor do arquivo
void read_vector(int* vector, int vector_size, FILE* file) {
	int i;
	for (i = 0; i < vector_size; ++i) {
		fscanf(file, "%d ", &vector[i]);
	}
}

// mostra os elementos do vetor
void print_vector(int* vector, int vector_size) {
	int i;
	for (i = 0; i < vector_size; ++i) {
		printf("%d\n", vector[i]);
	}
	printf("\n");
}

//------------ METODO PRINCIPAL --------------
int main(int argc, char *argv[]) {
	int SIZE = 100;
	char line[SIZE];
	int value, vector_size;

	// criando a variável ponteiro para o arquivo
	FILE* file = get_file_pointer(argv[1]);

	// lê o valor a ser buscado e o tamanho do vetor do arquivo
	fscanf(file, "%d\n", &value);
	fscanf(file, "%d\n", &vector_size);

	// aloca o vetor
	int* vector = create_vector(vector_size);

	// lê os dados do arquivo
	read_vector(vector, vector_size, file);

	// resultados da busca binária
	int position = binary_search(vector, vector_size, value);
	printf("------ Busca binaria ------\n");
	if(position != -1) {
		printf("Posicao encontrada: %d\n", position);
	}
	else {
		printf("Não foi encontrado!\n");
	}

	// resultados da busca sequencial
	position = linear_search(vector, vector_size, value);
	printf("------ Busca sequencial ------\n");
	if(position != -1) {
		printf("Posicao encontrada: %d\n", position);
	}
	else {
		printf("Não foi encontrado!\n");
	}

	free(vector);
	fclose(file);	

	return 0;
}
