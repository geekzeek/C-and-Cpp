/*
 File Menu
 file.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


#include "global.h"
#include "file.h"
#include "screen_utils.h"

/* Called from the main menu, this menu gets the user's selections for
 * how to work with the files.
 */
int file_main_menu()
{
    int selection = 0;
    int error = NO_ERROR;
    
    while (selection != EXIT_FILE_SEL)
    {
        clear_screen();
        selection = file_menu();
        switch (selection)
        {
            case CREATE_SEL:
            {
                error = file_create();
                if (error)
                    printf("File error: Check name\n");
                else
                    printf("File created successfully\n");
                press_enter();
                break;
            }
            case OPEN_SEL:
            {
                error = file_open();
                if (error)
                    printf("File error: Check that file is created\n");
                else
                    printf("File opened successfully\n");
                press_enter();
                break;
            }
            case RENAME_SEL:
            {
                error = file_rename();
                if (error)
                    printf("File error: Check that file exists\n");
                else
                    printf("File successfully renamed\n");
                press_enter();
                break;
            }
            case COPY_SEL:
            {
                error = file_copy();
                if (error)
                    printf("File error: Check that file exists\n");
                else
                    printf("File successfully copied\n");
                press_enter();
                break;
            }
            case PRINT_SEL:
            {
                error = file_print();
                if (error)
                    printf("File error: Check that file exists\n");
                else
                    printf("File successfully printed\n");
                press_enter();
                break;
            }
            case DELETE_SEL:
            {
                error = file_delete();
                if (error)
                    printf("File error: Check that file exists\n");
                else
                    printf("File successfully deleted\n");
                press_enter();
                break;
            }
                
        }
    }
    clear_screen();
    return error;
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
        while (1)
        {
            clear_screen();
            printf("Incorrect selection. Please enter one of these choices.\n");
            print_file_menu();
            gets(sel_s);
            sel = atoi(sel_s);
            if (!(sel < CREATE_SEL || sel > EXIT_FILE_SEL))
                break;
        }
    }
    return sel;
}

/* prints the file menu options to the screen. Is called from multiple places.
 * File Menu: 1) New 2) Open 3) Rename 4) Copy 5) Print 6) Delete 7) Exit\n")
 */
int print_file_menu(void)
{
    printf("StatPac File menu options.\n");
    printf(
           "File Menu: 1) New 2) Open 3) Rename 4) Copy 5) Print 6) Delete 7) Exit\n");
    printf("Please choose an option: ");
    fflush(stdout);
    return 0;
}

/************************************************************************************************
 Menu-called Functions
 These are the functions that implement the menu options for the file management system
 
 ************************************************************************************************/

/* gets user input for new file name, checks to make sure no file of that type already
 exists, if it doesn't exist it creates the file and initializes the header lines (see below)
 Returns file handle in fid.
 */
int file_create()
{
    char filename[MAX_FILE_NAME_LEN];
    int error = NO_ERROR;
    FileHeaderPtr fhp = NULL;
    FILE * fid;
    
    printf("File Creation:\nPlease enter the file name you wish to create: ");
    fflush(stdout);
    gets(filename);
    
    // test for valid filename format
    error = check_file_name(filename);
    
    if (!error)
    {
        fid = fopen(filename, "w");
    } else
    {
        return FILE_NAME_FORMAT_ERROR;
    }
    
    if (fid)
    {
        puts(filename);
        // create a new file header record initializing the dates, name and 0 data records.
        fhp = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate some space in the heap
        init_file_header(fhp, filename);
        // write that record to the file
        fprintf(fid, "%s,%s,%s,%s,%ld,%s,%f,%f,%f,%f", fhp->filename,
                fhp->creation_date, fhp->modification_date, fhp->owner,
                fhp->num_records, "new", fhp->mean, fhp->median, fhp->variance,
                fhp->std_dev);
        
        // close the file
        fclose(fid);
        free(fhp);
        return NO_ERROR;
    }
    return FILE_ERROR;
}

/* Opens an existing file for use. Returns successfully opened file in fid */
int file_open()
{
    FILE * fid;
    FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader));
    fid = NULL;
    char filename[MAX_FILE_NAME_LEN];
    char buff[256];
    int error;
    
    printf("Enter name of file you want to open: ");
    fflush(stdout);
    gets(filename);
    printf("\n");
    error = check_file_name(filename);
    if (error)
        return FILE_NAME_FORMAT_ERROR;
    fid = fopen(filename, "r+"); // opens an existing file for updating
    if (!fid) // error in opening file
    {
        printf(
               "Error in opening file %s: Check to make sure filename is correct and file exists.\n",
               filename);
        return FILE_ERROR; // a return here means we don't need an else clause
    }
    get_file_header(fh_p, fid);
    printf("%s", to_string_file_header(fh_p, buff));
    free(fh_p);
    fclose(fid);
    press_enter();
    clear_screen();
    return NO_ERROR;
}

