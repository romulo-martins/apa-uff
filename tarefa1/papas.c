#include <stdio.h>
#include <stdlib.h>

// lê os dados do arquivo para o array
void read_array(int* array, int array_size) {
	int i;
	for (i = 0; i < array_size; i++) {
		scanf("%d", &array[i]);		
	}
}

// cria o array
int* create_array(int array_size) {
	int* array = (int*)malloc(array_size*sizeof(int));
	return array;
}

void find_interval(int* array, int array_size, int interval_size) {
	int i, j, counter;
	int largest = 0;
	int first = 0;
	int end = 0;
	int current = 0;

	for (i = 0; i < array_size-1; i++) {
		counter = 0;
		j = i + 1;
		while(array[j] - array[i] < 5) {
			j++;
			if(array[j] - array[i] <= 5) {
				counter++;
			}
		}
		if(counter > largest) {
			largest = counter;
			first = array[i];
			end = array[j - 1];

		}
	}
	printf("%d %d %d\n", largest, first, end);
}

int main() {

	int y, p;

	scanf("%d", &y);

	scanf("%d", &p);

	int* popes = create_array(p);
	read_array(popes, p);

	find_interval(popes, p, y);

	free(popes);
	return 0;
}
