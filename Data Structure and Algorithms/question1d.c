#include <stdio.h>
#include <string.h>
#define SIZE 100

struct Student {
    char name[50];
    int age;
};

struct Stack {
    int top;
    struct Student s[SIZE];
} st;

void push(struct Student item) {
    if (st.top >= SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    st.s[++st.top] = item;
}

struct Student pop() {
    struct Student empty = {"", -1};
    if (st.top == -1) {
        printf("Stack underflow\n");
        return empty;
    }
    return st.s[st.top--];
}

void display() {
    if (st.top == -1) {
        printf("Stack is empty\n");
        return;
    }
    for (int i = 0; i <= st.top; i++) {
        printf("Name: %s, Age: %d\n", st.s[i].name, st.s[i].age);
    }
}

int main() {
    st.top = -1; 
    int choice;
    do {
        printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct Student student;
                printf("Enter name: ");
                scanf("%s", student.name);
                printf("Enter age: ");
                scanf("%d", &student.age);
                push(student);
                break;
            }
            case 2: {
                struct Student removed = pop();
                if (removed.age != -1) {
                    printf("Popped student -> Name: %s, Age: %d\n", removed.name, removed.age);
                }
                break;
            }
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}

