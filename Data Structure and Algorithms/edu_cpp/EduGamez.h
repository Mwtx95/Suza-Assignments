#ifndef EDUGAMEZ_H
#define EDUGAMEZ_H

#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <vector>
#include <memory>
#include <iomanip>
#include <algorithm>

// Constants
const int MAX_LENGTH = 50;
const int MIN_AGE = 8;
const int MAX_AGE = 20;

// Forward declarations
class User;
class Leaderboard;
class Question;
class QuestionQueue;

// Helper functions
void clearInputBuffer();

// Base class for Question
class Question {
private:
    std::string question;
    std::string options[4];
    int correctAnswer;
    std::string explanation;

public:
    Question();
    Question(const std::string& q, const std::string& opt1, const std::string& opt2, 
             const std::string& opt3, const std::string& opt4, int correct, const std::string& expl);

    const std::string& getQuestion() const;
    const std::string& getOption(int index) const;
    int getCorrectAnswer() const;
    const std::string& getExplanation() const;

    void display() const;
    bool checkAnswer(char userAnswer) const;
};

// QuestionQueue class
class QuestionQueue {
private:
    std::vector<std::unique_ptr<Question>> questions;

public:
    QuestionQueue();
    void enqueue(std::unique_ptr<Question> question);
    std::unique_ptr<Question> dequeue();
    bool isEmpty() const;
    size_t size() const;
};

// User class
class User {
private:
    std::string username;
    std::string password;
    std::string dateOfBirth;
    std::string grade;
    int score;

public:
    User();
    User(const std::string& uname, const std::string& pwd, 
         const std::string& dob, const std::string& grd);

    // Getters
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::string& getDateOfBirth() const;
    const std::string& getGrade() const;
    int getScore() const;

    // Method to add score
    void addScore(int points);

    // Calculate age
    int calculateAge() const;

    // Display user profile
    void displayProfile() const;
};

// UserManagement class
class UserManagement {
private:
    std::vector<std::unique_ptr<User>> users;
    
public:
    UserManagement();

    // Add a new user
    void addUser(std::unique_ptr<User> user);

    // Find user by username
    User* findUser(const std::string& username);

    // Validate username
    static bool isValidUsername(const std::string& username);

    // Validate password
    static bool isValidPassword(const std::string& password);

    // Validate date format and age
    static bool isValidDate(const std::string& date);

    // Register a new user
    bool registerUser();

    // Login a user
    User* loginUser();
};

// LeaderboardEntry class
class LeaderboardEntry {
private:
    std::string username;
    int score;

public:
    LeaderboardEntry(const std::string& uname, int scr);

    const std::string& getUsername() const;
    int getScore() const;
    
    void addScore(int points);
};

// Leaderboard class
class Leaderboard {
private:
    std::vector<std::unique_ptr<LeaderboardEntry>> entries;

public:
    Leaderboard();

    // Add entry to leaderboard
    void addEntry(const std::string& username, int score);

    // Sort leaderboard entries by score (descending)
    void sortEntries();

    // Display leaderboard
    void displayLeaderboard() const;
};

// Subject class (base class for specific subjects)
class Subject {
protected:
    std::string name;

public:
    Subject(const std::string& n);
    virtual ~Subject();

    const std::string& getName() const;
    virtual QuestionQueue createQuestions() = 0;
};

// Math subject
class MathSubject : public Subject {
public:
    MathSubject();
    QuestionQueue createQuestions() override;
};

// English subject
class EnglishSubject : public Subject {
public:
    EnglishSubject();
    QuestionQueue createQuestions() override;
};

// Physics subject
class PhysicsSubject : public Subject {
public:
    PhysicsSubject();
    QuestionQueue createQuestions() override;
};

// Test class to manage the testing process
class Test {
private:
    User* user;
    Leaderboard& leaderboard;
    std::vector<std::unique_ptr<Subject>> subjects;

public:
    Test(User* u, Leaderboard& lb);
    void startTest();
    void processQuestions(QuestionQueue& queue);
};

// EduGamez class (main application)
class EduGamez {
private:
    UserManagement userManager;
    Leaderboard leaderboard;
    User* currentUser;

public:
    EduGamez();
    void displayMainMenu();
    void displayUserMenu();
    void run();
};

#endif // EDUGAMEZ_H