#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LENGTH 50
#define MIN_AGE 8
#define MAX_AGE 20

// Data Structures
typedef struct UserNode {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char dob[11];
    char grade[MAX_LENGTH];
    int score;
    struct UserNode* next;
} UserNode;

typedef struct LeaderboardNode {
    char username[MAX_LENGTH];
    int score;
    struct LeaderboardNode* next;
} LeaderboardNode;

typedef struct QuestionNode {
    char question[200];
    char options[4][50];
    int correct_answer;
    char explanation[200];
    struct QuestionNode* next;
} QuestionNode;

typedef struct {
    QuestionNode *front;
    QuestionNode *rear;
    int size;
} QuestionQueue;

// Global variables
UserNode* userList = NULL;
LeaderboardNode* leaderboard = NULL;

// Function prototypes
UserNode* createUserNode(const char* username, const char* password, const char* dob, const char* grade);
void insertUser(UserNode** head, UserNode* newNode);
UserNode* findUser(UserNode* head, const char* username);
void registerUser();
UserNode* loginUser();
void displayMenu();
void startTest(UserNode* currentUser);
void processQuestions(QuestionQueue* q, UserNode* user);
void clearInputBuffer();

QuestionQueue* createQuestionQueue();
void enqueueQuestion(QuestionQueue* q, QuestionNode* question);
QuestionNode* dequeueQuestion(QuestionQueue* q);

// Leaderboard functions
void addToLeaderboard(LeaderboardNode** head, const char* username, int score);
LeaderboardNode* sortLeaderboard(LeaderboardNode* head);
void displayLeaderboard(LeaderboardNode* head);

// Helper Functions
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// User Management Functions
UserNode* createUserNode(const char* username, const char* password, const char* dob, const char* grade) {
    UserNode* newNode = (UserNode*)malloc(sizeof(UserNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->username, username);
    strcpy(newNode->password, password);
    strcpy(newNode->dob, dob);
    strcpy(newNode->grade, grade);
    newNode->score = 0;
    newNode->next = NULL;
    return newNode;
}

void insertUser(UserNode** head, UserNode* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    UserNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

UserNode* findUser(UserNode* head, const char* username) {
    UserNode* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to calculate age
int calculateAge(const char* dob) {
    int year, month, day;
    sscanf(dob, "%4d-%2d-%2d", &year, &month, &day);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int age = tm.tm_year + 1900 - year;
    if (tm.tm_mon + 1 < month || (tm.tm_mon + 1 == month && tm.tm_mday < day)) {
        age--;
    }
    return age;
}

// Function to validate username
bool isValidUsername(const char* username) {
    return strlen(username) >= 3;
}

// Function to validate password
bool isValidPassword(const char* password) {
    if (strlen(password) < 8) {
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else hasSpecial = true;
    }

    return hasUpper && hasLower && hasSpecial && hasDigit;
}


// Function to validate date format and age
bool isValidDate(const char* date) {
    int year, month, day;
    if (sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return false;
    }
    if (year < 1900 || year > 2100) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28)) {
            return false;
        }
    }
    int age = calculateAge(date);
    if (age < MIN_AGE || age > MAX_AGE) {
        return false;
    }
    return true;
}

