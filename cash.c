#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

float dollars; // initializing variable dollars

do
{
    dollars = get_float("Change: \n"); //Get user input and save in variable "dollars" as a float
}

while(dollars <= 0); //loops until condition is false, e.g. dollars is more than zero

int cents = round(dollars * 100); //- Multiply dollars by 100, Round cents to nearest penny

int counter = 0;
int remainder = cents;


do
{
    if (remainder - 25 > -1) // Quarters
    {
        remainder = remainder - 25;
        counter++;
    }

    else if (remainder - 10 > -1) // Dimes
    {
        remainder = remainder - 10;
        counter++;
    }

    else if (remainder - 5 > -1) // Nickels
    {
        remainder = remainder - 5;
        counter++;
    }

    else if (remainder - 1 > -1) // Pennies
    {
        remainder = remainder - 1;
        counter++;
    }

    else
    break;

}
while(remainder > 0 );


printf("%i\n", counter);
}