#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])  //User provides command line argument with what the key should be in the secret message.
{

    //  Check that program was run with one command-line argument
    if (argv[2] != 0)
    {
        printf("Usage: ./caesar key\n");
        //Return 1 signalling error
    }



    // Check if command-line argument is valid
    else if (argv[1] > 0)
    {
        int n = strlen(argv[1]);

        for (int i = 0; i < n; i++ ) // Checks if user input is all digits.
        {
            if (isdigit(argv[1][i])) // Executes if i is a number
            {

            }

            else
            {
                printf("Usage: ./caesar key\n");
                return 1;                               //  returns an error and terminates program

            }
        }
        printf("Success\n");

        //  Converts command line argument to int and stores in key
        int key = atoi(argv[1]);

        //  Prompt user for plaintext
        string plaintext = get_string("Plaintext:\n");
        int length = strlen(plaintext);

        //  Create array for ciphertext
        string ciphertext[length];

        printf("Ciphertext:");

            //  Iterate over each character of the plaintext:   TODO: Add ciphertext to array
            for (int i = 0; i < length; i++)
                if (isalpha(plaintext[i]))                  // Checks if plaintext is an alphabetic character
                {
                    if (isupper(plaintext[i]))              //  If it is an uppercase letter, rotate it, preserving case, then print out the rotated character,     ASCII 65-90
                    {

                        int upper = plaintext[i] - 65;          //  Subract 65 to make alphabetical index starting from zero
                        int c = (upper + key) % 26;             //  Wrap around to beginning of index
                        c = c + 65;                             //  Add 65 to convert back to ASCII
                        printf("%c", (char)c);                  //  Print ciphertext character

                    }


                    else if (islower(plaintext[i]))         //  If it is a lowercase letter, rotate it, preserving case, then print out the rotated character,  ASCI 97-122
                    {
                        int upper = plaintext[i] - 97;          //  Subract 97 to make alphabetical index starting from zero
                        int c = (upper + key) % 26;             //  Wrap around to beginning of index
                        c = c + 97;                             //  Add 97 to convert back to ASCII
                        printf("%c", (char)c);                  //  Print ciphertext character
                    }

                }
                
                else if (ispunct(plaintext[i]))             //  If it is neither, print out the character as is
                {
                    printf("%c", plaintext[i]);
                }
            printf("\n");                                   //  Print a newline




    }









    //If your program is executed without any command-line arguments or with more than one command-line argument,
    //your program should print an error message of your choice (with printf)
    //and return from main a value of 1 (which tends to signify an error) immediately.





}