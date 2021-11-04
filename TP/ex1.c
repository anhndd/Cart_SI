#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUM_POWER_RECORD 29000

char *concatFilename(int numberFile)
{
    int i;
    char *file = (char *)malloc(20 * sizeof(char));
    strcat(file, "curves/demo_");
    int numberFill = 0;
    int num = numberFile;
    while (num > 9)
    {
        numberFill++;
        num /= 10;
    }
    numberFill = 3 - numberFill;

    for (i = 0; i < numberFill; i++)
    {
        strcat(file, "0");
    }
    char snum[20];
    sprintf(snum, "%d", numberFile);
    strcat(file, snum);
    return file;
}

int main()
{
    double average[NUM_POWER_RECORD];
    int i;
    for (i = 0; i < 2000; i++)
    {
        char *file = concatFilename(i);
        // printf("%s\n", file);

        int bufferLength = 255;
        char buffer[bufferLength];

        FILE *fptr;
        fptr = fopen(file, "r");
        if (fptr == NULL)
        {
            printf("No file\n");
            return -1;
        }
        int j = 0;
        char *eptr;

        if (i == 0)
        {
            while (fgets(buffer, bufferLength, fptr))
            {
                average[j] = strtod(buffer, &eptr);
                j++;
            }
        }
        else
        {
            while (fgets(buffer, bufferLength, fptr))
            {
                average[j] += strtod(buffer, &eptr);
                // printf("%f\n", average[j]);
                j++;
            }
        }
        fclose(fptr);
        free(file);
    }

    FILE *out_file = fopen("average.txt", "w");

    for(i=0;i<NUM_POWER_RECORD;i++){
        average[i] /= 2000;
        printf("%f\n", average[i]);
        fprintf(out_file,"%f\n",average[i]);
    }


    fclose(out_file);
    return 0;
}