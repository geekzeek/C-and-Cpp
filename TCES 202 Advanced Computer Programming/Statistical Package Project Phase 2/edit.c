#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "global.h"
#include "edit.h"
#include "file.h"
#include "screen_utils.h"

/* edit the contents of an open file */
int edit_main_menu(void)
{
    int selection = 0;
    int error = NO_ERROR;

    while (selection != 4)
    {
        clear_screen();
        selection = edit_menu();
        switch (selection)
        {
            case EDIT_ADD_SEL:
            {
                error = edit_add();
                if (error)
                    printf("Error in opening file ...: Check to make sure filename is correct and file exists.\n");
                break;
            }
            case EDIT_EDIT_SEL:
            {
                error = edit_edit();
                if (error)
                    printf("Error in opening file ...: Check to make sure filename is correct and file exists\n");
                break;
            }
            case EDIT_DELETE_SEL:
            {
                error = edit_delete();
                if (error)
                    printf("Error in opening file ...: Check to make sure filename is correct and file exists\n");
                break;
            }
        }
    }
    clear_screen();

    return NO_ERROR;
}

// Validation for the edit menu selection
int edit_menu(void)
{
    char sel_s[3];
    int sel;

    print_edit_menu();
    gets(sel_s);
    sel = atoi(sel_s);
    if ((sel < EDIT_ADD_SEL || sel > EDIT_DELETE_SEL) && sel != 4)
    {
        while (1) {
            clear_screen();
            printf("Incorrect selection. Please enter one of these choices.\n");
            print_edit_menu();
            gets(sel_s);
            sel = atoi(sel_s);
            if (!((sel < EDIT_ADD_SEL || sel > EDIT_DELETE_SEL)
                  && sel != EXIT_SEL))
                break;
        }
    }
    return sel;
}

// Prints the different edit menu choices.
void print_edit_menu(void)
{
    printf("StatPac Edit menu options.\n");
    printf("File Menu: 1) Add New Data 2) Edit Existing Data 3) Delete Data 4) Exit\n");
    printf("Please choose an option: ");
    fflush(stdout);
}


/**********************************************************************************************/
/* allows users to add any number of new data items to the file.
 */
int edit_add(void)
{
    char filename[MAX_FILE_NAME_LEN], buffer[256];
    int i;
    float *array, number;
    FileHeaderPtr fh_p = NULL;

    /** Open the file, read its contents, and store the values in array. Store the header in fh_p **/

    i = 0;
    printf("\nEnter filename you wish to add data to: ");
    gets(filename);
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return FILE_ERROR;        // return error if opening file fails
    }
    fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header
    if(fh_p == NULL)
    {
        fclose(fp);
        return FILE_ERROR;
    }
    get_file_header(fh_p, fp);// retrieve file header, advance fp to new line.
    array = malloc((fh_p->num_records)* sizeof(float)); // allocate memory to array based on number of entries
    if(array == NULL)
    {
        puts("Error allocating memory");
        fclose(fp);
        free(fh_p);
        fh_p = NULL;
        return FILE_ERROR;
    }
    while(fgets(buffer, 256, fp) !=  NULL)//retrieve line from file and insert to buffer
    {
        if(buffer[strlen(buffer)-1] == '\n')//remove newline character
        {
            buffer[strlen(buffer)-1] = NULL;
        }
        number = atof(buffer);// convert buffer string to float
        array[i] = number; // assign number to array
        printf("%d: %.6f\n", (i+1), array[i]);
        i++;
    }
    fclose(fp);

    /** Gets new data from user and adds to array **/

    puts("\n");
    while(1)
    {
        printf("Enter data to add (q to quit): ");
        gets(buffer);
        if(buffer[strlen(buffer)-1] == '\n')//remove newline character
        {
            buffer[strlen(buffer)-1] = NULL;
        }
        if(buffer[0] == 'q') // exit if response is q
        {
            break;
        }
        array = realloc(array, (fh_p->num_records + 1)*sizeof(float)); // allocate additional memory to array for new data
        array[fh_p->num_records] = atof(buffer); // convert to float and add to end of array
        fh_p->num_records++; // advance count of records
    }
    printf("\n");
    for(i = 0; i<fh_p->num_records; i++)
    {
        printf("%d: %f\n", (i + 1), array[i]);
    }
    printf("\nAdding data complete. Closing %s ...\n", filename);
    press_enter();

    /** Update Modification date **/

    char date[26];
    time_t timer;
	struct tm *timeinfo;
	time(&timer);
	timeinfo = localtime(&timer);
	strcpy(date, (char *) asctime(timeinfo));
	date[24] = 0;
	strcpy(fh_p->modification_date, date);

    /** Reopens file for writing, deleting content, and writes new file header and data to it **/

    fp = fopen(filename, "w");
    fprintf(fp, "%s,%s,%s,%s,%ld,%s,%f,%f,%f,%f", fh_p->filename, // print new file header
				fh_p->creation_date, fh_p->modification_date, fh_p->owner,
				fh_p->num_records, "entry", fh_p->mean, fh_p->median, fh_p->variance,
				fh_p->std_dev);
    for(i=0; i<fh_p->num_records; i++)
    {
        fprintf(fp, "\n%f", array[i]);
    }
    fclose(fp);

    /** Free memory and return **/

    fh_p = NULL;
    free(fh_p);
    array = NULL;
    free(array);

    return NO_ERROR;

}

