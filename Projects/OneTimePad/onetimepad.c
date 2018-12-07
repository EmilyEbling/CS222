
#include <stdio.h>

//prototypes for functions
int inputMsg(unsigned char message[]);
int inputKey(unsigned char key[], int msgLength);
void output(unsigned char out[], int len);
void xor(unsigned char message[], unsigned char key[], unsigned char cipher[], int len);
int tiling(unsigned char key[], int msgLength, int keyLength);
void chaining(unsigned char key[], int keyLength);
char rotate(unsigned char c, int count);
int bits(unsigned char c);

int main() {
	
	unsigned char message[2048]; //array to hold the message text
	unsigned char key[2048]; //array to hold the key text
	unsigned char cipher[2048]; //array to hold the cipher of message and key, once they have been XORed

	int msgLength = inputMsg(message); //length of message
	int keyLength = inputKey(key, msgLength); //length of key
	keyLength = tiling(key, msgLength, keyLength); //change the keyLength to the new keyLength, which should be the same as the msgLength
	chaining(key, keyLength); //does some funky stuff to the key
	xor(message, key, cipher, msgLength); //combines the message and key using the XOR operator
	output(cipher, msgLength); //outputs the cipher text
	
	return 0;
}

int inputMsg(unsigned char message[]) { //this function reads in the text from an input file containing the message

	int c = 0;
	int i;
	
	for (i = 0; (c = getchar()) != 255; i++) //get the characters until you reach the deliminator 		
		if (i < 2048) //only add characters to the array for the first 2048 characters of the message
			message[i] = c;

	if (i > 2048) //if the message is longer than 2048 set the msgLength to 2048 (max array capacity)
		return 2048;

	return i; //otherwise i is the msgLength
}

int inputKey(unsigned char key[], int msgLength) { //this function reads in the text from an input file containing the key

	int c = 0;
	int i;

	for (i = 0; (c = getchar()) != EOF; i++) //get the characters until you reach the end of file
		if (i < 2048) //only add characters to the array for the first 2048 characters of the key		
			key[i] = c;

	if (i > 2048) //if the key is longer the 2048 set the keyLength to 2048 (max array capacity)
		return 2048;

	return i; //otherwise i is the keyLength
}

void output(unsigned char out[], int length) { //this function outputs the message to the specified document
	
	int i;

	for (i = 0;	i < length; i++) //runs for the length of the message
		putchar(out[i]); //outputs the characters to a file
} 

void xor(unsigned char message[], unsigned char key[], unsigned char cipher[], int length) { //this function xor's the message and the key
	
	int i;
	
	for (i = 0; i < length; i++) //runs for the length of the message (which should also be the length of the key)
		cipher[i] = message[i] ^ key[i]; //combines the message and key with the XOR operator
} 

int tiling(unsigned char key[], int msgLength, int keyLength) { //if the message is longer than the key, this function will make the key the same size as the message in order for the two to be combined properly

	int multiples = msgLength / keyLength - 1; //determines how many times the message is divisible by the key
	int remainder = msgLength % keyLength; //finds the remainder when dividing the message by the key
	int i;
	int j;
	int temp = keyLength;

	for (i = 0; i < multiples; i++) { //this loop will run multiples times.. ha 
		for (j = 0; j < keyLength; j++) //run for the length of the key
			key[keyLength + j] = key[j]; //set the last location in the key array to jth item in key
		keyLength += temp;	//increase the length of keyLength depending on how many times the full key was added to keys
	}

	for (i = 0; i < remainder; i++) //this loop will run through the program remainder times
		key[keyLength + i] = key[i]; //set the last location in the key array to the ith item in the key

	keyLength += remainder; //incresae the length of keyLength depending on how many characters were added to the end
	return keyLength; //returns the new length of key
}

/*void tiling(unsigned char key[], int length, int keyLength){ //if the key is shorter than the message, the key needs to be repeated to continue encrypting
	int i;
	for(i = keyLength; i < length; ++i) //go through the key and repeat it until it is the same length as the message
        key[i] = key[i-keyLength];
 }*/

void chaining(unsigned char key[], int keyLength) { //this functions mixes up the key so it's more complex/more difficult to crack

	int sum = key[keyLength - 1] % keyLength; //initializes the sum
	int i;

	key[0] = rotate(key[0] ^ key[sum], bits(key[keyLength - 1])); //sets the first position in the key
	sum += key[0]; //increases the sum
	sum %= keyLength; //mod by the length of key to keep index in bounds 

	for (i = 1; i < keyLength; i++) { //this loop will run for the length of the key
		key[i] = rotate(key[i] ^ key[sum], bits(key[i - 1])); //sets the ith position in key
		sum += key[i]; //increses the sum
		sum %= keyLength; //mod by the length of the key
	}
}

char rotate(unsigned char c, int count) { //this function rotates a character's 7 least significant bits to count places to the right

	int i;
	unsigned char storage = 1;
	unsigned char temp = 1; //used for a 1 bit

	if (count == 7) //if count is 7 then each position contains a 1 and the character's rotation is unchanging
		return c;

	for (i = 0; i < count; i++) {
		storage = c & temp; //&s the character and a 1 together
		c >>= 1; //shifts c to the right by 1 position
		if (storage) //if after &ing storage is 1 
			c |= 64; // | the character and 64 (the 7th bit)
	}

	return c; //return the newly rotated character
}

int bits(unsigned char c) { //this function counts the number of one bits in a character

	char temp = 1; 
	int i;
	int sum = 0;

	for (i = 0; i < 7; i++) { //run through the 8 bits of a character
		if (temp & c) //if &ing temp and c gets you a 1 then you increase the sum of one bits
			sum++; 
		temp <<= 1; //shift temp to the left and see if the next location is a one or not
	}

	return sum; //returns total number of one bits
}







