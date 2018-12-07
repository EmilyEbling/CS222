#include <stdio.h>
#include <stdlib.h>

void merge(int array1[], int length1, int array2[], int length2, int result[]);

int main() {

	int length1;
	int length2;
	int i;

	scanf("%d", &length1);
	scanf("%d", &length2);

	int* array1 = malloc(sizeof(int) * length1);
	int* array2 = malloc(sizeof(int) * length2);
	int* result = malloc(sizeof(int) * (length1 + length2));

	for (i = 0; i < length1; i++)
		scanf("%d", &array1[i]);	

	for (i = 0; i < length2; i++)
		scanf("%d", &array2[i]);	
	
	printf("List 1: ");
	for (i = 0; i <	length1; i++)
		printf("%d ", array1[i]);

	printf("\n");

	printf("List 2: ");
	for (i = 0;	i < length2; i++)
		printf("%d ", array2[i]);

	printf("\n");		

	merge(array1, length1, array2, length2, result);

	free(array1);
	free(array2);
	free(result);
}

void merge(int array1[], int length1, int array2[], int length2, int result[]) {

	int index = 0;	
	int index1 = 0;
	int index2 = 0;
	int i;

	while (index1 < length1 && index2 < length2) {
		if (array1[index1] < array2[index2]) {
			result[index] = array1[index1];
			index1++;
		}
		else if (array1[index1] > array2[index2]) {
			result[index] = array2[index2];
			index2++;
		}

	index++;

	}

	if (index1 != length1)
		for (i = 0; i < length1; i++) {
			result[index] = array1[index1]; 
			index++;
			index1++;
		}

	if (index2 != length2)
		for (i = 0; i < length2; i++) {
			result[index] = array2[index2];
			index++;
			index2++;
		}

	printf("Merged List: ");
	for (i = 0; i < length1 + length2; i++)
		printf("%d ", result[i]);

	printf("\n");
	
}























