/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2DHIF
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Pyramid of Numbers
 * Author:			Pirngruber Christian
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];

};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int str_tobigint(const char *str, int len, struct BigInt *big_int){
	int converted =0;
		int count = len;
		len -= 1;
		for (size_t i = 0; i < count; i++) {
			if (str[len] < '0' || str[len] > '9')
			{
				return 0;
			}
			big_int->the_int[i] = str[len] - '0';
			converted++;
			len--;
		}
		big_int->digits_count = converted;
		return converted;
}

/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int){
	bool notnulldigitfound = false;
		for (int i = 0; i < big_int->digits_count; i++) {
			if (big_int->the_int[i] > 0 || notnulldigitfound == true)
			{
							printf("%d",big_int->the_int[i]);
							notnulldigitfound = true;
			}
		}
}
/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result){
	int carry = 0;
	int temp;
	int count = big_int->digits_count;
	big_result->digits_count = big_int->digits_count;

	for (int i = 0; i < count; i++) {
	temp=big_int->the_int[i] * factor + carry;
	carry = 0;
	if (temp > 9) {
		if (i == big_int->digits_count-1)
		{
			big_result->digits_count++;
			big_result->the_int[i]=temp%10;
			big_result->the_int[i+1]=temp/10;
		} else {
			carry=temp/10;
			big_result->the_int[i]=temp%10;
		}
	}
	else
	{
		big_result->the_int[i]=temp;
	}
}
}


/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result){
	int carry = 0;
	int temp;
		for (int i = 0; i < big_int->digits_count; i++) {
			big_result->the_int[i] = 0;
			big_result->digits_count = i+1;
			temp = carry * 10 + big_int->the_int[i];
			if (temp >= divisor) {
				big_result->the_int[i] = temp / divisor;
				carry = temp % divisor;
			}
			else
			{
				carry = big_int->the_int[i];
			}

		}
}

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to){
 	from = to;
}


void reverse_Bigint(struct BigInt *big_int){
	int i = big_int->digits_count-1;
  int j = 0;
   while(i > j)
   {
     int temp = big_int->the_int[i];
		 int secondtemp = big_int->the_int[j];
     big_int->the_int[i] = secondtemp;
     big_int->the_int[j] = temp;
     i--;
     j++;
}
}
/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/

int main(int argc, char *argv[])
{
	struct BigInt bigint_result;
	struct BigInt bigint;
	struct BigInt bigint_division_result;
	char input[MAX_DIGITS];
	int len;
	int converted;
	int factor = 2;
	int divisor = 2;

	printf("Pyramid of Numbers\n");
	printf("==================\n");
	printf("\n");
	printf("Please enter a number: ");
	scanf("%s", input);

	len = strlen(input);
	converted = str_tobigint(input, len, &bigint);
	if (converted == 0)
	{
		return 0;
	}

	for (int i = 0; i < 8; i++) {
	multiply(&bigint,factor,&bigint_result);
	reverse_Bigint(&bigint_result);
	reverse_Bigint(&bigint);
	print_big_int(&bigint);
	printf(" * %d = ",factor);
	print_big_int(&bigint_result);
	printf("\n");
	reverse_Bigint(&bigint_result);
	reverse_Bigint(&bigint);
	bigint = bigint_result;
	factor++;
}
reverse_Bigint(&bigint_result);
for (int i = 0; i < 8; i++) {
	print_big_int(&bigint_result);
	divide(&bigint_result,divisor,&bigint_division_result);
	bigint_result = bigint_division_result;
	printf(" / %d = ",divisor);
	print_big_int(&bigint_division_result);
	printf("\n");
	divisor++;
}
	return 0;
}
