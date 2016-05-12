#include <stdio.h>
#include <stdlib.h>

// realiza a busca linear(ou sequencial)
int linear_search(int* vector, int vector_size, int value) {
	int count = 0;
	
	int i;
	for (i = 0; i < vector_size; i++) {
		count++;
		if(vector[i] == value) {
			printf("Numero de comparacoes: %d\n", count);
			return i;
		}
	}
	// neste caso não encontrou o valor
	return -1;
}

// realiza a busca binária
int binary_search(int* vector, int vector_size, int value) {
	int count = 0;

	int low = 0, high = vector_size-1, mid;
    while(low <= high) {
    	count++;

        mid = (low + high)/2;
        if(vector[mid] < value) {
            low = mid + 1;
        }
        else if(vector[mid] == value) {
        	printf("Numero de comparacoes: %d\n", count);
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

	// resultados da busca sequencial
	printf("\n------ BUSCA SEQUENCIAL ------\n");
	int position = linear_search(vector, vector_size, value);
	if(position != -1) {
		printf("Posicao encontrada: %d\n", position);
	}
	else {
		printf("Nao foi encontrado!\n");
	}

	// resultados da busca binária
	printf("\n------ BUSCA BINARIA ------\n");
	position = binary_search(vector, vector_size, value);
	if(position != -1) {
		printf("Posicao encontrada: %d\n", position);
	}
	else {
		printf("Nao foi encontrado!\n");
	}

	printf("\n");

	// mostra os elementos do vetor
	//print_vector(vector, vector_size);

	free(vector); // desaloca da memoria
	fclose(file); // fecha o arquivo	 

	return 0;
}
