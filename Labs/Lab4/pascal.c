#include <stdio.h>

int readInt(void);
long long factorial(int number);

int main() {

	int number;
	printf("Enter a number: ");
	number = readInt();

	if (number < 0 || number > 20)
		printf("Invalid input");
	
	int i;
	int j;
	for (i = 0; i < number; i++) {
		for (j = 0; j <= i; j++) 
			printf("%lld ", factorial(i) / (factorial(i-j)*factorial(j)));	
		printf("\n");
	}

	return 0;
}

int readInt() {
	
	int c = 0;
	int i = 0;
  
	while ((c = getchar()) != EOF && c != '\n' ) {
		if (c >= '0' && c <= '9')	
			i = i * 10 + (c - '0');	
	}

	return i;
}

long long factorial(int number) {

	if (number == 0)
		return 1;
	
	return number * factorial(number - 1);

}
