/*  Zeeshan Karim
    Autumn 2014
    CES 201
    This program takes user input and checks it against a .txt file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRL 60

int load_array(char list[][STRL]);
int find_string(char list[][STRL], const char *search, int tnames);

int main()
{
    char list[STRL][STRL];
    char search[STRL];
    char repeat;
    int tnames, success;
    tnames = load_array(list);
    if(tnames == -1)
    {
        puts("Error opening file");
        return (-1);
    }
    do
    {
        puts("\n\nEnter a name to search for:\n");
        gets(search);
        success = find_string(list, search, tnames);
        if (success)
        {
            puts("\nSuccess! The name entered in on the list.\n");
        }
        if(!success)
        {
            puts("\nFailure! The name entered is not on the list.\n");
        }
        printf("Do you want to search again?(y/n): ");
        scanf("%c", &repeat);
        getchar();
    }while(repeat == 'y' || repeat == 'Y');
    return 0;
}

int load_array(char list[][STRL])
{
    int i=0;
    FILE *in = fopen("search_list.txt", "r");
    if (in == NULL)
    {
        return(-1);
    }
    while (fgets(list[i], STRL, in) != NULL)
    {
        printf("%s", list[i]);
        i++;
    }
    fclose(in);
    return i;
}

int find_string(char list[][STRL], const char *search, int tnames)
{
    int i, length = strlen(search);
    for(i=0; i<tnames; i++)
    {
        if(!strncmp(list[i], search, length))
        {
            return 1;
        }
    }
    return 0;
}
