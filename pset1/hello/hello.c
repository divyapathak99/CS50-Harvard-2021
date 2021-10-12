#include<stdio.h>
#include<cs50.h>

int main()
{
    string name = get_string("what is your name? "); //asking user to enter.
    printf("Hello, %s!\n", name);
    
}