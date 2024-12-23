#include <stdio.h>
#define size 100

struct stack 
{
int top;
int s[size];
}st;

void push(int item)
{
if (st.top >=size-1){
printf("stack overflow\n");
}
st.s[++st.top] = item;
}

int pop()
{
if ( st.top == -1)
{
printf("stack underflow\n");
return -1;
}
int item = st.s[st.top];
st.top--;
return item;
}
void  display()
{
for ( int i = 0; i<=st.top;i++)
printf("%d",st.s[i]);
}

int main()
{

st.top = -1;
int choice = 1, value;

while (choice == 1)
{

printf("enter choices:\n");
printf("1. push\n");
printf("2.pop\n");
printf("3.display\n");
scanf("%d",&choice);

switch(choice)
{
case 1:
printf("enter the value: \n");
scanf("%d",&value);
push(value);
break;

case 2:
value = pop();
if (value != -1)
{
printf(" the popped value is %d \n",value);
}
break;

case 3:
display();
break;
default:
 printf("Invalid choice. Please try again.\n");
}
printf("do you wish to countinue, press 1 for yes 0 for no: \n");
scanf("%d",&choice);
}
}

