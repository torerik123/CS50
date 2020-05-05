#include <cs50.h>
#include <stdio.h>

int main(void)
{

    //Prompt user for credit card number

    long number = get_long("Number:\n");

    //TODO: Calculate checksum/Luhns algorithm:

    long slice = number;
    int remainder = 0;
    int multi = 0;
    int single = 0;
    int doubled = 0;
    int product = 0;
    int x = 0;
    int y = 0;
    int sum = 0;                        //sum of the total modulo of the two do/while loops
    long cardcheck = number;            //Used for counting length number
    int counter = 0;                    //Used for counting length number
    long startingnumber = number;


                                        // Counts the length of the number entered by the user
        while (cardcheck != 0)
                {
                    cardcheck /= 10;        // Divides by 10
                    counter++;              //increments counter by 1
                }








        do                          //This adds the digits that were not multiplied by 2
        {
            slice = slice/10;           //  Slice off the last number using %
            remainder = slice % 10;     //  Find remainder
            doubled = remainder * 2;    //  Multiply remainder by 2

            if (doubled >= 10)          //  Adds the numbers in doubled together if the result is more than 10
                {
                    x = doubled % 10;
                    y = doubled / 10;
                    x = doubled % 10;
                    product = x + y;
                    multi = multi + product;
                }

                                        //  If doubled is not more than 10, it just adds the number to the sum
            else
            {
                multi = doubled + multi;
            }

            slice = slice/10;

        }

        while (slice > 0);




        do                                  //This adds the digits that were not multiplied by 2
        {
            single = single + (number % 10);    //Finds the last digit of number
            number = number / 100;              //Divides by 100 to get to the next number to add to sum

        }

    while (number > 0);

    sum = multi + single;

    //  Executes if the total modulo is congruent to 10, aka the number ends with zero
    if (sum % 10 == 0)
        {

            //  VISA: 13 or 16 digits, Starts with 4
            if ((counter == 16 | counter == 13) && (startingnumber / 1000000000000000 == 4 | startingnumber / 1000000000000 == 4))
            printf("VISA\n");

            //  AMEX: 15 digits, Starts with 34 or 37
            else if ((counter == 15) && (startingnumber / 10000000000000 == 34 | startingnumber / 10000000000000 == 37))
            printf("AMEX\n");


            //  MASTERCARD: 16 digits, Starts with 51, 52, 53, 54, or 55
            else if ((counter == 16) && (startingnumber / 100000000000000 == 51 | startingnumber /  100000000000000 == 52 | startingnumber /  100000000000000 == 53 |
            startingnumber /  100000000000000 == 53 | startingnumber /  100000000000000 == 54 | startingnumber /  100000000000000 == 55 ))
            printf("MASTERCARD\n");

            else
            printf("INVALID\n");

        }
    
    else if (sum % 10 != 0)
        {
            printf("INVALID\n");
        }    
}
