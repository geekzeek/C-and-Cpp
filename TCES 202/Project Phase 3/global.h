/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 global.h
 
 Header information goes here
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define NO_ERROR 0
#define FILE_ERROR 1
#define FILE_NAME_FORMAT_ERROR 2
#define NO_DATA_FOUND_ERROR 3

/* main menu selections
 */
#define FILE_SEL 1
#define EDIT_SEL 2
#define COMPUTE_SEL 3
#define REPORT_SEL 4
#define EXIT_SEL 5

/* File menu selections
 */
#define CREATE_SEL 1
#define OPEN_SEL 2
#define RENAME_SEL 3
#define COPY_SEL 4
#define PRINT_SEL 5
#define DELETE_SEL 6
#define EXIT_FILE_SEL 7

/* Edit menu selections
 */
#define EDIT_ADD_SEL 1
#define EDIT_EDIT_SEL 2
#define EDIT_DELETE_SEL 3
#define EXIT_EDIT 4

/* Compute menu selections
 */
#define COMP_STATS 1
#define COMP_MEAN 2
#define COMP_MEDIAN 3
#define COMP_VARIANCE 4
#define COMP_STD_DEV 5
#define EXIT_COMP 6

/* Report menu selections
 */
#define REPORT_DISPLAY 1
#define EXIT_REPORT 2

#define MAX_DATE_FIELD 25
#define MAX_NAME_FIELD 65
#define MAX_OWNER_FIELD 65
#define MAX_FILE_NAME_LEN 101

typedef enum{NEW, S_ENTRY, SORTED} State ;

#define HEADER_FIELDS 10

typedef struct file_header {
    char * filename;
    char creation_date[25];
    char modification_date[25];
    char * owner;
    long num_records;
    State state;
    double mean;
    double median;
    double variance;
    double std_dev;
} FileHeader;

typedef FileHeader *FileHeaderPtr;

typedef struct data_record {
    double data;
} DataRecord;

typedef DataRecord *DataRecordPtr;

#endif
