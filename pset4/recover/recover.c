#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // Check number of arguments - argv[]
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open memory card file
    FILE *raw_file = fopen(argv[1], "r");

    // Set the start to the first BYTE
    fseek(raw_file, 0, SEEK_SET);

    // Check if file is not NULL
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // Create a buffer of 512 bytes and variables
    BYTE buffer[512];
    int jpeg_number = 0;
    char jpeg_name[8];
    FILE *img = NULL;

    // While loop 'til EOF
    while (fread(buffer, 512, 1, raw_file) == 1)
    {
        // If found start of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If this is not the first JPEG file
            if (jpeg_number != 0)
            {
                // Close last JPEG
                fclose(img);
            }

            // Open new JPEG
            sprintf(jpeg_name, "%03i.jpg", jpeg_number);

            img = fopen(jpeg_name, "w");

            // Write 512 bytes to JPEG file
            fwrite(buffer, 512, 1, img);

            jpeg_number++;
        }
        // If not find start of JPEG file
        else
        {
            // If already find a JPEG
            if (jpeg_number != 0)
            {
                // 5 Write 512 bytes to JPEG file
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    fclose(raw_file);
    fclose(img);
    return 0;

}
