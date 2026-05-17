#include<stdio.h>
#include<time.h>
int count=0;
struct expense
{
    int id;
    char name[100];
    char category[100];
    float amount;
};
struct expense ex[1000];
struct expense *ext =ex;

int main()
{
    int choice;
    while(1)
    {
        printf("======EXPENSE TRACKER======");
    printf("\n\n\n1. Add expense\n2. View all expenses\n3. Delete expense\n4. Save and Exit.");
    printf("\nplease enter your choice=");
    scanf("%d",&choice);
    switch(choice)
        {
            case 1:
                    void add_expense();
                    add_expense();
                    break;
            case 2:
                    void view_expenses(struct expense *ext);
                    view_expenses(ex);
                    break;
        }
    }  
}
void add_expense()
{
    
    ex[count].id=count+1;
    printf("expense id:%d",ex[count].id);
    printf("\nenter expense name:");
    scanf("%s",&ex[count].name);
    printf("enter expense category:");
    scanf("%s",&ex[count].category);
    printf("enter expense amount:");
    scanf("%f",&ex[count].amount);
    time_t date;
    time(&date);
    printf("date:%s",ctime(&date));
    count++;
}
void view_expenses(struct expense *ext)
{
    
    printf("=======list of expenses=======\n");
    for(int i=0;i<count;i++)
        {
            printf("\nexpense id:%d    expense name:%s    expense category:%s    expense amount:%f"
                ,ext[i].id,ext[i].name,ext[i].category,ext[i].amount);
        }
}