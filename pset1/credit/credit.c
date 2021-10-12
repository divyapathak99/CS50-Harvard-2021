#include <stdio.h>
#include <cs50.h>
#include<math.h>

long type1(long x);
long type2(long x);
long digit(long x);
int add(long x);
int main()
{
    long x;
    int start_dts, start_dts1, sum, n ;
    x = get_long("Card number: ");
    n = digit(x);
    sum = type1(x) + type2(x);
    start_dts = x / (pow(10, n - 2)); //Initial two digits of card number.
    start_dts1 = x / (pow(10, n - 1)); //first digit of card number.
    if ((sum % 10) == 0)
    {
        if (n == 15 && (start_dts == 34 || start_dts == 37))
        {
            printf("AMEX\n");
        }
        else if (n == 16 && (start_dts == 51 || start_dts == 52 || start_dts == 53 || start_dts == 54 || start_dts == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((n == 13 || n == 16) && start_dts1 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");

    }

}

//1. Calculate checksum.
// 1.1 step 1. Multiplying every other digit of "card number" by 2, starting with 2nd to last digit.
long type1(long x)
{
    long c, d, e;
    int i = 0;
    c = x / 10;
    d = add((c % 10) * 2); // Here " c%10 " is the 2nd last digit.
    do
    {
        e = c / 100;
        c = e;
        d += add((e % 10) * 2);
        i += 1;

    }
    while (e != 0);
    return d;
}

//Calculate the sum of digits within a number.
int add(long x)
{
    int a, b;
    a = x % 10 ; //last digit.
    do
    {
        b = x / 10;
        a += b % 10;
        x = b;
    }
    while (b != 0);
    return a;
}

//1.2 step 2: Sum of the digits of "card number" that weren't multiply by 2.
long type2(long x)
{
    long b, a;
    int i = 0;
    a = x % 10;  //last digit.
    do
    {
        b = x / 100;
        a += b % 10; //non multiply digits.
        i += 1;
        x = b;

    }
    while (b != 0);
    return a;
}

//calculate number of digits in "card number".
long digit(long x)
{
    int i = 0;
    
    
    long a;
    do
    {
        a = x / 10;
        i += 1;
        x = a;

    }
    while (a != 0);
    return i;
}
