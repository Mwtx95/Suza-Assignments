#include "EduGamez.h"

// Helper functions
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Question class implementation
Question::Question() {}

Question::Question(const std::string& q, const std::string& opt1, const std::string& opt2, 
         const std::string& opt3, const std::string& opt4, int correct, const std::string& expl) 
: question(q), correctAnswer(correct), explanation(expl) {
    options[0] = opt1;
    options[1] = opt2;
    options[2] = opt3;
    options[3] = opt4;
}

const std::string& Question::getQuestion() const { return question; }
const std::string& Question::getOption(int index) const { return options[index]; }
int Question::getCorrectAnswer() const { return correctAnswer; }
const std::string& Question::getExplanation() const { return explanation; }

void Question::display() const {
    std::cout << "\n" << question << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << static_cast<char>('A' + i) << ") " << options[i] << std::endl;
    }
}

bool Question::checkAnswer(char userAnswer) const {
    int userChoice = std::toupper(userAnswer) - 'A';
    if (userChoice >= 0 && userChoice < 4) {
        if (userChoice == correctAnswer) {
            std::cout << "Correct! " << explanation << std::endl;
            return true;
        } else {
            std::cout << "Incorrect. The correct answer is " 
                      << static_cast<char>('A' + correctAnswer) << ". " 
                      << explanation << std::endl;
        }
    } else {
        std::cout << "Invalid input. Treated as incorrect." << std::endl;
        std::cout << "Correct answer is " << static_cast<char>('A' + correctAnswer)
                  << ". " << explanation << std::endl;
    }
    return false;
}

// QuestionQueue class implementation
QuestionQueue::QuestionQueue() {}

void QuestionQueue::enqueue(std::unique_ptr<Question> question) {
    questions.push_back(std::move(question));
}

std::unique_ptr<Question> QuestionQueue::dequeue() {
    if (questions.empty()) {
        return nullptr;
    }
    
    std::unique_ptr<Question> front = std::move(questions.front());
    questions.erase(questions.begin());
    return front;
}

bool QuestionQueue::isEmpty() const {
    return questions.empty();
}

size_t QuestionQueue::size() const {
    return questions.size();
}

// User class implementation
User::User() : score(0) {}

User::User(const std::string& uname, const std::string& pwd, 
     const std::string& dob, const std::string& grd) 
: username(uname), password(pwd), dateOfBirth(dob), grade(grd), score(0) {}

const std::string& User::getUsername() const { return username; }
const std::string& User::getPassword() const { return password; }
const std::string& User::getDateOfBirth() const { return dateOfBirth; }
const std::string& User::getGrade() const { return grade; }
int User::getScore() const { return score; }

void User::addScore(int points) {
    score += points;
}

int User::calculateAge() const {
    int year, month, day;
    sscanf(dateOfBirth.c_str(), "%4d-%2d-%2d", &year, &month, &day);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int age = tm.tm_year + 1900 - year;
    if (tm.tm_mon + 1 < month || (tm.tm_mon + 1 == month && tm.tm_mday < day)) {
        age--;
    }
    return age;
}

void User::displayProfile() const {
    std::cout << "\nProfile for " << username << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Date of Birth: " << dateOfBirth << std::endl;
    std::cout << "Age: " << calculateAge() << std::endl;
}

// UserManagement class implementation
UserManagement::UserManagement() {}

void UserManagement::addUser(std::unique_ptr<User> user) {
    users.push_back(std::move(user));
}

User* UserManagement::findUser(const std::string& username) {
    for (auto& user : users) {
        if (user->getUsername() == username) {
            return user.get();
        }
    }
    return nullptr;
}

bool UserManagement::isValidUsername(const std::string& username) {
    return username.length() >= 3;
}

bool UserManagement::isValidPassword(const std::string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (std::isupper(c)) hasUpper = true;
        else if (std::islower(c)) hasLower = true;
        else if (std::isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }

    return hasUpper && hasLower && hasSpecial && hasDigit;
}

bool UserManagement::isValidDate(const std::string& date) {
    int year, month, day;
    if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3) {
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
    
    // Calculate age based on date
    User tempUser("", "", date, "");
    int age = tempUser.calculateAge();
    if (age < MIN_AGE || age > MAX_AGE) {
        return false;
    }
    return true;
}