/**********************************************************************************************/
int edit_edit()
{
    char filename[MAX_FILE_NAME_LEN], buffer[256];
    int i;
    float number;
    float *array = NULL;
    FileHeaderPtr fh_p = NULL;

    /** Open the file, read its contents, and store the values in array. Store the header in fh_p **/

    i = 0;
    printf("\nEnter filename you wish to edit: ");
    gets(filename);
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return FILE_ERROR;        // return error if opening file fails
    }
    fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header
    if(fh_p == NULL)
    {
        fclose(fp);
        return FILE_ERROR;
    }
    get_file_header(fh_p, fp);// retrieve file header, advance fp to new line.
    if(array == NULL)
    {
        array = malloc((fh_p->num_records)* sizeof(float)); // allocate memory to array based on number of entries
    }
    if(array == NULL)
    {
        puts("Error allocating memory");
        fclose(fp);
        free(fh_p);
        fh_p = NULL;
        return FILE_ERROR;
    }
    while(fgets(buffer, 256, fp) !=  NULL)//retrieve line from file and insert to buffer
    {
        if(buffer[strlen(buffer)-1] == '\n')//remove newline character
        {
            buffer[strlen(buffer)-1] = NULL;
        }
        number = atof(buffer);// convert buffer string to float
        array[i] = number; // assign number to array
        printf("%d: %.6f\n", (i+1), array[i]);
        i++;
    }
    fclose(fp);

    /** Gets new data and index from user and inserts data into array **/

    while(1)
    {
        if(fh_p->num_records == 0)
        {
            printf("\                                                        nNo records to edit, please add data.\n");
            press_enter();
            return NO_ERROR;
        }
        printf("\nEnter the record number to edit, or 0 to quit: 1 - %d: ", fh_p->num_records);
        scanf("%d", &i);
        if(i == 0)
        {
            break;
        }
        while(i < 0 || i > fh_p->num_records)
        {
            printf("\nIncorrect selection, please enter a record between 1 and %d: ", fh_p->num_records);
            scanf("%d", &i);
        }
        printf("Enter a new value for record %d, data %f : ", i, array[i-1]);
        scanf("%f", &array[i-1]);
    }

    printf("\n");
    for(i = 0; i<fh_p->num_records; i++)
    {
        printf("%d: %f\n", (i + 1), array[i]);
    }
    printf("\nEditing data complete. Closing %s ...\n", filename);
    getchar();
    press_enter();

    /** Update Modification date **/

    char date[26];
    time_t timer;
	struct tm *timeinfo;
	time(&timer);
	timeinfo = localtime(&timer);
	strcpy(date, (char *) asctime(timeinfo));
	date[24] = 0;
	strcpy(fh_p->modification_date, date);

    /** Reopens file for writing, deleting content, and writes new file header and data to it **/

    fp = fopen(filename, "w");
    fprintf(fp, "%s,%s,%s,%s,%ld,%s,%f,%f,%f,%f", fh_p->filename, // print new file header
				fh_p->creation_date, fh_p->modification_date, fh_p->owner,
				fh_p->num_records, "entry", fh_p->mean, fh_p->median, fh_p->variance,
				fh_p->std_dev);
    for(i=0; i<fh_p->num_records; i++)
    {
        fprintf(fp, "\n%f", array[i]);
    }
    fclose(fp);

    /** Free memory and return **/

    fh_p = NULL;
    free(fh_p);
    array = NULL;
    free(array);


    return NO_ERROR;
}

