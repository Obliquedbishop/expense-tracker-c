#include<stdio.h>
#include<time.h>

struct expense
{
    int id;
    char name[100];
    char category[100];
    float amount;
};

int count=0;
struct expense ex[1000];


void add_expense()
{
    // assigned a unique ID to the new expense
    ex[count].id = count+1;
    
    // Time when expense was added
    time_t date;
    time(&date);

    printf("\nEnter expense name: ");
    scanf("%s",ex[count].name);
    printf("Enter expense category: ");
    scanf("%s",ex[count].category);
    printf("Enter expense amount: ");
    scanf("%f",&ex[count].amount);
    
    // TODO: Add a line telling user that expense has been added successfully along with the date and time of addition
    printf("\n");
    count++;
}

void view_expenses()
{
    printf("=======list of expenses=======\n");
    for(int i=0;i<count;i++)
        {
            // TODO: Add uniform spacing between the columns for better readability
            printf("\nexpense id:%d    expense name:%s    expense category:%s    expense amount:₹%0.2f"
                ,ex[i].id,ex[i].name,ex[i].category,ex[i].amount);
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
        printf("\n");
        
        // TODO: Implement error handling for invalid choice (choice should be either 1 or 2)

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
                    // TODO: Implement delete_expense() function and call it here
                    printf("Delete expense functionality is not implemented yet.\n");
                    break;
                case 4:
                    printf("Exiting the program. Goodbye!\n");
                    return 0;
            }
    }  
}