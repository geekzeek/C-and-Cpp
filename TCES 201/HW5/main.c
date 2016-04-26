/*  Zeeshan Karim
    CES 201
    Autumn 2014
    This program generates 100 random numbers, stores them in a file,
    and reads that file to convert the numbers to hexadecimal and binary
    to write to another file
*/
#include <stdio.h>
#include <stdlib.h>

#define RANDOM_MAX 100
#define RANDOM_MIN 10

int random_number_file_generator();
void hex_and_binary_file_generator(char *);
void convert_decimal_to_hex(int, char *);
int convert_decimal_to_binary(int);

int main()
{
    // This function calls other functions, to generate a random number file
    // and generate the hex and decimal file
    char hex[2];
    int success = 1;
    success = random_number_file_generator();
    if(success == 1)
    {
        hex_and_binary_file_generator(hex);
    }
    return 0;
}

int random_number_file_generator()
{
    // This function uses a pseudo random number generator to
    // write 100 random numbers to a .txt file

    int random, success = 1, i = 0;
    FILE *outfile;
    outfile = fopen("randomNumbers.txt", "w");
    if(outfile == NULL)
        {
            success = 0;
        }
    while(i<100)
    {
        srand(time());
        random = ((rand()%(RANDOM_MAX-RANDOM_MIN)) + RANDOM_MIN);
        fprintf(outfile, "%d\n", random);
        i++;
    }
    fclose(outfile);
    return success;
}

void hex_and_binary_file_generator(char *hex)
{
    //This function reads the random number file and writes a new file
    //with the hex, binary, and decimal versions of the random number
    char input[3];
    int number;
    FILE *infile;
    FILE *outfile2;
    infile = fopen("randomNumbers.txt", "r");
    outfile2 = fopen("hexAndBinary.txt", "w");
    while(fgets(input, 4, infile) != NULL)
    {
        number = atoi(input);
        if (number > 255)
        {
            puts("Error, number is too large");
            fprintf(outfile2, "Error, the number is too large\n");
        }
        if(number<0)
        {
            puts("Error, number is too small");
            fprintf(outfile2, "Error, the number is too small\n");
        }
        convert_decimal_to_hex(number, hex);
        fprintf(outfile2, "0x%2s ", hex);
        fprintf(outfile2, "%08d", convert_decimal_to_binary(number));
        fprintf(outfile2, " (%d)\n", number);
    }
    fclose(outfile2);
    fclose(infile);
}

void convert_decimal_to_hex(int n, char *hex)
{
    {
    int i=1,remainder;
    while (n!=0)
    {
        remainder=n%16;
        switch(remainder)
        {
            case 10:
              hex[i]='A';
              break;
            case 11:
              hex[i]='B';
              break;
            case 12:
              hex[i]='C';
              break;
            case 13:
              hex[i]='D';
              break;
            case 14:
              hex[i]='E';
              break;
            case 15:
              hex[i]='F';
              break;
            default:
              hex[i]=remainder+'0';
              break;
        }
        --i;
        n/=16;
    }
    hex[2]='\0';
}

int convert_decimal_to_binary(int n)
{
    int temp, factor=1, binary=0;
    while (n!=0)
    {
            temp=n%2;
            n/=2;
            binary+=temp*factor;
            factor*=10;
    }
    return binary;
}

