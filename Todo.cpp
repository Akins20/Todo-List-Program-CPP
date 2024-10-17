#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
using namespace std;

const string TodoFileName = "TodoList.txt";

void clrScreen()
{
    system("cls");
}

class TodoItem
{
public:
    int id;
    string description;
    string content;
    bool completed;

    // Declare and define todo items setters and getters
    void setId(int a)
    {
        id = a;
    }
    void setDescription(string b)
    {
        description = b;
    }
    void setContent(string c)
    {
        content = c;
    }
    void setCompleted(bool d)
    {
        completed = d;
    }

    int getId()
    {
        return id;
    }
    string getDescription()
    {
        return description;
    }
    string getContent()
    {
        return content;
    }
    bool getCompleted()
    {
        return completed;
    }
};

// Function to load the todo list from file
void loadTodoList()
{
    ifstream file(TodoFileName);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string idStr, description, content, completedStr;
            getline(ss, idStr, ',');
            getline(ss, description, ',');
            getline(ss, content, ',');
            getline(ss, completedStr);

            int id = stoi(idStr);

            bool completed = (completedStr == "Yes");

            TodoItem newItem;
            newItem.setId(id);
            newItem.setDescription(description);
            newItem.setContent(content);
            newItem.setCompleted(completed);

            cout << newItem.getId() << " || " << newItem.getDescription() << " || " << newItem.getContent() << " || " << (newItem.getCompleted() ? "Yes" : "No") << endl;
        };
        file.close();
    }
}

// Function to display the todo list
void displayTodoList()
{
    cout << "List of Todo Items:" << endl;
    cout << "ID || Description || Content || Completed" << endl;
    loadTodoList();
    // Add more items to the list here...
}

// Function to fetch the todo list by id
void fetchTodoListByID(int id)
{
    ifstream file(TodoFileName);

    if (file.is_open())
    {
        string line;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            string todoIdStr, description, content, completedStr;
            getline(ss, todoIdStr, ',');
            int currentId = stoi(todoIdStr);

            // Check if the current line's ID matches the input ID
            if (currentId == id)
            {

                getline(ss, description, ',');
                getline(ss, content, ',');
                getline(ss, completedStr);

                bool completed = (completedStr == "Yes");

                TodoItem newItem;
                newItem.setId(currentId);
                newItem.setContent(content);
                newItem.setDescription(description);
                newItem.setCompleted(completed);

                cout << newItem.getId() << " || " << newItem.getDescription() << " || " << newItem.getContent() << " || " << (newItem.getCompleted() ? "Yes" : "No") << endl;
                found = true;
                break;
            }
            if (!found)
            {
                cout << "The inputted Id: " << id << " does not exist." << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "Error opening file: " << TodoFileName << endl;
    }
}

void saveTodoList(int id, string description, string content, bool completed)
{
    TodoItem newItem;
    newItem.setId(id);
    newItem.setDescription(description);
    newItem.setContent(content);
    newItem.setCompleted(completed);
    ofstream file(TodoFileName, ios::app);
    if (file.is_open())
    {
        file << newItem.getId() << ", " << newItem.getDescription() << ", "
             << newItem.getContent() << ", "
             << (newItem.getCompleted() ? "Yes" : "No") << endl;
        file.close();
    }
    else
    {
        cout << "Error opening file: " << TodoFileName << endl;
        return;
    }
}
void addTodoItem()
{
    int id;
    string description, content;
    string completedStr;
    bool completed;

    cout << "Enter list id: ";
    cin >> id;
    cin.ignore();

    cout << "Enter title: ";
    getline(cin, description);
    cout << "Enter content: ";
    getline(cin, content);
    cout << "Enter completed status (yes/no): ";
    cin >> completedStr;
    completed = (completedStr == "yes");
    saveTodoList(id, description, content, completed);

    cout << "Todo item added successfully!" << endl;
}

int determineChoice(int choice)
{
    switch (choice)
    {
    case 1:
        addTodoItem();
        break;
    case 2:
        displayTodoList();
        break;
    case 3:
        int inputId;
        cout << "Enter the list id: ";
        cin >> inputId;
        fetchTodoListByID(inputId);
        break;
    case 4:
        cout << "Exiting...";
        exit(0);
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
    }
    return choice;
}

void welcomeUser()
{
    int choice;
    int choice2;

    cout << "Welcome to Todo List!" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Add a new todo item" << endl;
    cout << "2. Display the todo list" << endl;
    cout << "3. Display a specific todo item by Id" << endl;
    cout << "4. Exit" << endl;
    cout << "Answer: ";
    cin >> choice;
    choice2 = determineChoice(choice);
    if (choice2 != 4)
    {
        welcomeUser();
    }
}
// A simple To do list program
int main()
{
    welcomeUser();

    return 0;
}