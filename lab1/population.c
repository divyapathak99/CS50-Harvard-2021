#include<stdio.h>
#include<cs50.h>

int main()
{
    int start_size, end_size, year = 0, n;
    // TODO: Prompt for start size
    do
    {
        start_size = get_int("start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    do
    {
        end_size = get_int("end size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    n = start_size;
    if (n == end_size)
    {
        year = 0;
    }
    else 
    {
        do
        {
            n = n + (n / 3) - (n / 4);
            year += 1;
            
        }
        while (n < end_size);
    }
 
    // TODO: Print number of years
    printf("Years: %i\n", year);
}