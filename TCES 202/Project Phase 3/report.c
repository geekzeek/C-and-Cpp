//
//  report.c
//  Statistical Package Project Phase 3
//
//  Created by Education on 3/4/15.
//  Copyright (c) 2015 Hess, Brian G. All rights reserved.
//

#include "report.h"

int report_main_menu(void)
{
    int selection = 0;
    
    while (selection != EXIT_REPORT)
    {
        clear_screen();
        selection = report_menu();
        switch (selection)
        {
            case REPORT_DISPLAY:
            {
                report_display();
                press_enter();
                break;
            }
        }
    }
    clear_screen();
    return NO_ERROR;
}

// Validation for the Report menu selection
int report_menu(void)
{
    char sel_s[3];
    int sel;
    
    print_report_menu();
    gets(sel_s);
    sel = atoi(sel_s);
    if ((sel != REPORT_DISPLAY) && sel != EXIT_REPORT)
    {
        while (1)
        {
            clear_screen();
            printf("Incorrect selection. Please enter one of these choices.\n");
            print_report_menu();
            gets(sel_s);
            sel = atoi(sel_s);
            if (!((sel != REPORT_DISPLAY)
                  && sel != EXIT_REPORT))
                break;
        }
    }
    return sel;
}

// Prints the different Report menu choices.
void print_report_menu(void)
{
    printf("StatPac Report menu options.\n");
    printf(
           "Report Menu: 1) Report Statistics 2) Exit\n");
    printf("Please choose an option: ");
}

int report_display(void)
{
    char filename[MAX_FILE_NAME_LEN], buffer[256];
    int i;
    float number;
    float *array = NULL;
    FileHeaderPtr fh_p = NULL;
    
    /** Open the file, read its contents, and store the values in array. Store the header in fh_p **/
    
    i = 0;
    printf("\nEnter the file name for reporting statistics: ");
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
    
    /* Reports statistics */
    
    printf("\nReporting statistics for %s\n", filename);
    printf("Mean: %f\n", fh_p->mean);
    printf("Median: %f\n", fh_p->median);
    printf("Variance: %f\n", fh_p->variance);
    printf("Standard Deviation: %f\n", fh_p->std_dev);
    printf("Reporting statistics complete.\n");
    
    fh_p = NULL;
    free(fh_p);
    array = NULL;
    free(array);
    
    press_enter();
    return NO_ERROR;
}
