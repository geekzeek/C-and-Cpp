//
//  main.c
//  Assassin
//
//  Created by Menaka Abraham on 12/11/14.
//  Copyright (c) 2014 Menaka. All rights reserved.
// 	DO NOT MODIFY THIS FILE.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "assassin_list.h"
#define FAILURE -1
#define SUCCESS 0
#define NAME_LEN 50

int read_names(char[][NAME_LEN], char *);
void shuffle_names(char[][NAME_LEN], int);
void print_names(char names[][NAME_LEN], int size);
void one_game(alist);

int main(int argc, const char * argv[]) {
	char names[NAME_LEN][NAME_LEN];
	int i;

	//Read the names from the file into the array and shuffle.
	int length = read_names(names, "names.txt");
	if (length != FAILURE) {
		shuffle_names(names, length);
		//For debugging
		//print_names(names, length);

	}
	alist list = (alist) malloc(sizeof(alist));
	list->kill_ring = NULL;
	list->grave_yard = NULL;

	if (list == NULL) {
		puts("Unable to allocate.");
		return FAILURE;
	}
	for (i = 0; i < length; i++) {
		list_add(list, names[i]);
	}

	while (!game_over(list)) {
		one_game(list);
	}

	printf("\nGame was won by %s\n ", winner(list));

	deallocate(list);

	//to make the screen wait on the exe.
	getchar();
	return 0;
}

/**
 * Play one game to get the name from the console and to
 * kill the person in the kill ring and move them into the graveyard.
 */
void one_game(alist list) {
	char victim[NAME_LEN];
	print_kill_ring(list);
	print_grave_yard(list);
	printf("\nnext victim? ");
	gets(victim);
	if (grave_yard_contains(list, victim)) {
		printf("%s is already dead.\n", victim);
	} else if (!kill_ring_contains(list, victim)) {
		puts("Unknown person");
	} else {
		kill_victim(list, victim);
	}
}


/**
 * Prints the names in the array.
 */
void print_names(char names[][NAME_LEN], int size) {
	int i;
	for (i = 0; i < size; i++)
		printf("%s\n", names[i]);
}
/***
 Reads the names from the text file into the array.
 Returns FAILURE if unable to open file, number of names
 if it reads the contents into the array.
 */
int read_names(char names[][NAME_LEN], char *file_name) {
	FILE *fid = fopen(file_name, "r");
	if (fid == NULL) {
		puts("Unable to read file");
		return FAILURE;
	}
	int i = 0;
	char buffer[NAME_LEN];
	while (fgets(buffer, NAME_LEN, fid) != NULL) {
		strcpy(names[i], buffer);
		//Remove carriage return and newline characters from the strings.
		char *ch = strrchr(names[i], '\r');
		if (ch)
			*ch = '\0';
		ch = strrchr(names[i], '\n');
		if (ch)
			*ch = '\0';
		i++;
	}
	fclose(fid);
	return i;
}

/**
 Shuffles the names randomly.
 */
void shuffle_names(char names[][NAME_LEN], int size) {
	srand(time(NULL));
	int iter = 0, i, j;
	char temp[NAME_LEN];
	do {
		i = rand() % size;
		j = rand() % size;
		if (i != j) {
			strcpy(temp, names[i]);
			strcpy(names[i], names[j]);
			strcpy(names[j], temp);
		}

		iter++;
	} while (iter < 100);
}

