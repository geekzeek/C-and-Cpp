/*
 File Menu
 file.c
 
 Brian G. Hess
 TCES202
 Winter 2015
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "global.h"
#include "screen_utils.h"
#include "file.h"

/* Called from the main menu, this menu gets the user's selections for how to work with the files. Calls the file_menu to get a valid selection. Based on the selection, calls the appropriate file functions.
 */
int file_main_menu(void)
{
    int selection=0;
    int error_code = NO_ERROR;
    
    while (selection != EXIT_FILE_SEL)
    {
        selection = file_menu();
        switch (selection)
        {
            case CREATE_SEL:
            {
                file_create();
                break;
            }
            case OPEN_SEL:
            {
                file_open();
                break;
            }
            case RENAME_SEL:
            {
                file_rename();
                break;
            }
            case COPY_SEL:
            {
                file_copy();
                break;
            }
            case PRINT_SEL:
            {
                file_print();
                break;
            }
            case DELETE_SEL:
            {
                file_delete();
                break;
            }
        }
    }
    return 0;
}


/* gets the selection from the file menu. It calls print_file_menu() to put the menu on the screen. If the
 user enters an invalid selection they are given opportunities to get it right.
 */
int file_menu(void)
{
    char sel_s[3];
    int sel;
    
    print_file_menu();
    gets(sel_s);
    sel = atoi(sel_s);
    if (sel < CREATE_SEL || sel > EXIT_FILE_SEL)
    {
        while (sel!=EXIT_FILE_SEL)
        {
            clear_screen();
            printf("Incorrect selection. Please enter one of these choices: ");
            print_file_menu();
            gets(sel_s);
            sel = atoi(sel_s);
            if (!(sel < CREATE_SEL || sel > EXIT_FILE_SEL)) break;
        }
    }
    return sel;
}


/* prints the file menu options to the screen. Is called from multiple places.
 * File Menu: 1) New 2) Open 3) Rename 4) Copy 5) Print 6) Delete 7) Exit\n")
 */
void print_file_menu(void)
{
    printf ("STATPAC File Menu Options.\n");
    printf ("File Menu: 1) NEW, 2) OPEN, 3)RENAME, 4) COPY, 5) PRINT, 6) DELETE, 7) EXIT\n");
    printf ("Please Choose an Option:");
}

/************************************************************************************************
 Menu-called Functions
 These are the functions that implement the menu options for the file management system
 
 ************************************************************************************************/

/* gets user input for new file name, checks to make sure no file of that type already
 exists, if it doesn't exist it creates the file and initializes the header lines (see below)
 */
int file_create(void)
{
    char file_name [MAX_FILE_NAME_LEN];
    FILE *fp;
    FileHeaderPtr fhp = malloc(sizeof(struct file_header));
    printf ("File Creation:\n");
    printf ("Please Enter the File Name You Wish to Create:");
    gets (file_name);
    if (fopen (file_name, "r") == NULL)
    {
        fp = fopen (file_name, "a+");
    }
    else
    {
        printf ("File Name Already Exists.");
        return NO_ERROR;
    }
    init_file_header(fhp, file_name);
    printf("File: %s\nCreated: %s\nModified: %s\nOwner: %s\nRecords: %d\nState: NEW\nMean: %f\nMedian: %f\nVariance: %f\nStd. Dev: %f\n",
           fhp->filename, fhp->creation_date, fhp->modification_date,
           fhp->owner, fhp->num_records, fhp->mean, fhp->median,
           fhp->variance, fhp->std_dev);
    fprintf (fp, "%s, %s, %s, %s, %d, NEW, %f, %f, %f, %f\n",
             fhp->filename, fhp->creation_date, fhp->modification_date,
             fhp->owner, fhp->num_records, fhp->mean, fhp->median,
             fhp->variance, fhp->std_dev);
    fclose (fp);
    free(fhp);
    return NO_ERROR;
}

/* Opens an existing file for use. */
int file_open(void)
{
    char file_name[MAX_FILE_NAME_LEN];
    printf ("Enter the Name of the File You Want to Open:");
    gets (file_name);
    FILE *fp;
    FileHeaderPtr fhp = malloc(sizeof(struct file_header));
    fp = fopen (file_name, "r");
    if (fp == NULL)
    {
        printf ("Error in opening file %s: Check to make sure file name is correct and file exists.", file_name);
    }
    get_file_header(fhp, fp);
    printf("File: %s\nCreated: %s\nModified: %s\nOwner: %s\nRecords: %d\nState: NEW\nMean: %f\nMedian: %f\nVariance: %f\nStd. Dev: %f\n",
           fhp->filename, fhp->creation_date, fhp->modification_date,
           fhp->owner, fhp->num_records, fhp->mean, fhp->median,
           fhp->variance, fhp->std_dev);
    fclose (fp);
    free(fhp);
    return NO_ERROR;
}

/* allows the user to change the name of an existing file to an alternate
 */
