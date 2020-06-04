#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{


    //  Check for valid command line argument - name of image to recover

    //  If more than one command line argument, remind user of correct usage and main should return 1
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //  Open memory card if argv[1] exists
    FILE *file = fopen(argv[1], "r");

    // Returns 1 if the forensic image cannot be opened for reading
    if (file == NULL)
    {
        return 1;
    }

    else
    {

    //  Look for beginning of JPEG
    //  Buffer array to store block to read
    unsigned char buffer[512];

    //  Count JPEGS
    int jpgcounter = 0;

    //  Make filename - Array to store 7 ints (000.jpg) + NULL character
    char name[8];

    FILE* img = NULL;

    //  Loops until end of card - When fread can not read any more bytes the condition will be false
    while (fread(buffer, 512, 1, file) == 1)
    {
        //  If start of new JPEG
        if (buffer[0] == 0xff
            && buffer[1] == 0xd8
            && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            //  If first JPEG
            if (jpgcounter == 0)
            {
                //  Print string to filename
                sprintf(name,"%03i.jpg", jpgcounter);

                //  Open new JPEG file to write to
                img = fopen(name, "w");

                //  Write 512 bytes from buffer array into img
                fwrite(buffer,512,1, img);
                jpgcounter++;
            }

            else
            {
                fclose(img);
                
                //  Print string to filename
                sprintf(name,"%03i.jpg", jpgcounter);
                //  Open new JPEG file to write to
                img = fopen(name, "w");
                
                //  Write 512 bytes from buffer array into img
                fwrite(buffer,512,1, img);
                jpgcounter++;
            }
        }

        //  If it is not the start of a JPEG, that means we have already started writing to a file
        else
        {
            if (jpgcounter > 0) // If # of JPEGS is more than 0, meaning it is not the first JPEG
            {
                //  Write 512 bytes from buffer array into img
                fwrite(buffer,512,1, img);
            }
        }
    }
    printf("JPEGS found: %i\n", jpgcounter);

    //  Close remaining files
    fclose(img);
    }
}
