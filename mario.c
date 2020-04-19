
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n; //creates integer named n
    do     //do the following n times:
    {
     n = get_int("Height:\n"); //takes a number from the user and stores it in variable n
    }
     while (n < 1 || n > 8); //if n is less than 1, run loop again.
     for (int i = 0; i < n ; i++) // Height = vertical columns
     {
         for (int j = 0; j < n; j++)
         {
             if (i + j < n -1)
                printf(" ");
            else
                printf("#");
         }
         printf("\n");
     }
} 
