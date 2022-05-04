#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check for valid usage
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    //check for valid file
    if (!file)
    {
        printf("can't open");
        return 2;
    }

    BYTE bytes[512];
    FILE *img = NULL;
    bool first_jpg_flag = true;
    int found = 0;
    char filename[100];
    int file_number = 0;
    while (fread(&bytes, sizeof(BYTE), 512, file))
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            //if jpg image found turn found = 1.
            found = 1;
            //if first jpg image found then turn first_jpg_flag false.
            if (first_jpg_flag == true)
            {
                first_jpg_flag = false;

            }
            else
            {
                //if its not the first jpg file then close the last open file.
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", file_number);
            img = fopen(filename, "w");
            fwrite(&bytes, sizeof(BYTE), 512, img);
            file_number += 1;
        }
        else if (found == 1)
        {
            //copy those blocks which follows the jpg image, till new jpg found.
            fwrite(&bytes, sizeof(BYTE), 512, img);
        }
    }
    fclose(img);
    fclose(file);
    return 0;
}