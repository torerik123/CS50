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

//TODO: Keep track of remaining change owed
int quarters = 0; //0.25
int dimes = 0;   //0.10
int nickels = 0;  //0.05
int pennies = 0;  // 0.01

int remainder = cents;


do // Make one loop for each
{
    if (remainder - 25 > -1) // Quarters
    {
        remainder = remainder - 25;
        quarters++;
    }

    if (remainder - 10 > -1) // Dimes
    {
        remainder = remainder - 10;
        dimes++;
    }

    if (remainder - 5 > -1) // Nickels
    {
        remainder = remainder - 5;
        nickels++;
    }

    if (remainder - 1 > -1) // Pennies
    {
        remainder = remainder - 1;
        pennies++;
    }

    else
    break;

}
while(remainder >= 0);

printf("Quarters: %i\nDimes: %i\nNickels: %i\nPennies: %i\n", quarters, dimes, nickels, pennies);
}