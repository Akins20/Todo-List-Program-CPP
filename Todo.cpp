#include "TodoUtils.h"
using namespace std;

void welcomeUser()
{
    int choice;
    int choice2;

    cout << "Welcome to Todo List!" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Add a new todo item" << endl;
    cout << "2. Display the todo list" << endl;
    cout << "3. Update a list item by Id" << endl;
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