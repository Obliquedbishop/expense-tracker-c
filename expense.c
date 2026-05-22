#include<stdio.h>
#include<time.h>
#include<string.h>

struct expense
{
    int id;
    char name[100];
    char category[100];
    float amount;
    time_t date;
    
};

int count=0;
struct expense ex[1000];


void add_expense()
{
    // assigned a unique ID to the new expense
    ex[count].id = count+1;
    // Time when expense was added
        time(&ex[count].date);
    //taking input of expenses 
    printf("\nEnter expense name: ");
    while(getchar() != '\n');
    fgets(ex[count].name,100,stdin);
    ex[count].name[strlen(ex[count].name)-1]='\0';
    printf("Enter expense category: ");
    fgets(ex[count].category,100,stdin);
    ex[count].category[strlen(ex[count].category)-1]='\0';
    printf("Enter expense amount: ");
    scanf("%f",&ex[count].amount);

    //Added a line telling user that expense has been added successfully along with the date and time of addition
    printf("You have successfully added an expense named %s under the category %s of amount %0.2f dated %s",ex[count].name,ex[count].category,ex[count].amount,ctime(&ex[count].date));
    printf("\n");
    count++;
}

void view_expenses()
{
    printf("====================list of expenses========================\n");
    printf("%-5s %-20s %-20s %-15s %-25s\n","ID","EXPENSE NAME","CATEGORY","AMOUNT","DATE");
    printf("============================================================\n");
    for(int i=0;i<count;i++)
        {
            printf("%-5d %-20s %-20s Rs.%-10.2f %-25.24s\n",ex[i].id,ex[i].name,ex[i].category,ex[i].amount,ctime(&ex[i].date));
            
        }
    printf("\n");
}

void delete_expense()
{
    int id,i,temp;
    //Asking for ID to be deleted
    printf("Enter the ID you want to delete= ");
        scanf("%d",&id);
    
    for(i=0;i<count;i++)
        {
            //searching for the ID
            if(ex[i].id==id)
                {
                    for(i=0;i<count;i++)
                    {
                        ex[i]= ex[i+1];//swapping the elements stored in the array 
                        ex[i].id=i+1;//changing ID's according to order
                    }  
                    count--;
                    printf("Expense deleted successfully\n");
                    break;
                }
            else if(ex[i].id!=id)
                {
                    printf("Sorry! Expense not found\n");
                }
        }
    printf("\n");
}

int main()
{
    int choice;
    while(1)
    {
        printf("======EXPENSE TRACKER======");
        printf("\n\n\n1. Add expense\n2. View all expenses\n3. Delete expense\n4. Exit.");
        printf("\nPlease enter your choice = ");
        scanf("%d",&choice);
        if (choice!=1&&choice!=2&&choice!=3&&choice!=4)
        {
            printf("Invalid choice");
            return(0);
        }
          // Calling CRUD functions based on user choice
        switch(choice)
            {
                case 1:
                    add_expense();
                    break;
                case 2:
                    view_expenses();
                    break;
                case 3:
                    delete_expense();
                    break;
                case 4:
                    printf("Exiting the program. Goodbye!\n");
                    return 0;
            }
        
    }  
}