//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
#include "global.h"
#include "edit.h"



/* edit the contents of an open file */
int edit_main_menu(void)
{
    int selection = 0;
    
    while (selection != EXIT_EDIT)
    {
        clear_screen();
        selection = edit_menu();
        switch (selection)
        {
            case EDIT_ADD_SEL:
            {
                edit_add();
                press_enter();
                break;
            }
            case EDIT_EDIT_SEL:
            {
                edit_edit();
                press_enter();
                break;
            }
            case EDIT_DELETE_SEL:
            {
                edit_delete();
                press_enter();
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
    if ((sel < EDIT_ADD_SEL || sel > EDIT_DELETE_SEL) && sel != EXIT_EDIT)
    {
        while (1)
        {
            clear_screen();
            printf("Incorrect selection. Please enter one of these choices.\n");
            print_edit_menu();
            gets(sel_s);
            sel = atoi(sel_s);
            if (!((sel < EDIT_ADD_SEL || sel > EDIT_DELETE_SEL)
                  && sel != EXIT_EDIT))
                break;
        }
    }
    return sel;
}

// Prints the different edit menu choices.
void print_edit_menu(void)
{
    printf("StatPac Edit menu options.\n");
    printf(
           "Edit Menu: 1) Add new data 2) Edit existing data 3) Delete data 4) Exit\n");
    printf("Please choose an option: ");
}

/**
 Called by the three edit functions to see if the file exists.
 */
int open_file_for_edit(char *filename, FileHeaderPtr fh_p)
{
    FILE *fid = NULL;
    char headerStr[1000];
    int error = check_file_name(filename);
    if (!error)
    {
        fid = fopen(filename, "r");
        if (!fid) // error in opening file
        {
            printf(
                   "Error in opening file %s: Check to make sure filename is correct and file exists.\n",
                   filename);
            return FILE_ERROR; // a return here means we don't need an else clause
        }
        get_file_header(fh_p, fid);
        printf("%s\n", to_string_file_header(fh_p, headerStr));
        fclose(fid);
    }
    return NO_ERROR;
}
/**********************************************************************************************/
/* allows users to add any number of new data items to the file.
 */
int edit_add(void)
{
    int entries = 0;
    int error = 0;
    int i;
    char buff[31];	// longer than double
    char filename[91];
    char headerStr[1000];
    char state[12];
    FILE * fid;
    FILE * fid_temp;
    DataRecord dr;
    char * pos;
    clear_screen();
    printf("Enter the file name for adding data: ");
    gets(filename);
    printf("\n");
    FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader));
    error = open_file_for_edit(filename, fh_p);
    
    // Append data records if file exists.
    if (error == NO_ERROR)
    {
        fid = fopen(filename, "a");
        if (!fid)
        {
            printf("File error for append\n");
            return FILE_ERROR;
        }
        printf("File: %s open for adding data\nPress enter to start adding data. \n", filename);
        press_enter();
        fprintf(fid, "\n");
        while (TRUE)
        {
            printf("Enter data ('q' to quit): ");
            gets(buff);
            if (buff[0] == 'q' || buff[0] == 'Q')
                break;
            pos = strchr(buff, '\n');
            if (pos)
                *pos = 0;
            dr.data = atof(buff);
            fprintf(fid, "%f\n", dr.data);
            entries++;
        }
        fclose(fid);
        if (fh_p->num_records < fh_p->num_records + entries)
            strcpy(state, "entry");
        else
            strcpy(state, "new");
        fh_p->num_records += entries;
        fid = fopen(filename, "r");
        fid_temp = fopen("temp.dat", "w");
        fgets(headerStr, 999, fid);	// read in the header to throw away
        fprintf(fid_temp, "%s,%s,%s,%s,%ld,%s,%f,%f,%f,%f\n", fh_p->filename,
                fh_p->creation_date, fh_p->modification_date, fh_p->owner,
                fh_p->num_records, state, fh_p->mean, fh_p->median,
                fh_p->variance, fh_p->std_dev);
        for (i = 1; i < fh_p->num_records; i++) // get all but last record
        {
            headerStr[0] = 0;
            fgets(headerStr, 999, fid);		// use for data records
            fprintf(fid_temp, "%s", headerStr);
        }
        headerStr[0] = 0;
        fgets(headerStr, 999, fid);		// get last record
        pos = strchr(headerStr, '\n');
        if (pos)
            *pos = 0;
        fprintf(fid_temp, "%s", headerStr);
        fclose(fid);
        fclose(fid_temp);
        remove(filename);
        rename("temp.dat", filename);
        printf("Adding data complete. Closing %s\n", filename);
        free(fh_p);
    }
    return NO_ERROR;
}

/** Edit data
 */

int edit_edit()
{
    int error = 0;
    int i;
    char filename[91];
    char headerStr[1000];
    FILE * fid;
    FILE * fid_temp;
    char * pos;
    char state[12];
    clear_screen();
    printf("Enter the file name for editing data: ");
    gets(filename);
    printf("\n");
    error = check_file_name(filename);
    if (!error)
    {
        fid = fopen(filename, "r");
        if (!fid) // error in opening file
        {
            printf(
                   "Error in opening file %s: Check to make sure filename is correct and file exists.\n",
                   filename);
            return FILE_ERROR; // a return here means we don't need an else clause
        }
        FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader));
        get_file_header(fh_p, fid);
        printf("%s\n", to_string_file_header(fh_p, headerStr));
        strcpy(state, "entry");
        fid_temp = fopen("temp.dat", "w");
        fprintf(fid_temp, "%s,%s,%s,%s,%ld,%s,%f,%f,%f,%f\n", fh_p->filename,
                fh_p->creation_date, fh_p->modification_date, fh_p->owner,
                fh_p->num_records, state, fh_p->mean, fh_p->median,
                fh_p->variance, fh_p->std_dev);
        
        if (fh_p->num_records > 0)
        {
            double data[fh_p->num_records];
            for (i = 1; i <= fh_p->num_records; i++) // get all but last record
            {
                headerStr[0] = 0;
                fgets(headerStr, 99, fid);		// use for data records
                pos = strchr(headerStr, '\n');
                if (pos)
                    *pos = 0;
                data[i-1] = atof(headerStr);
                printf("%d: %f\n", i, data[i - 1]);
            }
            int record_number;
            do
            {
                printf(
                       "\nWhich record would you like to edit? Enter the record number or 0 to quit : %d - %ld: ",
                       1, fh_p->num_records);
                scanf("%d", &record_number);
                if (record_number == 0)
                    break;
                while (record_number < 1 || record_number > fh_p->num_records)
                {
                    printf("\nPlease enter a number in the range :  %u - %lu: ",
                           1, fh_p->num_records);
                    scanf("%d", &record_number);
                    if (record_number == 0)
                        break;
                }
                if (record_number == 0) break;
                printf("\nEnter new value for record %u, data %f : ",
                       record_number, data[record_number - 1]);
                scanf("%lf", &data[record_number - 1]);
            } while (1);
            for (i = 1; i <= fh_p->num_records; i++)
            {
                if (i == fh_p->num_records)
                    fprintf(fid_temp, "%f", data[i-1]);
                else fprintf(fid_temp, "%f\n", data[i-1]);
                printf("%d: %f\n", i, data[i - 1]);
            }
        }
        fclose(fid);
        fclose(fid_temp);
        remove(filename);
        rename("temp.dat", filename);
        printf("Editing data complete. Closing %s\n", filename);
        free(fh_p);
    }
    return NO_ERROR;
}

