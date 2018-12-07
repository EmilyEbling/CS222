#include <stdio.h>

char toLower(char value);

int main() {

	char word[1024];

	int i;
	int c = 0;
	int wordLength = 0;

	printf("Enter a string: ");

	for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
		if (i < 1024) 
			word[i] = c;
		
	wordLength = i;
	word[wordLength] = '\0'; 
	int isPalindrome = 1;

	for (i = 0; i < wordLength; i++) 
		if (toLower(word[i]) != toLower(word[wordLength - i - 1])) 
			isPalindrome = 0;

	if (isPalindrome)
		printf("The string \"%s\" is a palindrome.\n", word);
	else 
		printf("The string \"%s\" is not a palindrome.\n", word);		
	
	return 0;
}

char toLower(char value) {

	if (value >= 'A' || value <= 'Z')
		return value - 'A' + 'a';

	return value;

}