void registerUser() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char confirmPassword[MAX_LENGTH];
    char dob[11];
    char grade[MAX_LENGTH];

    printf("\n=== Registration ===\n");

    while (1) {
        printf("Enter username: ");
        scanf("%s", username);
        clearInputBuffer();

        if (isValidUsername(username)) {
            break;
        } else {
            printf("Username must be at least 4 characters long! Please try again.\n");
        }
    }

    if (findUser(userList, username) != NULL) {
        printf("Username already exists!\n");
        return;
    }

    while (1) {
        printf("Enter password: ");
        scanf("%s", password);
        clearInputBuffer();

        if (isValidPassword(password)) {
            while (1) {
                printf("Confirm password: ");
                scanf("%s", confirmPassword);
                clearInputBuffer();

                if (strcmp(password, confirmPassword) == 0) {
                    break;
                } else {
                    printf("Passwords do not match! Please try again.\n");
                }
            }
            break;
        } else {
            printf("Password must be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, one digit, and one special character.\n");
        }
    }

    while (1) {
        printf("Enter date of birth (YYYY-MM-DD): ");
        scanf("%s", dob);
        clearInputBuffer();

        if (isValidDate(dob)) {
            break;
        } else {
            printf("Invalid date format or age not between %d and %d! Please try again.\n", MIN_AGE, MAX_AGE);
        }
    }

    int gradeChoice;
    while (1) {
        printf("Choose grade:\n");
        printf("1. STD IV\n");
        printf("2. STD V\n");
        printf("3. STD VI\n");
        printf("4. STD VII\n");
        printf("5. FORM I\n");
        printf("6. FORM II\n");
        printf("7. FORM III\n");
        printf("8. FORM IV\n");
        printf("Choice: ");
        scanf("%d", &gradeChoice);
        clearInputBuffer();

        switch (gradeChoice) {
            case 1: strcpy(grade, "STD IV"); break;
            case 2: strcpy(grade, "STD V"); break;
            case 3: strcpy(grade, "STD VI"); break;
            case 4: strcpy(grade, "STD VII"); break;
            case 5: strcpy(grade, "FORM I"); break;
            case 6: strcpy(grade, "FORM II"); break;
            case 7: strcpy(grade, "FORM III"); break;
            case 8: strcpy(grade, "FORM IV"); break;
            default:
                printf("Invalid choice! Please try again.\n");
                continue;
        }
        break;
    }

    UserNode* newUser = createUserNode(username, password, dob, grade);
    insertUser(&userList, newUser);
    printf("Registration successful!\n");
}

UserNode* loginUser() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("\n=== Login ===\n");
    printf("Username: ");
    scanf("%s", username);
    clearInputBuffer();

    printf("Password: ");
    scanf("%s", password);
    clearInputBuffer();

    UserNode* user = findUser(userList, username);
    if (user != NULL && strcmp(user->password, password) == 0) {
        printf("Login successful!\n");
        printf("Hello %s welcome! \n", user->username);
        return user;
    }

    printf("Invalid username or password!\n");
    return NULL;
}

void displayMenu() {
    printf("\n=== EduGamez - Data Structures & Algorithms ===\n");
    printf("1. Start Test\n");
    printf("2. View Leaderboard\n");
    printf("3. View Profile\n");
    printf("4. Logout\n");
    printf("Choice: ");
}