int file_rename(void)
{
    int success;
    FILE *fp;
    char new[MAX_FILE_NAME_LEN], old[MAX_FILE_NAME_LEN];
    printf("Enter the name of the file you want to rename: ");
    gets(old);
    fp=fopen(old, "r");
    if (fp == NULL)
    {
        printf("Error in opening file %s: Check to make sure filename is correct and file exists.", old);
        fclose(fp);
        return FILE_ERROR;
    }
    else
    {
        printf("\nEnter the new file name");
        gets(new);
        success = rename(old, new);
        if(success == 0)
        {
            printf("File successfully renamed");
        }
        else
        {
            printf("Error unable to rename file");
        }
        return NO_ERROR;
    }
}

/* makes a copy of an existing file. The new file must have a different legal filename
 */
int file_copy(void)
{
    char prev_file [MAX_FILE_NAME_LEN];
    char new_file [MAX_FILE_NAME_LEN];
    FILE *new_fp;
    FILE *prev_fp;
    printf ("Enter the Name of the File You Want to Copy:\n");
    gets (prev_file);
    prev_fp = fopen (prev_file, "r");
    if (prev_fp == NULL)
    {
        printf ("Error in opening file %s: Check to make sure file name is correct and file exists.", prev_file);
        return FILE_ERROR;
    }
    printf ("Enter the Copy File Name:");
    gets (new_file);
    new_fp = fopen (new_file, "a+");
    if (new_fp == NULL)
    {
        printf ("Error in opening file %s: Check to make sure file name is correct and file exists.", new_file);
        return FILE_ERROR;
    }
    char name_buffer [200];
    while (fgets (name_buffer,200,prev_fp) != NULL)
    {
        fputs(name_buffer, new_fp);
    }
    fclose (prev_fp);
    fclose (new_fp);
    return NO_ERROR;
}

/* copies a data file to a formatted version suitable for printing on a printer. This is a preliminary
 version. See to_string_file_header() below for an alternate method.
 */
int file_print(void)
{
    char file_name[MAX_FILE_NAME_LEN];
    char file_name_print[MAX_FILE_NAME_LEN] = "print_";
    printf ("Enter the Name of the File You Want to Print:");
    gets (file_name);
    strcat(file_name_print, file_name);
    //printf("this is the file_name_print %s\n", file_name_print);
    FILE *fp, *fp_print;
    FileHeaderPtr fhp = malloc(sizeof(struct file_header));
    fp = fopen (file_name, "r");
    if (fp == NULL)
    {
        printf ("Error in opening file %s: Check to make sure file name is correct and file exists.", file_name);
    }
    get_file_header(fhp, fp);
    fp_print = fopen (file_name_print, "a+");
    if (fp_print == NULL)
    {
        printf ("Error in opening file %s: Check to make sure file name is correct and file exists.", file_name_print);
    }
    fprintf(fp_print, "File: %s\nCreated: %s\nModified: %s\nOwner: %s\nRecords: %d\nState: NEW\nMean: %f\nMedian: %f\nVariance: %f\nStd. Dev: %f\n",
           fhp->filename, fhp->creation_date, fhp->modification_date,
           fhp->owner, fhp->num_records, fhp->mean, fhp->median,
           fhp->variance, fhp->std_dev);
    fclose (fp);
    fclose (fp_print);
    free(fhp);
    return NO_ERROR;
}

/* allows the user to delete an existing file; gives the user a second chance to abort, uses the remove() function from stdio.h
 */
int file_delete(void)
{
    int status;
    char file_name [MAX_FILE_NAME_LEN];
    char response;
    printf ("Enter Name of File You Want to Delete.");
    gets (file_name);
    printf ("Are you sure you want to delete %s? Y or N", file_name);
    scanf ("%c", &response);
    getchar();
    if (response == 'Y' || response == 'y')
    {
        status = remove (file_name);
        if (status==0)
        {
            printf ("%s was deleted successfully.\n", file_name);
            fflush(stdout);
            return NO_ERROR;
        }
        else
        {
            printf ("Error deleting file.\n");
            return FILE_ERROR;
        }
    }
    return NO_ERROR;
}

/***************************************************************************************************
 Utilities
 Helper functions that support the file management system (menu)
 ***************************************************************************************************/
/* fhp should have already been allocated so that it contains a valid heap pointer. filename space will need to be allocated here. Date spaces were allocated in the structure. Owner will need to be determined
 */
