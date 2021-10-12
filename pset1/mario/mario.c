#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int n, l;
    //accepting only positive integer in the range (1,8).
    do
    {
        //get positive integer from user
        n = get_int("Height: ");

    }
    while (n < 1 || n > 8);
    
    for (int i = 1; i <= n; i++) //this loop creates the pattern vertically.
    {
        l = n - i;
        for (int k = 0; k < l; k++) 
        {
            printf(" "); 
        }
        for (int j = 0; j < 2 * i; j++) //this loop creats the pattern horizontally.
        {

            if (j == i)
            {
                printf("  ");

            }
            printf("#");

        }
        printf("\n");
        
    }
}