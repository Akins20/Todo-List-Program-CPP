#include <iostream>
#include <string>
#include <fstream>
#include <utility>
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
        int id;
        string description, content, completedStr;
        while (file >> id >> description >> content >> completedStr)
        {
            bool completed = completedStr == "Yes" ? true : false;
            TodoItem newItem;
            newItem.setId(id);
            newItem.setDescription(description);
            newItem.setContent(content);
            newItem.setCompleted(completed);

            // Add the loaded item to the todo list here using lambda functions...
            auto idDescription = [&newItem]() -> pair<int, string>
            {
                return make_pair(newItem.getId(), newItem.getDescription());
            };

            auto contentStatus = [&newItem]() -> pair<string, bool>
            {
                return make_pair(newItem.getContent(), newItem.getCompleted());
            };

            pair<int, string> idDesc = idDescription();
            pair<string, bool> conStat = contentStatus();

            cout << idDesc.first << " || " << idDesc.second << " || " << conStat.first << " || " << conStat.second << endl;
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
    cout << "Enter title: ";
    cin.clear();
    cin.ignore();
    getline(cin, description);
    cout << "Enter content: ";
    cin.clear();
    cin.ignore();
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
        cout << "Exiting..." << endl;
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
    cout << "3. Exit" << endl;
    cout << "Answer: ";
    cin >> choice;
    choice2 = determineChoice(choice);
    if(choice2 != 3){
        welcomeUser();
    }
}
// A simple To do list program
int main()
{
    welcomeUser();

    return 0;
}