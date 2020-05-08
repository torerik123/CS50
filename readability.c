#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>




int main(void)

{
    string s = get_string("Text:\n");

    int n = strlen(s);
    int letters = 0;
    int words = 1;
    int sentences = 0;

    //  Count number of letters. Only count upper and lowercase letters, ignore spaces, punctuations etc.
    for (int i = 0; i < n; i++)
    {
        char array = s[i];

        if (islower(array) || (isupper(array)))     //  Counts upper and lowercase letters
        {
            letters++;                              //  Counts letters
        }
        
        if (isblank(array))                         // Any sequence of letters separated by a space is going to count as a word
        {
            words++;
        }

//  Counts sentences. Any punctuation mark, exclamation point or question mark counts as a sentence.
        if (s[i] == '.'                             
            || s[i] == '?'               
            || s[i] == '!')  
        {
            sentences++;
        }
    }

    

    //  Output grade level

    float l = ((float)letters / (float)words) * 100;
    float z = ((float)sentences / (float)words) * 100;

    float index = 0.0588 * l - 0.296 * z - 15.8;
    int grade = round(index);
    
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    
    else
    {
        printf("Grade %i\n", grade);
    }
}