// Question Queue Functions
QuestionQueue* createQuestionQueue() {
    QuestionQueue* q = (QuestionQueue*)malloc(sizeof(QuestionQueue));
    if (q == NULL) {
        printf("Memory allocation failed for question queue.\n");
        exit(1);
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueueQuestion(QuestionQueue* q, QuestionNode* question) {
    if (q == NULL || question == NULL) return;
    question->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = question;
    } else {
        q->rear->next = question;
        q->rear = question;
    }
    q->size++;
}

QuestionNode* dequeueQuestion(QuestionQueue* q) {
    if (q == NULL || q->front == NULL) return NULL;
    QuestionNode* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    q->size--;
    return temp;
}

void processQuestions(QuestionQueue* q, UserNode* user) {
    int score = 0;
    int total = q->size;

    while (q->front != NULL) {
        QuestionNode* current = dequeueQuestion(q);
        printf("\n%s\n", current->question);
        for (int i = 0; i < 4; i++) {
            printf("%c) %s\n", 'A' + i, current->options[i]);
        }

        printf("Your answer (A-D): ");
        char answer;
        scanf(" %c", &answer);
        clearInputBuffer();

        int userChoice = toupper(answer) - 'A';
        if (userChoice >= 0 && userChoice < 4) {
            if (userChoice == current->correct_answer) {
                printf("Correct! %s\n", current->explanation);
                score++;
            } else {
                printf("Incorrect. The correct answer is %c. %s\n",
                       'A' + current->correct_answer, current->explanation);
            }
        } else {
            printf("Invalid input. Treated as incorrect.\n");
            printf("Correct answer is %c. %s\n",
                   'A' + current->correct_answer, current->explanation);
        }

        free(current);
    }

    user->score += score;
    printf("Your score: %d/%d\n", score, total);
    free(q);

    // Add to leaderboard
    addToLeaderboard(&leaderboard, user->username, score);
    leaderboard = sortLeaderboard(leaderboard);
}

void startTest(UserNode* currentUser) {
    int subjectChoice;

    printf("Starting test for user: %s\n", currentUser->username);
    printf("Choose a subject:\n");
    printf("1. Math\n");
    printf("2. English\n");
    printf("3. Physics\n");
    printf("Choice: ");
    scanf("%d", &subjectChoice);
    clearInputBuffer();

    switch (subjectChoice) {
        case 1: {
            printf("You chose Math.\n");
            QuestionQueue* mathQueue = createQuestionQueue();

            // Math Question 1
            QuestionNode* q1 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q1->question, "What is 3 multiplied by 4?");
            strcpy(q1->options[0], "7");
            strcpy(q1->options[1], "12");
            strcpy(q1->options[2], "10");
            strcpy(q1->options[3], "15");
            q1->correct_answer = 1;
            strcpy(q1->explanation, "3 times 4 is 12.");
            enqueueQuestion(mathQueue, q1);

            // Math Question 2
            QuestionNode* q2 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q2->question, "What is the square root of 64?");
            strcpy(q2->options[0], "6");
            strcpy(q2->options[1], "7");
            strcpy(q2->options[2], "8");
            strcpy(q2->options[3], "9");
            q2->correct_answer = 2;
            strcpy(q2->explanation, "The square root of 64 is 8.");
            enqueueQuestion(mathQueue, q2);

            // Math Question 3
            QuestionNode* q3 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q3->question, "What is 10 divided by 2?");
            strcpy(q3->options[0], "2");
            strcpy(q3->options[1], "3");
            strcpy(q3->options[2], "5");
            strcpy(q3->options[3], "6");
            q3->correct_answer = 2;
            strcpy(q3->explanation, "10 divided by 2 is 5.");
            enqueueQuestion(mathQueue, q3);

            processQuestions(mathQueue, currentUser);
            break;
        }
        case 2: {
            printf("You chose English.\n");
            QuestionQueue* englishQueue = createQuestionQueue();

            // English Question 1
            QuestionNode* q1 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q1->question, "What is the synonym of 'happy'?");
            strcpy(q1->options[0], "Sad");
            strcpy(q1->options[1], "Joyful");
            strcpy(q1->options[2], "Angry");
            strcpy(q1->options[3], "Tired");
            q1->correct_answer = 1;
            strcpy(q1->explanation, "The synonym of 'happy' is 'joyful'.");
            enqueueQuestion(englishQueue, q1);

            // English Question 2
            QuestionNode* q2 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q2->question, "What is the antonym of 'difficult'?");
            strcpy(q2->options[0], "Easy");
            strcpy(q2->options[1], "Hard");
            strcpy(q2->options[2], "Complicated");
            strcpy(q2->options[3], "Tough");
            q2->correct_answer = 0;
            strcpy(q2->explanation, "The antonym of 'difficult' is 'easy'.");
            enqueueQuestion(englishQueue, q2);

            // English Question 3
            QuestionNode* q3 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q3->question, "What is the plural form of 'child'?");
            strcpy(q3->options[0], "Childs");
            strcpy(q3->options[1], "Children");
            strcpy(q3->options[2], "Childes");
            strcpy(q3->options[3], "Childrens");
            q3->correct_answer = 1;
            strcpy(q3->explanation, "The plural form of 'child' is 'children'.");
            enqueueQuestion(englishQueue, q3);

            processQuestions(englishQueue, currentUser);
            break;
        }
        case 3: {
            printf("You chose Physics.\n");
            QuestionQueue* physicsQueue = createQuestionQueue();

            // Physics Question 1
            QuestionNode* q1 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q1->question, "What is the speed of light?");
            strcpy(q1->options[0], "300,000 km/s");
            strcpy(q1->options[1], "150,000 km/s");
            strcpy(q1->options[2], "450,000 km/s");
            strcpy(q1->options[3], "600,000 km/s");
            q1->correct_answer = 0;
            strcpy(q1->explanation, "The speed of light is 300,000 km/s.");
            enqueueQuestion(physicsQueue, q1);

            // Physics Question 2
            QuestionNode* q2 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q2->question, "What is the unit of force?");
            strcpy(q2->options[0], "Joule");
            strcpy(q2->options[1], "Newton");
            strcpy(q2->options[2], "Watt");
            strcpy(q2->options[3], "Pascal");
            q2->correct_answer = 1;
            strcpy(q2->explanation, "The unit of force is Newton.");
            enqueueQuestion(physicsQueue, q2);

            // Physics Question 3
            QuestionNode* q3 = (QuestionNode*)malloc(sizeof(QuestionNode));
            strcpy(q3->question, "What is the formula for kinetic energy?");
            strcpy(q3->options[0], "mv^2");
            strcpy(q3->options[1], "1/2 mv^2");
            strcpy(q3->options[2], "mgh");
            strcpy(q3->options[3], "F=ma");
            q3->correct_answer = 1;
            strcpy(q3->explanation, "The formula for kinetic energy is 1/2 mv^2.");
            enqueueQuestion(physicsQueue, q3);

            processQuestions(physicsQueue, currentUser);
            break;
        }
        default:
            printf("Invalid choice!\n");
            break;
    }
}