bool UserManagement::registerUser() {
    std::string username, password, confirmPassword, dob, grade;

    std::cout << "\n=== Registration ===\n";

    while (true) {
        std::cout << "Enter username: ";
        std::cin >> username;
        clearInputBuffer();

        if (isValidUsername(username)) {
            break;
        } else {
            std::cout << "Username must be at least 3 characters long! Please try again.\n";
        }
    }

    if (findUser(username) != nullptr) {
        std::cout << "Username already exists!\n";
        return false;
    }

    while (true) {
        std::cout << "Enter password: ";
        std::cin >> password;
        clearInputBuffer();

        if (isValidPassword(password)) {
            while (true) {
                std::cout << "Confirm password: ";
                std::cin >> confirmPassword;
                clearInputBuffer();

                if (password == confirmPassword) {
                    break;
                } else {
                    std::cout << "Passwords do not match! Please try again.\n";
                }
            }
            break;
        } else {
            std::cout << "Password must be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, one digit, and one special character.\n";
        }
    }

    while (true) {
        std::cout << "Enter date of birth (YYYY-MM-DD): ";
        std::cin >> dob;
        clearInputBuffer();

        if (isValidDate(dob)) {
            break;
        } else {
            std::cout << "Invalid date format or age not between " << MIN_AGE << " and " << MAX_AGE << "! Please try again.\n";
        }
    }

    int gradeChoice;
    while (true) {
        std::cout << "Choose grade:\n";
        std::cout << "1. STD IV\n";
        std::cout << "2. STD V\n";
        std::cout << "3. STD VI\n";
        std::cout << "4. STD VII\n";
        std::cout << "5. FORM I\n";
        std::cout << "6. FORM II\n";
        std::cout << "7. FORM III\n";
        std::cout << "8. FORM IV\n";
        std::cout << "Choice: ";
        std::cin >> gradeChoice;
        clearInputBuffer();

        switch (gradeChoice) {
            case 1: grade = "STD IV"; break;
            case 2: grade = "STD V"; break;
            case 3: grade = "STD VI"; break;
            case 4: grade = "STD VII"; break;
            case 5: grade = "FORM I"; break;
            case 6: grade = "FORM II"; break;
            case 7: grade = "FORM III"; break;
            case 8: grade = "FORM IV"; break;
            default:
                std::cout << "Invalid choice! Please try again.\n";
                continue;
        }
        break;
    }

    auto newUser = std::make_unique<User>(username, password, dob, grade);
    addUser(std::move(newUser));
    std::cout << "Registration successful!\n";
    return true;
}

User* UserManagement::loginUser() {
    std::string username, password;

    std::cout << "\n=== Login ===\n";
    std::cout << "Username: ";
    std::cin >> username;
    clearInputBuffer();

    std::cout << "Password: ";
    std::cin >> password;
    clearInputBuffer();

    User* user = findUser(username);
    if (user != nullptr && user->getPassword() == password) {
        std::cout << "Login successful!\n";
        std::cout << "Hello " << user->getUsername() << " welcome!\n";
        return user;
    }

    std::cout << "Invalid username or password!\n";
    return nullptr;
}

// LeaderboardEntry class implementation
LeaderboardEntry::LeaderboardEntry(const std::string& uname, int scr) : username(uname), score(scr) {}

const std::string& LeaderboardEntry::getUsername() const { return username; }
int LeaderboardEntry::getScore() const { return score; }

void LeaderboardEntry::addScore(int points) { score += points; }

// Leaderboard class implementation
Leaderboard::Leaderboard() {}

void Leaderboard::addEntry(const std::string& username, int score) {
    // Check if user already exists in leaderboard
    for (auto& entry : entries) {
        if (entry->getUsername() == username) {
            entry->addScore(score);
            sortEntries();
            return;
        }
    }

    // Add new entry if user doesn't exist
    entries.push_back(std::make_unique<LeaderboardEntry>(username, score));
    sortEntries();
}

void Leaderboard::sortEntries() {
    std::sort(entries.begin(), entries.end(), 
        [](const std::unique_ptr<LeaderboardEntry>& a, const std::unique_ptr<LeaderboardEntry>& b) {
            return a->getScore() > b->getScore();
        }
    );
}

void Leaderboard::displayLeaderboard() const {
    std::cout << "\n/-----------------------------------\\\n";
    std::cout << "| Username               | Score    |\n";
    std::cout << "|-----------------------------------|\n";

    for (const auto& entry : entries) {
        std::cout << "| " << std::left << std::setw(22) << entry->getUsername() 
                  << " | " << std::setw(8) << entry->getScore() << " |\n";
    }

    std::cout << "\\-----------------------------------/\n";
}

// Subject class implementation
Subject::Subject(const std::string& n) : name(n) {}
Subject::~Subject() {}

const std::string& Subject::getName() const { return name; }

// MathSubject implementation
MathSubject::MathSubject() : Subject("Math") {}

QuestionQueue MathSubject::createQuestions() {
    QuestionQueue queue;
    
    // Math Question 1
    queue.enqueue(std::make_unique<Question>(
        "What is 3 multiplied by 4?",
        "7", "12", "10", "15",
        1, "3 times 4 is 12."
    ));

    // Math Question 2
    queue.enqueue(std::make_unique<Question>(
        "What is the square root of 64?",
        "6", "7", "8", "9",
        2, "The square root of 64 is 8."
    ));

    // Math Question 3
    queue.enqueue(std::make_unique<Question>(
        "What is 10 divided by 2?",
        "2", "3", "5", "6",
        2, "10 divided by 2 is 5."
    ));

    return queue;
}

// EnglishSubject implementation
EnglishSubject::EnglishSubject() : Subject("English") {}

