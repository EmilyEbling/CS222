
#include <stdio.h>

void lazyCaterer(); 
void primes();
void fibonacci();
void collatz();
void happyNum();
int recursion(int x, int count);

int main() {

	lazyCaterer(); //calls lazyCaterer function
	printf("\n");
	primes(); //calls primes function
	printf("\n");
	fibonacci(); //calls fibonacci function
	printf("\n");
	collatz(); //calls collatz function
	printf("\n");
	happyNum(); //calls happyNum function
		
	return 0;
}

void lazyCaterer() { //if a caterer was lazy he/she would use this method to determine the maximum number of pieces he/she could cut from a cake, incrementing the number of slices each time

	int cuts = 0;
	int i;

	printf("Lazy Caterer's Sequence:\n");

	for (i = 0; i < 50; i++) { //determines how many pieces are possible with 1-50 cuts
		int pieces = ((cuts * cuts) + cuts + 2) / 2;
		printf("%d ", pieces); //prints out the total number of pieces
		cuts++; //increments the number of cuts being made 
	}
	
	printf("\n");
}

void primes() { //calculates and prints out the first 50 prime numbers 

	int i;
	int j;
	int count = 0;

	printf("Prime Numbers:\n");

	for (i = 2; i < 230; i++) { //the first 50 prime numbers are from 2-229 so this loop runs enough times for 50 primes numbers to be printed out lol
		count = 0;
		for (j = 2; j < i; j++) {
			if (i % j == 0) { //if j evenly divides into i, then i is not a prime number
				count = 1;
			}
		}
		if (count == 0) //if the count is zero that means i was not divisible by any j values and therefor is prime
			printf("%d ", i);			
	}

	printf("\n");
}

void fibonacci() { //calculates the first 50 numbers in the fibonacci sequence 

	long long x = 0;
	long long y = 1;
	long long z;
	int i;

	printf("Fibonacci Sequence:\n");
	printf("%lld ", y); 

	for (i = 1; i < 50; i++) {
		z = x + y; //adds the first two numbers together
		printf("%lld ", z); //prints out the sum
		x = y; //updates x to the next sequential number
		y = z; //updates y to the next suquential number
	}

	printf("\n");
}

void collatz() { //uses some fancy math to determine the amount of steps it takes for a number to reach one, doing different math depending on if the number is even or odd

	int i;
	int n;
	int count;

	printf("Collatz Stopping Times:\n");

	for (i = 1; i <= 50; i++) { //runs 50 times
		n = i;
		count = 0; //keeps track of the steps taken
		while (n != 1) { //if n is 1 then you have calculated the stopping time
			if (n % 2 == 0)  //if i is even then do this math
				n = n / 2;
			else //otherwise n is odd and you should do this math
				n = 3 * n + 1;
			count++; //thou count shall be updated until n reaches 1 (which it apparently always will at some point)	
		}
		printf("%d ", count); 
	}

	printf("\n");

}

void happyNum() { //determines the mood of a specific number 
    printf("Happy Numbers:\n");
    int count = 0;
    int i;
    int j;
    int k;
    //keeps track of the number of happy numbers
    for(i = 1; count <= 50; i++){
        j = i;
        k = 0;
        //continues to square numbers digits and add them together until 4 or 1 is returned
        while(k != 4 && k !=1){
            k = 0;
            //divides j until there isn't enough to divide
            while(j > 0) {
                k = (j % 10) * (j % 10) + k;
                j /= 10;
            }
            j = k;
        }
        //determines if the number is happy
        if(k == 1){
            printf("%d ", i);
            count = count + 1;
        }            
    }
    printf("\n");
}










