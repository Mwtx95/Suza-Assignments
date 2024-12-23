#include <stdio.h>
#define size 100

struct stack 
{
    int top;
    int s[size];
} st;

void push(int item)
{
    if (st.top >= size - 1) {
        printf("stack overflow\n");
    } else {
        st.s[++st.top] = item;
    }
}

int pop()
{
    if (st.top == -1) {
        printf("stack underflow\n");
        return -1;
    }
    int item = st.s[st.top];
    st.top--;
    return item;
}

void display()
{
    for (int i = 0; i <= st.top; i++) {
        printf("%d", st.s[i]);
    }
}

int checkParentheses(char *expression)
{
    st.top = -1;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(') {
            push('(');
        } else if (expression[i] == ')') {
            if (pop() == -1) {
                return 0;
            }
        }
    }
    return (st.top == -1);
}

int main()
{
    char expression[size];
    printf("Enter an expression: ");
    scanf("%s", expression);

    if (checkParentheses(expression)) {
        printf("Parentheses are balanced\n");
    } else {
        printf("Parentheses are not balanced\n");
    }

    return 0;
}

