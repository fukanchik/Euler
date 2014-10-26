/*
 * Speed item 1:
 * There are 1110 palindromes in base 10
 * there are 1999 in base 2.
 * hence "if palindrome x in 10 && palindrome x in 2"
 * would be faster than
 * if palindrome in 2 && palindrome in 10.
 * Speed item 2:
 * Since problem states: palindromic # may not
 * include leading zeroes, the last digit in binary can not
 * be zero, which means only odd numbers may be palindromes.
 */
#include <stdio.h>

#include <euler/palindrome.h>

#define LIMIT 1000000

int
main(int argc, char* argv[])
{
	int sum;
	int i;

	for(sum = 0, i = 1; i < LIMIT; i += 2) {
		if(is_palindrome(i, 10) && is_palindrome(i, 2))
			sum += i;
	}

	printf("%d\n", sum);

	return 0;
}

