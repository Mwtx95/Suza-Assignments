#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *head = NULL;

void front_insertion()
{
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    printf("enter the element to be inserted\n");
    scanf("%d", &newnode->data);
    newnode->next = NULL;

    if (head == NULL)
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
    if (head == NULL)
        front_insertion();
    else
    {
        newnode = (struct node*)malloc(sizeof(struct node));
        printf("enter the element to be inserted \n");
        scanf("%d", &newnode->data);
        newnode->next = NULL;
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
    return;
}

void front_deletion()
{
    struct node *temp;
    if (head == NULL)
        printf("the list is empty\n");
    else
    {
        temp = head;
        if (head->next == NULL)
            head = NULL;
        head = head->next;
        printf("the deleted node is %d\n", temp->data);
        free(temp);
    }
}

void back_deletion()
{
    struct node *temp, *prev;
    if (head == NULL)
    {
        printf("the list is empty\n");
        return;
    }
    else
    {
        temp = head;
        while (temp->next != NULL)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = NULL;
        if (prev->data == NULL)
            head = NULL;
        free(temp);
    }
    return;
}

void remove_duplicates()
{
    struct node *temp1, *temp2, *prev;
    temp1 = head;
    while (temp1 != NULL && temp1->next != NULL)
    {
        prev = temp1;
        temp2 = temp1->next;
        while (temp2 != NULL)
        {
            if (temp1->data == temp2->data)
            {
                prev->next = temp2->next;
                free(temp2);
                temp2 = prev->next;
            }
            else
            {
                prev = temp2;
                temp2 = temp2->next;
            }
        }
        temp1 = temp1->next;
    }
}

void display()
{
    struct node *temp;
    temp = head;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