/* allows the user to change the name of an existing file to an alternate
 */
int file_rename(void)
{
    int err = 0;
    FILE * fid = NULL;
    char filename[MAX_FILE_NAME_LEN], newname[MAX_FILE_NAME_LEN];
    
    printf("Enter name of file you want to rename: ");
    gets(filename);
    printf("\n");
    err = check_file_name(filename);	// checks the validity of the name
    if (err == FILE_NAME_FORMAT_ERROR)
    {
        printf("Incorrect file name format\n");
        return err;
    }
    
    fid = fopen(filename, "r");
    if (!fid) // error in opening file
    {
        printf(
               "Error in opening file %s: Check to make sure filename is correct and file exists.\n",
               filename);
        return FILE_ERROR; // a return here means we don't need an else clause
    }
    fclose(fid);
    
    printf("Enter the new file name: ");
    gets(newname);
    printf("\n");
    err = check_file_name(newname);	// checks the validity of the name
    if (err == FILE_NAME_FORMAT_ERROR)
    {
        printf("Incorrect file name format\n");
        return err;
    }
    rename(filename, newname);
    return NO_ERROR;
}

/* makes a copy of an existing file. The new file must have a different legal filename
 */
int file_copy(void)
{
    int err = 0;
    FILE * src_file;
    FILE * dest_file;
    char buff[256];
    
    char filename[MAX_FILE_NAME_LEN], copyname[MAX_FILE_NAME_LEN];
    
    printf("Enter name of file you want to copy: ");
    gets(filename);
    printf("\n");
    err = check_file_name(filename);	// checks the validity of the name
    if (err == FILE_NAME_FORMAT_ERROR)
    {
        printf("Incorrect file name format\n");
        return err;
    }
    printf("Enter the copy file name: ");
    gets(copyname);
    printf("\n");
    err = check_file_name(copyname);	// checks the validity of the name
    if (err == FILE_NAME_FORMAT_ERROR)
    {
        printf("Incorrect file name format\n");
        return err;
    }
    src_file = fopen(filename, "r");
    if (!src_file) // error in opening file
    {
        printf(
               "Error in opening file %s: Check to make sure filename is correct and file exists.\n",
               filename);
        return FILE_ERROR; // a return here means we don't need an else clause
    }
    
    dest_file = fopen(copyname, "w");
    while (!feof(src_file))
    {
        buff[0] = 0;			// make sure buff is initialized to empty
        fgets(buff, 255, src_file);
        fprintf(dest_file, "%s\n", buff);
        printf("%s\n", buff);
    }
    fclose(src_file);
    fclose(dest_file);
    return NO_ERROR;
    
}

/* copies a data file to a formatted version suitable for printing on a printer.
 */
int file_print(void)
{
    int err = 0;
    FILE * src_file;
    FILE * dest_file;
    int c, item = 0;
    
    char filename[MAX_FILE_NAME_LEN], printname[MAX_FILE_NAME_LEN];
    
    printf("Enter name of file you want to print: ");
    gets(filename);
    printf("\n");
    err = check_file_name(filename);	// checks the validity of the name
    if (err == FILE_NAME_FORMAT_ERROR)
    {
        printf("Incorrect file name format\n");
        return err;
    }
    printf("Enter the copy file name: ");
    gets(printname);
    printf("\n");
    err = check_file_name(printname);	// checks the validity of the name
    if (err == FILE_NAME_FORMAT_ERROR)
    {
        printf("Incorrect file name format\n");
        return err;
    }
    src_file = fopen(filename, "r");
    if (!src_file) // error in opening file
    {
        printf(
               "Error in opening file %s: Check to make sure filename is correct and file exists.\n",
               filename);
        return FILE_ERROR; // a return here means we don't need an else clause
    }
    
    dest_file = fopen(printname, "w");
    item = 1;
    fprintf(dest_file, "Filename: ");
    while (!feof(src_file))
    {
        c = fgetc(src_file);
        if (c == ',') // This is one way to handle printing the contents of a structure. See file.h for macro definitions
        {
            switch (item)
            {
                case CREATION_DATE_FIELD:
                {
                    fprintf(dest_file, "\nCreation date: ");
                    break;
                }
                case MODIFICATION_DATE_FIELD:
                {
                    fprintf(dest_file, "\nModification date: ");
                    break;
                }
                case OWNER_FIELD:
                {
                    fprintf(dest_file, "\nOwner: ");
                    break;
                }
                case NUMBER_RECORDS_FIELD:
                {
                    fprintf(dest_file, "\nNumber of Records: ");
                    break;
                }
                case STATE_FIELD:
                {
                    fprintf(dest_file, "\nState: ");
                    break;
                }
                case MEAN_FIELD:
                {
                    fprintf(dest_file, "\nMean: ");
                    break;
                }
                case MEDIAN_FIELD:
                {
                    fprintf(dest_file, "\nMedian: ");
                    break;
                }
                case VARIANCE_FIELD:
                {
                    fprintf(dest_file, "\nVariance: ");
                    break;
                }
                case STD_DEV_FIELD:
                {
                    fprintf(dest_file, "\nStandard deviation: ");
                    break;
                }
            }
            item++;
            c = '\t';
        }
        if (feof(src_file))
            break;
        fputc(c, dest_file);
    }
    fprintf(dest_file, "\n");
    fclose(src_file);
    fclose(dest_file);
    return NO_ERROR;
    
}

