#include <stddef.h>

char* new_strcpy(char* destination, const char* source) { //this function takes the string in source and copies it to destination

	int i;

	for (i = 0; source[i] != '\0'; i++) 
		destination[i] = source[i]; //copies source into destination

	destination[i] = '\0'; //adds the null character to the end of destination, making it a legal string

	return destination; 

}

char* new_strncpy(char* destination, const char* source, size_t n) { //this function takes the string in source and copies it into destination up to n

	int i;
    int j;
	
	for (i = 0; i < n && source[i] != '\0'; i++)  
		destination[i] = source[i]; //copies source into destination up until n
	
	for (j = i; j < n; j++) //if there is still space in destination, pad with null characters
		destination[i] = '\0';

	return destination; 

}


int new_strcmp(const char* string1, const char* string2) { //this function compares two strings

	int i;

	for (i = 0; string1[i] != '\0' && string2[i] != '\0'; i++) {
		if (string1[i] > string2[i]) //if string1 comes after string2, return a postive number
			return 1;
		else if (string1[i] < string2[i]) //if string1 comes before string2, return a negative number
			return -1;	
	}

	return 0; //if the two strings are identical, return 0
	
}


int new_strncmp(const char* string1, const char* string2, size_t n) { //this function compares two strings up until the nth character

	int i;

	for (i = 0; i < n && string1[i] != '\0' && string2[i] != '\0'; i++) {
		if (string1[i] > string2[i]) //if string1 comes after string2, return a postive number
			return 1;
		else if (string1[i] < string2[i]) //if string1 comes before string2, return a negative number
			return -1;
	}

	return 0; //if the two strings are identical, return 0
 
}

char* new_strcat(char* destination, const char* source) { //this function combines the two strings by adding source to the end of destination

	int i = 0; 
	int j;
	
	while (destination[i] != '\0') //gets the length of destination
		i++;

	for (j = 0; source[j] != '\0'; j++) {
		destination[i] = source[j]; //at the end of destination, add source
		i++;
	}

	destination[i] = '\0'; //add null character to end of new string

	return destination;

}

char* new_strncat(char* destination, const char* source, size_t n) { //this function combines the two strings by adding source to the end of destination up until the nth character

	int i = 0;
	int j;

	while (destination[i] != '\0') //gets the length of destination
		i++;

	for (j = 0; j < n && source[j] != '\0'; j++) {
		destination[i] = source[j]; //at the end of destination, add source
		i++;
	}

	destination[i] = '\0'; //add null character to end of new string

	return destination;

}

size_t new_strlen(const char* string) { //finds the length of a string

	int count = 0;

	while (string[count] != '\0') 
		count++; //counts the characters for the length of the string

	return count;

}

char* new_strchr(const char* string, int character) { //finds the first occurrence of a character in a string or null if the character cannot be found

	int i = 0;

	while (string[i] != '\0') { //runs the length of the string
		if (string[i] == (char)character) //if the character is equal to a character in string
			return (char*)&string[i]; //return that location of a character
		i++;
	}

	return NULL;

}

char* new_strstr(const char* haystack, const char* needle) { //finds the first occurrence of the string contained in needle in haystack or null if the needle cannot be found

	int i = 0;

	if (needle == "") //empty string case
		return (char*)&haystack[i];

	while (haystack[i] != '\0') { //runs the length of the string
		int j = 0;
		while (haystack[i + j] == needle[j]) {
			j++;
			if (needle[j] == '\0') //if the string needle is found in haystack
				return (char*)&haystack[i]; //return that substring
		}
		i++;		
	}

	return NULL;
}


























