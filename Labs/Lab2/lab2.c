#include <stdio.h>
#include "convert.h"

int main() {

	int c = getchar();

	while (c != EOF) {
		if (c != LF)
			putchar(c);
		c = getchar();	
	}
	return 0;
}
