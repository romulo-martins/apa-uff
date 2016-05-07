#include <stdio.h>
#include <stdlib.h>

// busca linear
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

// busca binária
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
		return 0;
	}
	// retorna o ponteiro
	return file_pointer;
}

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

//------------ METODO PRINCIPAL --------------
int main(int argc, char *argv[]) {

	// criando a variável ponteiro para o arquivo
	FILE* file_pointer = get_file_pointer(argv[1]);

	show_all_elements(file_pointer);

	return 0;
}