/**
 Delete entries from file
 */
int edit_delete()
{
    
    int error = 0;
    int i;
    char filename[91];
    char headerStr[1000];
    FILE * fid;
    FILE * fid_temp;
    char * pos;
    char state[12];
    int entries = 0;
    clear_screen();
    
    printf("Enter the file name for editing data: ");
    gets(filename);
    printf("\n");
    error = check_file_name(filename);
    if (!error)
    {
        fid = fopen(filename, "r");
        if (!fid) // error in opening file
        {
            printf(
                   "Error in opening file %s: Check to make sure filename is correct and file exists.\n",
                   filename);
            return FILE_ERROR; // a return here means we don't need an else clause
        }
        FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader));
        get_file_header(fh_p, fid);
        printf("%s\n", to_string_file_header(fh_p, headerStr));
        
        
        strcpy(state, "entry");
        fid_temp = fopen("temp.dat", "w");
        
        
        if (fh_p->num_records > 0)
        {
            double data[fh_p->num_records];
            for (i = 1; i <= fh_p->num_records; i++) // get all but last record
            {
                headerStr[0] = 0;
                fgets(headerStr, 99, fid);		// use for data records
                pos = strchr(headerStr, '\n');
                if (pos)
                    *pos = 0;
                data[i-1] = atof(headerStr);
                printf("%d: %f\n", i, data[i - 1]);
            }
            
            int record_number;
            do
            {
                printf(
                       "\nWhich record would you like to delete? Enter the record number or 0 to quit : %d - %ld: ",
                       1, fh_p->num_records);
                scanf("%d", &record_number);
                if (record_number == 0)
                    break;
                while (record_number < 1 || record_number > fh_p->num_records)
                {
                    printf("\nPlease enter a number in the range :  %u - %lu: ",
                           1, fh_p->num_records);
                    scanf("%d", &record_number);
                    if (record_number == 0)
                        break;
                }
                if (record_number == 0) break;
                data[record_number - 1] = -9999;
                entries++;
                
            } while (1);
            
            fprintf(fid_temp, "%s,%s,%s,%s,%ld,%s,%f,%f,%f,%f\n", fh_p->filename,
                    fh_p->creation_date, fh_p->modification_date, fh_p->owner,
                    (fh_p->num_records - entries), state, fh_p->mean, fh_p->median,
                    fh_p->variance, fh_p->std_dev);
            
            for (i = 1; i <= fh_p->num_records; i++)
            {
                if (data[i-1] != -9999)
                {
                    if (i == fh_p->num_records)
                    {
                        fprintf(fid_temp, "%f", data[i-1]);
                    }
                    else
                    {
                        fprintf(fid_temp, "%f\n", data[i-1]);
                    }
                }
            }
        }
        
        fclose(fid);
        fclose(fid_temp);
        remove(filename);
        rename("temp.dat", filename);
        
        
        printf("Deleting data complete. Closing %s\n", filename);
        free(fh_p);
    }
    
    return NO_ERROR;
}

