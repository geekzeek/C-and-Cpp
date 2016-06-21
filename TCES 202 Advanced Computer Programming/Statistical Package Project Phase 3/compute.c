//
//  compute.c
//  Statistical Package Project Phase 3
//
//  Created by Education on 3/4/15.
//  Copyright (c) 2015 Hess, Brian G. All rights reserved.
//

#include "compute.h"

void mean (char *, FileHeaderPtr, double *);
void median (char *, FileHeaderPtr, double *);
void var (char *, FileHeaderPtr, double *);
void st_dev (char *, FileHeaderPtr, double *);
void quick_sort(double *, double, long);

int compute_main_menu (void)
{
    int selection = 0;
    
    while (selection != EXIT_COMP)
    {
        clear_screen();
        selection = compute_menu();
        switch (selection)
        {
            case COMP_STATS:
            {
                compute_update();
                press_enter();
                break;
            }
            case COMP_MEAN:
            {
                compute_mean();
                press_enter();
                break;
            }
            case COMP_MEDIAN:
            {
                compute_median();
                press_enter();
                break;
            }
            case COMP_VARIANCE:
            {
                compute_variance();
                press_enter();
                break;
            }
            case COMP_STD_DEV:
            {
                compute_st_dev();
                press_enter();
                break;
            }
        }
    }
    clear_screen();
    return NO_ERROR;
}

int compute_menu (void)
{
    char sel_s[3];
    int sel;
    
    print_compute_menu();
    gets(sel_s);
    sel = atoi(sel_s);
    if ((sel < COMP_STATS || sel > COMP_STD_DEV) && sel != EXIT_COMP)
    {
        while (1)
        {
            clear_screen();
            printf("Incorrect selection. Please enter one of these choices.\n");
            print_compute_menu();
            gets(sel_s);
            sel = atoi(sel_s);
            if (!((sel < COMP_STATS || sel > COMP_STD_DEV)
                  && sel != EXIT_COMP))
                break;
        }
    }
    return sel;
}

void print_compute_menu (void)
{
    printf("StatPac Compute menu options.\n");
    printf("Compute Menu: 1) Update All 2) Compute Mean 3) Compute Median 4) Compute Variance 5) Compute Standard Deviaton 6) Exit\n");
    printf("Please choose an option: ");
}

/* This function will be utilized by each computing function to open the file, get the file header info and also get the data placed into an array. */

int open_file_retrieve_data(char *filename, FileHeaderPtr fh_p, double *array)
{
    char buffer[256];
    int i=0;
    double number;
    
    //Open the file, read its contents, and store the values in array. Store the header in fh_p
    
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return FILE_ERROR;        // return error if opening file fails
    }
    //fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header
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
        if(buffer[strlen(buffer)-2] == '\n')//remove newline character
        {
            buffer[strlen(buffer)-1] = NULL;
        }
        number = atof(buffer);// convert buffer string to float
        array[i] = number; // assign number to array
        printf("%d: %.6f\n", (i+1), array[i]);
        i++;
    }
    fclose(fp);
    return NO_ERROR;
}

