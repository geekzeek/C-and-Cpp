//
//  compute.h
//  Statistical Package Project Phase 3
//
//  Created by Education on 3/4/15.
//  Copyright (c) 2015 Hess, Brian G. All rights reserved.
//

#ifndef __Statistical_Package_Project_Phase_3__compute__
#define __Statistical_Package_Project_Phase_3__compute__

#include "edit.h"
#include "file.h"
#include "global.h"
#include "screen_utils.h"

// prototypes
int compute_main_menu (void);
int compute_menu (void);
void print_compute_menu (void);

int open_file_retrieve_data (char *, FileHeaderPtr, double *);
int open_file_update_data (char *, FileHeaderPtr, double *);

void compute_update ();
void compute_mean ();
void compute_median ();
void compute_variance ();
void compute_st_dev ();

#endif /* defined(__Statistical_Package_Project_Phase_3__compute__) */
