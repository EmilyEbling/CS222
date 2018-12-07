#include <iostream>
#include <string>

using namespace std;

string getName(int value);
string getTens(int value);
string getTeens(int value);

int main() {

	int number;
	int ones;
	int tens;
	int hundreds;
	string word;
	
	cout << "Enter a number: (0-999) ";

	cin >> number;

	if (number == 0) {
		cout << "Your number in words: zero" << endl;
		return 0;
	}

	ones = number%10;
	number = number/10;

	tens = number%10;
	number = number/10;

	hundreds = number;

	if (hundreds == 0 && tens > 1)
		word = getTens(tens) + " " + getName(ones);
	
	else if (hundreds == 0 && tens == 1)
		word = getTeens(ones);	

	else if (hundreds == 0 && tens == 0)
		word = getName(ones);

	else { 
		if (tens > 1)
			word = getName(hundreds) + " hundred " + getTens(tens) + " " + getName(ones);
		else if (tens == 1)
			word = getName(hundreds) + " hundred " + getTeens(ones);
		else if (tens == 0)
			word = getName(hundreds) + " hundred " + getName(ones);
	}

	cout << "Your number in words: " << word << endl;

	return 0;
}

string getName(int value) {
	
	switch (value) {
	case 1: return "one";
	case 2: return "two";
	case 3: return "three";
	case 4: return "four";
	case 5: return "five";
	case 6: return "six";
	case 7: return "seven";
	case 8: return "eight";
	case 9: return "nine";
	}
	
	return "";

}

string getTens(int value) {

	switch (value) {
	case 2: return "twenty";
	case 3: return "thirty";
	case 4: return "forty";
	case 5: return "fifty";
	case 6: return "sixty";
	case 7: return "seventy";
	case 8: return "eighty";
	case 9: return "ninty";
	}
	
	return "";

}

string getTeens(int value) {

	switch (value) {
	case 0: return "ten";
	case 1: return "eleven";
	case 2: return "twelve";
	case 3: return "thirteen";
	case 4: return "fourteen";
	case 5: return "fifteen";
	case 6: return "sixteen";
	case 7: return "seventeen";
	case 8: return "eighteen";
	case 9: return "nineteen";
	}
	
	return "";

}