// Leaderboard Functions
void addToLeaderboard(LeaderboardNode** head, const char* username, int score) {
    LeaderboardNode* current = *head;
    LeaderboardNode* prev = NULL;

    // Check if username exists in leaderboard
    while (current != NULL && strcmp(current->username, username) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        // Update score if username exists
        current->score += score;
    } else {
        // Add new user to leaderboard
        LeaderboardNode* newNode = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
        strcpy(newNode->username, username);
        newNode->score = score;
        newNode->next = NULL;

        if (prev == NULL) {
            *head = newNode;
        } else {
            prev->next = newNode;
        }
    }
}

LeaderboardNode* sortLeaderboard(LeaderboardNode* head) {
    if (head == NULL || head->next == NULL) return head;

    LeaderboardNode *sorted = NULL, *current = head;

    while (current != NULL) {
        LeaderboardNode* next = current->next;
        LeaderboardNode* insert = sorted;
        LeaderboardNode* prev = NULL;

        while (insert != NULL && insert->score >= current->score) {
            prev = insert;
            insert = insert->next;
        }

        current->next = insert;
        if (prev == NULL) {
            sorted = current;
        } else {
            prev->next = current;
        }

        current = next;
    }

    return sorted;
}

void displayLeaderboard(LeaderboardNode* head) {
    printf("\n/-----------------------------------\\\n");
    printf("| Username               | Score    |\n");
    printf("|-----------------------------------|\n");

    LeaderboardNode* current = head;
    while (current != NULL) {
        printf("| %-22s | %-8d |\n", current->username, current->score);
        current = current->next;
    }

    printf("\\-----------------------------------/\n");
}

// Main function
int main() {
    int choice;
    UserNode* currentUser = NULL;

    while (1) {
        if (currentUser == NULL) {
            printf("\n=== EduGamez ===\n");
            printf("1. Login\n");
            printf("2. Register\n");
            printf("3. Exit\n");
            printf("Choice: ");

            scanf("%d", &choice);
            clearInputBuffer();

            switch (choice) {
                case 1:
                    currentUser = loginUser();
                    break;
                case 2:
                    registerUser();
                    break;
                case 3:
                    printf("Thank you for using EduGamez!\n");
                    return 0;
                default:
                    printf("Invalid choice!\n");
            }
        } else {
            displayMenu();
            scanf("%d", &choice);
            clearInputBuffer();

            switch (choice) {
                case 1:
                    startTest(currentUser);
                    break;
                case 2:
                    displayLeaderboard(leaderboard);
                    break;
                case 3:
                    printf("\nProfile for %s\n", currentUser->username);
                    printf("Grade: %s\n", currentUser->grade);
                    printf("Score: %d\n", currentUser->score);
                    printf("Date of Birth: %s\n", currentUser->dob);
                    printf("Age: %d\n", calculateAge(currentUser->dob));
                    break;
                case 4:
                    currentUser = NULL;
                    printf("Logged out successfully!\n");
                    break;
                default:
                    printf("Invalid choice!\n");
            }
        }
    }
}
