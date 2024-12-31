#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	struct node *next;
};

struct node *head = NULL;

void  enq()
{
	struct node *newnode,*temp;
	newnode =  (struct node*)malloc(sizeof(struct node));
	printf("enter the value to enqueue\n");
	scanf("%d",&newnode->data);
	newnode->next = NULL;
	if(head==NULL)
	{
		head = newnode;
	}
	else
	{
		temp = head;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp-> next = newnode;
	}
	return;
}


void deq()

{
	struct node *temp;
	if(head == NULL)
	{
		printf("queue underflow\n");
		return;
	}
	else
	{
		temp = head;
		head = head->next;
		printf("the value %d has been dequeued\n",temp->data);
		free(temp);
	}
}


void display()
{
struct node *temp;
 if(head == NULL)
 {
 	printf("queue is underflow\n");
 	return;	
 }
 else
 {
 	temp = head;
 	printf("The queue has: \n");
 	while(temp!=NULL)
 	{
		printf("%d ",temp->data);
		temp = temp->next;
 	}
 	printf("\n");
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
			enq();
			break;

			case 2:
			deq();
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
