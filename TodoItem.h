#ifdef TODOITEM_H
#endif
#define TODOITEM_H
#include <string>

using namespace std;

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
