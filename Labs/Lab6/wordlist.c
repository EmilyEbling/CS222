#include <stdio.h>
#include <string.h>

void backwards(char** argv, int count);
void reverse(char** argv, int count);
void sort (char** argv, int count);

int main(int argc, char** argv) {

	int i;

	for (i = 1; argv[1][i] != '\0'; i++) {
		if (argv[1][i] == 'b')
			backwards (argv, argc);
		if (argv[1][i] == 'r')
			reverse (argv, argc);
		if (argv[1][i] == 's')
			sort(argv, argc);
	}

	for (i = 2; i < argc; i++)
		printf("%s ", argv[i]);
	
	printf("\n");

	return 0;
}

void backwards(char** argv, int count) {

	int i;
	int j;
	char temp;

	for (i = 2; i < count; i++) { //starts at the first word (second argument)
		int length = strlen(argv[i]);
		for (j = 0; j < length/2; j++) {
			temp = argv[i][j]; 
			argv[i][j] = argv[i][length - j - 1];
			argv[i][length - j - 1] = temp;
		}
	}
}

void reverse(char** argv, int count) {

	int i;
	int j;
	int start = 2;
	int end = count - 1;
	char* temp;
	
	while (start < end) {
		temp = argv[start]; 
		argv[start] = argv[end];
		argv[end] = temp;
		start++;
		end--;
	}
}

void sort (char** argv, int count) {
	
	int i;
	int j;
	char* temp;

	for (i = 2; i < count - 1; i++)
		for (j = 2; j < count - 1; j++)
			if (strcmp(argv[j], argv[j + 1]) > 0) {
				temp = argv[j];
				argv[j] = argv[j + 1];
				argv[j + 1] = temp;
			}
}


