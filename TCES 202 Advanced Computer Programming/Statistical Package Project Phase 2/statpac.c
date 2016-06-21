/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
statpac.c

header information goes here
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "statpac.h"

int main(int argc, char * argv[]) {

	int selection=0;
	int error_code = NO_ERROR;

	while (selection != EXIT_SEL) {
		selection = main_menu();
		switch (selection) {
			case FILE_SEL: {
				file_main_menu();
				selection = 0;
				break;
			}
			case EDIT_SEL:
				edit_main_menu();
				break;
			/*
			case SEARCH_SEL: search_menu();
			case COMPUTE_SEL: compute_menu();
			case REPORT_SEL: report_menu();
			*/
		}
	}
	clear_screen();
	printf("Thank you for using StatPac. Goodbye.\n");
	fflush(stdout);

	return error_code;
}

int main_menu(void) {
	int sel;
	char sel_s[3];

	print_main_menu();
	gets(sel_s);
	sel = atoi(sel_s);
	if (sel < FILE_SEL || sel > EXIT_SEL) {
		while (1) {
			clear_screen();
			printf("Incorrect selection. Please enter one of these choices: ");
			print_main_menu();
			gets(sel_s);
			sel = atoi(sel_s);
			if (!(sel < FILE_SEL || sel > EXIT_SEL)) break;
		}
	}
	return sel;
}

void print_main_menu (void) {
	printf("StatPac main menu options.\n");
	printf("Main Menu: 1) File, 2) Edit, 3) Search, 4) Compute, 5) Report, 6) Exit\n");
	printf("Please choose an option: ");
	fflush(stdout);
}



