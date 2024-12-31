#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

struct node *head = NULL;

void push()
{
	struct node *newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	printf("enter the element you wanna push:\n");
	scanf("%d",&newnode->data);
	newnode->next = NULL;
	if(head==NULL)
	{
		head = newnode;
	}
	else
	{
		newnode->next = head;
		head = newnode;
	}
	return;
}

void pop()
{
	struct node *temp;
	if(head == NULL)
	{
		printf("Stack is empty!");
		return;
	}
	else
	{
		temp = head;
		if(head->next == NULL)
			head = NULL;
		else
		{
			head = head->next;
		}
		printf("the deleted value is %d\n",temp->data);
		free(temp);
	}
}
void display()
{
	struct node *temp;
	temp = head;
	if(head == NULL)
	printf("stack is empty\n");
	while(temp!=NULL)
	{
		printf("%d\n",temp->data);
		temp = temp->next;
	}
}

int main()
{
	int choice = 1;

	while(choice==1)
	{
		printf("enter choices:\n");
		printf("1.push\n");
		printf("2.pop\n");
		printf("3.display\n");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
			push();
			break;

			case 2:
			pop();
			break;

			case 3:
			display();
			break;
			default:
			printf("you entered wrong choice\n");
		}
		printf("Do you wish to countinue 1(yes)/0(no)");
		scanf("%d",&choice);
	}
}