/**********************************************************************************************/
int edit_delete(void)
{
    char filename[MAX_FILE_NAME_LEN], buffer[256];
    int i, counter;
    float *array, number;
    FileHeaderPtr fh_p = NULL;

    /** Open the file, read its contents, and store the values in array. Store the header in fh_p **/

    i = 0;
    printf("\nEnter filename you wish to delete data from: ");
    gets(filename);
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return FILE_ERROR;        // return error if opening file fails
    }
    fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header
    if(fh_p == NULL)
    {
        fclose(fp);
        return FILE_ERROR;
    }
    get_file_header(fh_p, fp);// retrieve file header, advance fp to new line.
    array = malloc((fh_p->num_records)* sizeof(float)); // allocate memory to array based on number of entries
    if(array == NULL)
    {
        puts("Error allocating memory");
        fclose(fp);
        fh_p = NULL;
        free(fh_p);
        return FILE_ERROR;
    }
    while(fgets(buffer, 256, fp) !=  NULL)//retrieve line from file and insert to buffer
    {
        if(buffer[strlen(buffer)-1] == '\n')//remove newline character
        {
            buffer[strlen(buffer)-1] = NULL;
        }
        number = atof(buffer);// convert buffer string to float
        array[i] = number; // assign number to array
        printf("%d: %.6f\n", (i+1), array[i]);
        i++;
    }
    fclose(fp);

    /** Gets index to delete from user, and removes element from array **/

    if(fh_p->num_records == 0)
    {
        printf("\nNo records to delete, please add data. \n\n");
        press_enter();
        return NO_ERROR;
    }
    while(1)
    {
        if(fh_p->num_records == 0)
        {
            printf("No records remaining, please add data.");
            press_enter();
            break;
        }
        printf("\nEnter the record number to delete, or 0 to exit (1 - %d): ", fh_p->num_records);
        scanf("%d", &i);
        while(i < 0 || i > fh_p->num_records)
        {
            printf("\nIncorrect selection, please enter a record between 1 and %d: ", fh_p->num_records);
            scanf("%d", &i);
        }
        if(i == 0)
        {
            break;
        }
        clear_screen();
        printf("Record %d removed.\n\n", i);
        for(counter = 0; counter<fh_p->num_records - 1; counter++)
        {
            if(counter >= i-1)
            {
                array[counter] = array[counter + 1];
            }
            printf("%d: %.6f\n", counter + 1, array[counter]);
        }
        fh_p->num_records--;
    }




    /** Update Modification date **/

    char date[26];
    time_t timer;
	struct tm *timeinfo;
	time(&timer);
	timeinfo = localtime(&timer);
	strcpy(date, (char *) asctime(timeinfo));
	date[24] = 0;
	strcpy(fh_p->modification_date, date);

    /** Reopens file for writing, deleting content, and writes new file header and data to it **/

    fp = fopen(filename, "w");
    fprintf(fp, "%s,%s,%s,%s,%ld,%s,%f,%f,%f,%f", fh_p->filename, // print new file header
				fh_p->creation_date, fh_p->modification_date, fh_p->owner,
				fh_p->num_records, "entry", fh_p->mean, fh_p->median, fh_p->variance,
				fh_p->std_dev);
    for(i=0; i<fh_p->num_records; i++)
    {
        fprintf(fp, "\n%f", array[i]);
    }
    fclose(fp);

    /** Free memory and return **/

    fh_p = NULL;
    free(fh_p);
    array = NULL;
    free(array);
    getchar();

    return NO_ERROR;
}