/* This function will be utilized by each computing function to open the file and place the updated info in the header */
int open_file_update_data (char *filename, FileHeaderPtr fh_p, double *array)
{
    FILE * fp;
    int i;
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

/* This will update the file by calling the mean, median, variance, and st_dev subfunctions and updating the newly computed info in the file. */
void compute_update ()
{
    char filename[MAX_FILE_NAME_LEN];
    printf("\nEnter filename for computing statistics: ");
    gets(filename);
    FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header;
    double array[256]={0};
    open_file_retrieve_data(filename, fh_p, array);
    mean(filename, fh_p, array);
    median(filename, fh_p, array);
    var(filename, fh_p, array);
    st_dev(filename, fh_p, array);
    open_file_update_data (filename, fh_p, array);
}

/* This will call up the mean subfunction to compute the mean of the data in the file. */
void compute_mean ()
{
    char filename[MAX_FILE_NAME_LEN];
    printf("\nEnter filename for computing statistics: ");
    gets(filename);
    FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header;
    double array[256]={0};
    open_file_retrieve_data(filename, fh_p, array);
    mean(filename, fh_p, array);
    open_file_update_data (filename, fh_p, array);
}

/* This will call up the median subfunction to compute the median of the data in the file. */
void compute_median ()
{
    char filename[MAX_FILE_NAME_LEN];
    printf("\nEnter filename for computing statistics: ");
    gets(filename);
    FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header;
    double array[256]={0};
    open_file_retrieve_data(filename, fh_p, array);
    median(filename, fh_p, array);
    open_file_update_data (filename, fh_p, array);
}

/* This will call up the variance subfunction to compute the variance of the data in the file. */
void compute_variance ()
{
    char filename[MAX_FILE_NAME_LEN];
    printf("\nEnter filename for computing statistics: ");
    gets(filename);
    FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header;
    double array[256]={0};
    open_file_retrieve_data(filename, fh_p, array);
    var(filename, fh_p, array);
    open_file_update_data (filename, fh_p, array);
}

/* This will call up the st_dev subfunction to compute the standard deviation of the data in the file. */
void compute_st_dev ()
{
    char filename[MAX_FILE_NAME_LEN];
    printf("\nEnter filename for computing statistics: ");
    gets(filename);
    FileHeaderPtr fh_p = (FileHeaderPtr) malloc(sizeof(FileHeader)); // allocate memory for file header;
    double array[256]={0};
    open_file_retrieve_data(filename, fh_p, array);
    st_dev(filename, fh_p, array);
    open_file_update_data (filename, fh_p, array);
}

/* This subfunction will compute the mean of the data. */
void mean (char *filename, FileHeaderPtr fh_p, double *m_array)
{
    double sum=0;
    int i;
    for (i=0; i<fh_p->num_records; i++)
    {
        sum += m_array[i];
    }
    fh_p->mean = sum/fh_p->num_records;
}

/* This subfunction will compute the median of the data. */
void median (char *filename, FileHeaderPtr fh_p, double *med_array)
{
    double median=0;
    int i;
    double med_sort_array[fh_p->num_records];
    for (i=0; i<fh_p->num_records; i++)
    {
        med_sort_array [i] = med_array[i];
    }
    quick_sort(med_sort_array, 0, fh_p->num_records-1); //Sorts the array
    
    //Computes the median
    if (fh_p->num_records % 2 != 0)
    {
        median = med_sort_array[(fh_p->num_records/2)];
    }
    else
    {
        median = (med_sort_array[(fh_p->num_records/2)-1] + med_sort_array[(fh_p->num_records/2)])/2;
    }
    fh_p->median = median;
}

/* This subfunction will compute the variance of the data. */
void var (char *filename, FileHeaderPtr fh_p, double *v_array)
{
    double variance=0;
    int i;
    if (fh_p->mean <= 0) //verifies that the mean has been computed and filled in
    {
        mean (filename, fh_p, v_array);
    }
    
    //Compute Standard Deviation
    for (i=0; i<fh_p->num_records; i++)
    {
        variance += pow ((fh_p->mean-v_array[i]), 2);
    }
    variance = variance/fh_p->num_records;
    fh_p->variance = variance;
}

/* This subfunction will compute the standard deviation of the data. */
void st_dev (char *filename, FileHeaderPtr fh_p, double *std_array)
{
    if (fh_p->variance <= 0) //varifies that the variance has been computed and filled in
    {
        var (filename, fh_p, std_array);
    }
    fh_p->std_dev = pow(fh_p->variance, 0.5);
}

/* This will sort the array.  This function provided by instructor*/
void quick_sort(double s_array[], double first, long last)
{
    int pivot,temp,i;
    long j;
    
    // Set the pivot point
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        
        // Find the first element that is less than
        // everything on the left and greater than
        // everything on the right
        while(i<j)
        {
            while(s_array[i]<=s_array[pivot]&&i<last)
                i++;
            while(s_array[j]>s_array[pivot])
                j--;
            if(i<j)
            {
                temp=s_array[i];
                s_array[i]=s_array[j];
                s_array[j]=temp;
            }
        }
        temp=s_array[pivot];
        s_array[pivot]=s_array[j];
        s_array[j]=temp;
        quick_sort(s_array,first,j-1);
        quick_sort(s_array,j+1,last);
    }
}