/* allows the user to delete an existing file; gives the user a second chance to abort
 uses the remove() function from stdio.h
 */
int file_delete(void)
{
    int err = 0;
    char filename[MAX_FILE_NAME_LEN];
    
    printf("Enter name of file you want to delete: ");
    gets(filename);
    printf("\n");
    err = check_file_name(filename);	// checks the validity of the name
    if (err == FILE_NAME_FORMAT_ERROR)
    {
        printf("Incorrect file name format\n");
        return err;
    }
    return remove(filename);
}

/***************************************************************************************************
 Utilities
 Helper functions that support the file management system (menu)
 ***************************************************************************************************/
/* fhp should have already been allocated so that it contains a valid heap pointer. filename space will
 need to be allocated here. Date spaces were allocated in the structure. Owner will need to be determined
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

/* gets a file header record from the file f_p and parses it into the structure fh_p. When it
 returns fh_p will be pointing to a filled file header record.
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
    size_t i, field;
    
    pos = strchr(header, ',');
    *pos++ = 0;
    strcpy(buff, header);	// copies filename into buff
    i = strlen(buff);
    
    fh_p->filename = (char *) malloc(sizeof(char) * i + 1); // allocate space for the name
    strcpy(fh_p->filename, buff);
    
    header = pos;		// resets head of header string
    for (field = 1; field < HEADER_FIELDS; field++) {
        switch (field) {
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
                if (strncmp(buff, "new", 3) == 0) // a use of goto to emulate a switch statement with non-int
                {
                    fh_p->state = NEW;
                    goto getout;
                    // more efficient than nested if-else if statements
                }
                if (strncmp(buff, "entry", 5) == 0)
                {
                    fh_p->state = S_ENTRY;
                    goto getout;
                }
                if (strncmp(buff, "sorted", 6) == 0)
                {
                    fh_p->state = SORTED;
                    goto getout;
                }
            getout: header = pos;
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

/* creates a string containing all of the fields from a file header structure pointed at by fh_p. The
 char string buff should have been pre-allocated from the calling function.
 */
char *to_string_file_header(FileHeaderPtr fh_p, char * buff)
{
    
    char loc_buff[11];
    
    if (fh_p->state == NEW)
        strcpy(loc_buff, "new");
    else if (fh_p->state == S_ENTRY)
        strcpy(loc_buff, "entry");
    else if (fh_p->state == SORTED)
        strcpy(loc_buff, "sorted");
    
    sprintf(buff,
            "File: %s\nCreated: %s\nModified: %s\nOwner: %s\nRecords: %ld\nState: %s\nMean: %f\nMedian: %f\nVariance: %f\nStd. Dev: %f\n",
            fh_p->filename, fh_p->creation_date, fh_p->modification_date,
            fh_p->owner, fh_p->num_records, loc_buff, fh_p->mean, fh_p->median,
            fh_p->variance, fh_p->std_dev);
    return buff;
}

/* checks the file name for erroneous characters - this is more restrictive than Unix file naming
 conventions, but the rules are application specific.
 */
int check_file_name(const char * filename)
{
    int i;
    size_t length = strlen(filename);
    
    for (i = 0; i < length; i++)
    {
        if (!(isalnum(filename[i]) || filename[i] == '_' || filename[i] == '.'))
            return FILE_NAME_FORMAT_ERROR;
    }
    return NO_ERROR;
}

