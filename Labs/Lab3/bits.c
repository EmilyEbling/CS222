#include <stdio.h> 

int main() {

	int value = 0;
	printf("Enter an integer: ");
	value = readInt();

	char command; 
	printf("Do you want to set, unset, or flip a bit? (s, u, f): ");
	command = getchar();
	getchar();

	int bit;
	printf("Which bit? (0-31): ");
	bit = readInt();

	int newValue;
	int newBit;

	if (command == 's') {
		newBit = 1 << bit;
		newValue = newBit | value;
		printf("The result of setting bit %d in %d is %d \n", bit, value, newValue);
	}
	
	else if (command == 'u') {
		newBit = 1 << bit;
		newBit = ~newBit;
		newValue = newBit & value;
		printf("The result of unsetting bit %d in %d is %d \n", bit, value, newValue);
	}
	
	else if (command == 'f') {
		newBit = 1 << bit;
		newValue = newBit ^ value;
		printf("The result of flipping bit %d in %d is %d \n", bit, value, newValue);
	}	
	
}

int readInt() {
	
	int c = 0;
	int i = 0;
  
	while( (c = getchar()) != EOF && c != '\n' ) {
		if( c >= '0' && c <= '9')	
			i = i * 10 + (c - '0');	
	}

	return i;
}
