#include <stdio.h>


int my_write(char c) {
    return write(1, &c, 1);
}

void my_putnbr(int c) {
    
    const int ASCII_ORIGIN = 48;
    
    int reverse = 0;
    while (c > 0) {
        reverse = reverse * 10 + c % 10;
        c = c / 10;
    }
    
    int dig = 0;
    
    if (reverse == 0) {
        my_write(dig + ASCII_ORIGIN);
    } else {
        while(reverse) {
            dig = reverse % 10;
            my_write(dig + ASCII_ORIGIN);
            reverse = reverse / 10;
        }
    }
    // print the number using only my_write
    // read ascii table to convert digit to character
}

int main(void) {
    my_putnbr(12345); // should print 12345
	return 0;
}