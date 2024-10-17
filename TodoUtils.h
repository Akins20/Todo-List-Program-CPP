#ifdef TODOUTILS_H
#endif
#define TODOUTILS_H

#include "TodoItem.h"
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <vector>

const string TodoFileName = "TodoList.txt";
const string TempTodoFile = "TempTodo.txt";

void clrScreen()
{
    system("cls");
}

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

// Function to fetch the todo list by id and return the data in a vector
vector<string> fetchTodoListByID(int id)
{
    ifstream file(TodoFileName);
    vector<string> todoData;

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

                // bool completed = (completedStr == "Yes");

                todoData.push_back(todoIdStr);
                todoData.push_back(description);
                todoData.push_back(content);
                todoData.push_back(completedStr);

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

    return todoData;
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

void updateTodoListById(int inputtedId)
{
    cout << "Updating Todo List by ID: " << inputtedId << endl;
    cout << "Leave empty to skip....." << endl;
    // Add code to update the todo list by ID here...

    vector<string> todoData = fetchTodoListByID(inputtedId);

    if (todoData.empty())
    {
        cout << "No item found with whe provided ID: " << inputtedId << endl;
        return;
    }
    else
    {
        string description = todoData[1];
        string content = todoData[2];
        string newDescription, newContent, newCompletedStr;

        // Display the current data for user to modify
        cout << "Current title: " << description << endl;
        cout << "Enter new title to update: ";
        cin.ignore();
        getline(cin, newDescription);
        if (!newDescription.empty())
        {
            todoData[1] = newDescription;
        }

        cout << "Current content: " << content << endl;
        cout << "Enter new content to update: ";
        getline(cin, newContent);
        if (!newContent.empty())
        {
            todoData[2] = newContent;
        }

        cout << "Enter new completed status (yes/no) to update: ";
        cin >> newCompletedStr;

        todoData[3] = (newCompletedStr == "yes") ? "Yes" : "No"; // Update completed status

        // Now save the updated todo list back to the file
        // To do this, you need to read all data from the file, replace the updated todo, and rewrite the file
        ifstream fileIn(TodoFileName);
        ofstream tempFile(TempTodoFile);

        if (fileIn.is_open() && tempFile.is_open())
        {
            string line;
            while (getline(fileIn, line))
            {
                stringstream ss(line);
                string todoIdStr;
                getline(ss, todoIdStr, ',');
                int currentId = stoi(todoIdStr);

                if (currentId == inputtedId)
                {
                    // Write the inputted data to the tempfile
                    tempFile << currentId << "," << todoData[1] << "," << todoData[2] << "," << todoData[3] << endl;
                }
                else
                {
                    // Write the original data to the tempfile
                    tempFile << line << endl;
                }
            }
            fileIn.close();
            tempFile.close();

            // Now replace the original file with the updated temp file
            remove(TodoFileName.c_str());
            rename("TempTodo", TodoFileName.c_str());

            cout << "Todo list updated successfully!" << endl;
        }
        else
        {
            cout << "Error opening file: " << TodoFileName << " or updating." << endl;
            return;
        }
    }
}

// Function to determine the user choice and return the right function
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
        cout << "Enter id: ";
        cin >> inputId;
        updateTodoListById(inputId);
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

// End of file