QuestionQueue EnglishSubject::createQuestions() {
    QuestionQueue queue;
    
    // English Question 1
    queue.enqueue(std::make_unique<Question>(
        "What is the synonym of 'happy'?",
        "Sad", "Joyful", "Angry", "Tired",
        1, "The synonym of 'happy' is 'joyful'."
    ));

    // English Question 2
    queue.enqueue(std::make_unique<Question>(
        "What is the antonym of 'difficult'?",
        "Easy", "Hard", "Complicated", "Tough",
        0, "The antonym of 'difficult' is 'easy'."
    ));

    // English Question 3
    queue.enqueue(std::make_unique<Question>(
        "What is the plural form of 'child'?",
        "Childs", "Children", "Childes", "Childrens",
        1, "The plural form of 'child' is 'children'."
    ));

    return queue;
}

// PhysicsSubject implementation
PhysicsSubject::PhysicsSubject() : Subject("Physics") {}

QuestionQueue PhysicsSubject::createQuestions() {
    QuestionQueue queue;
    
    // Physics Question 1
    queue.enqueue(std::make_unique<Question>(
        "What is the speed of light?",
        "300,000 km/s", "150,000 km/s", "450,000 km/s", "600,000 km/s",
        0, "The speed of light is 300,000 km/s."
    ));

    // Physics Question 2
    queue.enqueue(std::make_unique<Question>(
        "What is the unit of force?",
        "Joule", "Newton", "Watt", "Pascal",
        1, "The unit of force is Newton."
    ));

    // Physics Question 3
    queue.enqueue(std::make_unique<Question>(
        "What is the formula for kinetic energy?",
        "mv^2", "1/2 mv^2", "mgh", "F=ma",
        1, "The formula for kinetic energy is 1/2 mv^2."
    ));

    return queue;
}

// Test class implementation
Test::Test(User* u, Leaderboard& lb) : user(u), leaderboard(lb) {
    subjects.push_back(std::make_unique<MathSubject>());
    subjects.push_back(std::make_unique<EnglishSubject>());
    subjects.push_back(std::make_unique<PhysicsSubject>());
}

void Test::startTest() {
    if (!user) {
        std::cout << "No user logged in!" << std::endl;
        return;
    }

    std::cout << "Starting test for user: " << user->getUsername() << std::endl;
    std::cout << "Choose a subject:" << std::endl;
    
    for (size_t i = 0; i < subjects.size(); i++) {
        std::cout << (i + 1) << ". " << subjects[i]->getName() << std::endl;
    }
    
    std::cout << "Choice: ";
    int choice;
    std::cin >> choice;
    clearInputBuffer();

    if (choice >= 1 && choice <= static_cast<int>(subjects.size())) {
        int subjectIndex = choice - 1;
        std::cout << "You chose " << subjects[subjectIndex]->getName() << "." << std::endl;
        
        // Get questions for the selected subject
        QuestionQueue queue = subjects[subjectIndex]->createQuestions();
        processQuestions(queue);
    } else {
        std::cout << "Invalid choice!" << std::endl;
    }
}

void Test::processQuestions(QuestionQueue& queue) {
    int score = 0;
    int total = queue.size();

    while (!queue.isEmpty()) {
        auto question = queue.dequeue();
        question->display();

        std::cout << "Your answer (A-D): ";
        char answer;
        std::cin >> answer;
        clearInputBuffer();

        if (question->checkAnswer(answer)) {
            score++;
        }
    }

    user->addScore(score);
    std::cout << "Your score: " << score << "/" << total << std::endl;

    // Add to leaderboard
    leaderboard.addEntry(user->getUsername(), score);
}

// EduGamez class implementation
EduGamez::EduGamez() : currentUser(nullptr) {}

void EduGamez::displayMainMenu() {
    std::cout << "\n=== EduGamez ===\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Exit\n";
    std::cout << "Choice: ";
}

void EduGamez::displayUserMenu() {
    std::cout << "\n=== EduGamez - Data Structures & Algorithms ===\n";
    std::cout << "1. Start Test\n";
    std::cout << "2. View Leaderboard\n";
    std::cout << "3. View Profile\n";
    std::cout << "4. Logout\n";
    std::cout << "Choice: ";
}

void EduGamez::run() {
    int choice;
    
    while (true) {
        if (currentUser == nullptr) {
            displayMainMenu();
            std::cin >> choice;
            clearInputBuffer();

            switch (choice) {
                case 1:
                    currentUser = userManager.loginUser();
                    break;
                case 2:
                    userManager.registerUser();
                    break;
                case 3:
                    std::cout << "Thank you for using EduGamez!\n";
                    return;
                default:
                    std::cout << "Invalid choice!\n";
            }
        } else {
            displayUserMenu();
            std::cin >> choice;
            clearInputBuffer();

            switch (choice) {
                case 1: {
                    Test test(currentUser, leaderboard);
                    test.startTest();
                    break;
                }
                case 2:
                    leaderboard.displayLeaderboard();
                    break;
                case 3:
                    currentUser->displayProfile();
                    break;
                case 4:
                    currentUser = nullptr;
                    std::cout << "Logged out successfully!\n";
                    break;
                default:
                    std::cout << "Invalid choice!\n";
            }
        }
    }
}