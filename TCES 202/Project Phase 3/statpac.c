/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
statpac.c

header information goes here
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//#include "global.h"
#include "statpac.h"

/**
 Main menu to select the file, edit, compute, report functions
 for the statistics package. Starting point for the project.
 */
int main(int argc, char * argv[])
{

	int selection=0;
	int error_code = NO_ERROR;

	while (selection != EXIT_SEL)
    {
		selection = main_menu();
		switch (selection)
        {
			case FILE_SEL:
            {
				file_main_menu();
				selection = 0;
				break;
			}
			case EDIT_SEL:
            {
				edit_main_menu();
				break;
			}
			case COMPUTE_SEL:
            {
				compute_main_menu();
				break;
			}
            case REPORT_SEL:
            {
                report_main_menu();
                break;
            }
		}
	}
	clear_screen();
	printf("Thank you for using StatPac. Goodbye.\n");
	fflush(stdout);

	return error_code;
}

/*
  Validate that user made the right menu choice.
 */
int main_menu(void)
{
	int sel;
	char sel_s[3];

	print_main_menu();
	gets(sel_s);
	sel = atoi(sel_s);
	if (sel < FILE_SEL || sel > EXIT_SEL)
    {
		while (1)
        {
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

/*
  Prints the main menu choices.
 */
void print_main_menu (void)
{
	printf("StatPac main menu options.\n");
	printf("Main Menu: 1) File, 2) Edit, 3) Compute, 4) Report, 5) Exit\n");
	printf("Please choose an option: ");
	fflush(stdout);
}