void init_file_header(FileHeaderPtr fhp, char * name)
{
    
    char date[26];
    char owner[MAX_OWNER_FIELD];
    
    fhp->filename = (char *) malloc(sizeof(char) * strlen(name) + 1);
    strcpy(fhp->filename, name);
    
    // this algorithm used to initialize a file header record
    //when a file is first created
    time_t timer;
    struct tm *timeinfo;
    time(&timer);
    timeinfo = localtime(&timer);
    strcpy(date, (char *) asctime(timeinfo));
    date[24] = 0;
    
    strcpy(fhp->creation_date, date);
    strcpy(fhp->modification_date, date);
    
    fhp->num_records = 0;
    fhp->state = NEW;
    fhp->mean = 0.0L;
    fhp->median = 0.0L;
    fhp->variance = 0.0L;
    fhp->std_dev = 0.0L;
    
    printf("Enter owner name: ");
    gets(owner);
    printf("\n");
    fhp->owner = (char *) malloc(sizeof(char) * strlen(owner) + 1);
    strcpy(fhp->owner, owner);
}

/* gets a file header record from the file f_p and parses it into the structure fh_p. When it returns fh_p will be pointing to a filled file header record.
 */
int get_file_header(FileHeaderPtr fh_p, FILE * f_p)
{
    if (!f_p)
        return FILE_ERROR;
    
    char header[1000];
    
    if (!fh_p)
        fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader));
    
    fgets(header, 999, f_p);	// reads the header record
    puts(header);
    parse_file_header(fh_p, header);
    return NO_ERROR;
}

/* this function parses a single string, header, containing a file header record and puts the values into
 the fields of the structure pointed to by fh_p. Both fh_p and header must be valid pointers.
 */
void parse_file_header(FileHeaderPtr fh_p, char * header)
{
    char buff[256];
    char * pos;
    int i, field;
    
    pos = strchr(header, ',');
    *pos++ = 0;
    strcpy(buff, header);	// copies filename into buff
    i = strlen(buff);
    
    fh_p->filename = (char *) malloc(sizeof(char) * i + 1); // allocate space for the name
    strcpy(fh_p->filename, buff);
    
    header = pos;		// resets head of header string
    for (field = 1; field < HEADER_FIELDS; field++)
    {
        switch (field)
        {
            case CREATION_DATE_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(fh_p->creation_date, header);
                header = pos;
                break;
            }
            case MODIFICATION_DATE_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(fh_p->modification_date, header);
                header = pos;
                break;
            }
            case OWNER_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(buff, header);	//
                i = strlen(buff);
                fh_p->owner = (char *) malloc(sizeof(char) * i + 1);
                strcpy(fh_p->owner, buff);
                header = pos;
                break;
            }
            case NUMBER_RECORDS_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(buff, header);
                fh_p->num_records = atoi(buff);
                header = pos;
                break;
            }
            case STATE_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(buff, header);
                if (strncmp(buff, "new", 3) == 0) { // a use of goto to emulate a switch statement with non-int
                    fh_p->state = NEW;
                }
                else if (strncmp(buff, "entry", 5) == 0)
                {
                    fh_p->state = ENTRIES;
                }
                else if (strncmp(buff, "sorted", 6) == 0)
                {
                    fh_p->state = SORTED;
                }
                header = pos;
                break;
            }
            case MEAN_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(buff, header);
                fh_p->mean = atof(buff);
                header = pos;
                break;
            }
            case MEDIAN_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(buff, header);
                fh_p->median = atof(buff);
                header = pos;
                break;
            }
            case VARIANCE_FIELD:
            {
                pos = strchr(header, ',');
                *pos++ = 0;
                strcpy(buff, header);
                fh_p->variance = atof(buff);
                header = pos;
                break;
            }
            case STD_DEV_FIELD:
            {
                strcpy(buff, header);
                fh_p->std_dev = atof(buff);
                puts(buff);
                break;
            }
        }	// end switch
    }	// end for loop
}

/* creates a string containing all of the fields from a file header structure pointed at by fh_p. The char string buff should have been pre-allocated from the calling function.
 */
char * to_string_file_header(FileHeaderPtr fh_p, char * buff)
{
    
    char loc_buff[11];
    
    if (fh_p->state == NEW)
        strcpy(loc_buff, "new");
    else if (fh_p->state == ENTRIES)
        strcpy(loc_buff, "entry");
    else if (fh_p->state == SORTED)
        strcpy(loc_buff, "sorted");
    
    sprintf(buff,
            "File: %s\nCreated: %s\nModified: %s\nOwner: %s\nRecords: %d\nState: %s\nMean: %f\nMedian: %f\nVariance: %f\nStd. Dev: %f\n",
            fh_p->filename, fh_p->creation_date, fh_p->modification_date,
            fh_p->owner, fh_p->num_records, loc_buff, fh_p->mean, fh_p->median,
            fh_p->variance, fh_p->std_dev);
    return buff;
}

/* checks the file name for erroneous characters - this is more restrictive than Unix file naming conventions, but the rules are application specific.
 */
int check_file_name(const char * filename)
{
    int i;
    int length = strlen(filename);
    
    for (i = 0; i < length; i++)
    {
        if (!(isalnum(filename[i]) || filename[i] == '_' || filename[i] == '.'))
            return FILE_NAME_FORMAT_ERROR;
    }
    return NO_ERROR;
}
