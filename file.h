#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void readDoubleFileByLine(char *fileName, double* data)
{
    // printf("%s\n", file);
    int bufferLength = 255;
    char buffer[bufferLength];
    printf("%s\n", fileName);
    FILE *fptr;
    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        printf("No file, %s and\n",fileName);
        return;
    }
    int j = 0;
    char *eptr;

    while (fgets(buffer, bufferLength, fptr))
    {
        data[j] = strtod(buffer, &eptr);
        j++;
    }
    fclose(fptr);
}

char *readFile(char *fileName)
{
    char *buffer;
    FILE *fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        fseek(fp, 0L, SEEK_END);
        long stell = ftell(fp);
        rewind(fp);
        buffer = (char *)malloc(stell);
        if (buffer != NULL)
        {
            fread(buffer, stell, 1, fp);
            fclose(fp);
            fp = NULL;
        }
    }
    return buffer;
}

void readFileByLineKnownLength(char *fileName, char *strArray[], int nrows, int ncolumns)
{
    FILE *fp; // pointer to file
    int i, j;
    //char content[MAX_NUM_LINES][MAX_LINE_LENGTH];

    for (i = 0; i < nrows; i++)
    {
        strArray[i] = (char *)malloc(ncolumns * sizeof(char));
        for (j = 0; j < ncolumns; j++)
        {
            strArray[i][j] = 0;
        }
    }
    // // has file argument
    fp = fopen(fileName, "r");

    if (fp != NULL)
    {
        i = 0;
        while (fgets(strArray[i], ncolumns, fp))
        {
            fgetc(fp);
            i++;
        }
    }
    fclose(fp);
}

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

int hexbyte2int(char chl, char chr)
{
    int number = hex2int(chl);
    int number2 = hex2int(chr);
    return number2 + number * 16;
}

int hex2intArray(char *hexStr, char *hex)
{
    int i, j = 0;
    int size = strlen(hexStr);
    for (i = 0; i < size; i += 2)
    {
        hex[j] = hexbyte2int(hexStr[i], hexStr[i + 1]);
        j++;
    }
}