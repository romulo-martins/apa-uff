/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VerificaOrdem.c
 * Author: Carrara
 *
 * Created on 7 de Maio de 2016, 18:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 
 */

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


int main(int argc, char** argv) {
    int atual, proximo,size, element;
    char* arq[10];
    arq[0] ="testes/Teste1.txt"; 
    arq[1] ="testes/Teste2.txt"; 
    arq[2] ="testes/Teste3.txt"; 
    arq[3] ="testes/Teste4.txt"; 
    arq[4] ="testes/Teste5.txt"; 
    arq[5] ="testes/Teste6.txt"; 
    arq[6] ="testes/Teste7.txt"; 
    arq[7] ="testes/Teste8.txt"; 
    arq[8] ="testes/Teste9.txt"; 
    arq[9] ="testes/Teste10.txt"; 
    
    FILE *file;
    int i;
    for (i = 0; i < 10; i++) {
        file = get_file_pointer(arq[i]);
        fscanf(file, "%d\n", &element);
	fscanf(file, "%d\n", &size);
        
        
        int *aux = create_vector(size);
        read_vector(aux,size,file);
        int j;
        for (j = 0; j < size-2; j++) {
	    if(aux[j]>aux[j+1]){
                printf("Vetor não ordenado: %s", arq[i]);
                break;
            }    
        }
        fclose(file);
          
           
           
    }

    
    
    
    
    printf("Nenhum desordenado");
    return (EXIT_SUCCESS);
}

