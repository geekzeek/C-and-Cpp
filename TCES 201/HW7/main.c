#include <stdio.h>
#define ID_LEN 7
#define NAME_LEN 21
//CHANGE THIS TO 2 for easy testing
#define EMP_LEN 2

typedef struct employee
{
   char id[ID_LEN];
   char name[NAME_LEN];
   int hours;
   float rate;
   float gross_pay;
} EMPLOYEE;


void input_employee(EMPLOYEE *);
void print_employee(const EMPLOYEE *);

int main()
{
    EMPLOYEE emps[EMP_LEN];
    int i;
    for (i=0; i<EMP_LEN; i++)
    {
        printf("\nEmployee %d: \n", (i+1));
        input_employee(&emps[i]);
    }

    puts("\n\nEmployees information:");
    for (i=0; i<EMP_LEN; i++)
    {
        printf("\nEmployee %d: \n", (i+1));
        print_employee(&emps[i]);
    }
    return 0;
}

/**
Gets input and initializes the structure members.
Calculates the gross pay and initializes it.
*/
void input_employee(EMPLOYEE *e)
{

    float overtime = 0;
    printf("\n\nEnter id: ");
    gets(e->id);
    printf("Enter name: ");
    gets(e->name);
    printf("Enter hours: ");
    scanf("%d", &e->hours);
    printf("Enter rate: ");
    scanf("%f", &e->rate);
    getchar();
    if(e->hours > 40)
    {
        overtime = 1.5*(e->hours - 40);
    }
    e->gross_pay = e->rate * (e->hours + overtime);
}

/**
Prints the employee information.
*/
void print_employee(const EMPLOYEE *e)
{
    printf("\nId: %s", e->id);
    printf("\nName: %s", e->name);
    printf("\nHours: %d", e->hours);
    printf("\nRate: %4.2f", e->rate);
    printf("\nGross Pay: %6.2f\n\n", e->gross_pay);
}
