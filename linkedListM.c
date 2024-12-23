#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

struct node *head = NULL;
/*single node*/
/*struct node *newnode = (struct node*)malloc(sizeof(struct  node));*/

void front_insertion()
{
	struct node *newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	printf("enter the element to be inserted\n");
	scanf("%d",&newnode->data);
	newnode->next = NULL;
	
	if(head == NULL)
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

void back_insertion()
{
	struct node *newnode, *temp;
	if(head ==NULL)
		front_insertion();
	else
	{
		newnode = (struct node*)malloc(sizeof(struct node));
		printf("enter the element to be inserted \n");
		scanf("%d",&newnode->data);
		newnode->next = NULL;
		temp = head;

		while(temp->next!=NULL)
		{
			temp = temp->next;
		}
		temp->next = newnode;
	}
		return;
}

void middle_insertion()
{
	struct node *newnode,*temp;
	int n;
	newnode = (struct node)malloc(sizeof(struct node));
	printf("enter the element to be inserted\n");
	scanf("%d",&newnode->data);
	printf("enter the node after which this node has to be inserted\n");
	scanf("%d",&n);
	temp = head;
	while(temp->data!=n && temp!=NULL)
		{
			temp = temp->next;
			newnode ->next = temp->next;
			temp->next = newnode;
			return;
		}
}

void front_deletion()
{
	struct node *temp;
	if(head == NULL)
		printf("the list is empty\n");
	else
	{
		temp = head;
		if(head->next == NULL)
		head = NULL;
		head = head->next;
		printf("the deleted node is %d\n",temp->data);
		free(temp);
	}
}

void back_deletion()
{
	struct node *temp,*prev;
	if(head == NULL)
	{
		printf("the list is empty\n")
		return;
	}
	else
	{
		temp = head;
		while(temp->next!=NULL)
		{
			prev = temp;
			temp = temp->next;
		}
		prev->next = NULL;
		if(prev->data==NULL)
		head = NULL;
		free(temp);
	}
	return;
}

void middle_deletion() {
    struct node *temp, *prev;
    int n;

    if (head == NULL) {
        printf("The list is empty\n");
        return;
    }

    printf("Enter the node to be deleted: ");
    scanf("%d", &n);

    temp = head;

    if (temp->data == n) {
        head = head->next;
        printf("The deleted node is %d\n", temp->data);
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != n) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Node not found\n", n);
        return;
    }

    prev->next = temp->next;
    printf("The deleted node is %d\n", temp->data);
    free(temp);
    return;
}

void display()
{
	struct node *temp;
	/*head = temp;*/
	temp = head; 
	while(temp!=NULL)
	{
		printf("%d\n",temp->data);
		temp = temp->next;
	}
}

int main()
{
	front_insertion();
	back_insertion();
	display();
}
