#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <set> // to ensure ID's don't duplicate.
#include <limits> // so can clear the input buffer to avoid bugs.



/*
1. Changed "int id" to unsigned char instead sunce originally the largest ID the code supported was 100, now it's 256 with less space.
2. Ensured that ID's don't duplcate.
3. Decided to add const unsigned char numberOfIds so I can test how the program behaves when reaching the limit of possible ID's which is 256 for an unsigned char.
4. Changed all strings to wstrings to support MBCS.
5. Added functionality to remove Todos the program runs out of accecible IDs.
6. Added functionality to clear input buffet after reading input from user to prevent potential errors caused by residual or unwanted input data being processed later in the program.
*/

// using namespace std; I commented this out for a few reasons like Namespace Pollutions and Name Conflicts and a few more reasons.




//numberOfids should be equal to 256 so it 
const unsigned char numberOfIds{ 2 }; // Implemented for debugging and testing purposes.



class TodoItem
{
private:
    static std::set<unsigned char> usedIds;
    unsigned int id{};
    std::wstring description;
    bool completed;
public:

    TodoItem() : id(0), description(L""), completed(false) {}
    ~TodoItem() = default;

    bool create(std::wstring new_description)
    {
        unsigned char newId;
        do {
            newId = rand() % numberOfIds + 1;
        } while (usedIds.count(newId) > 0); // Keep generating until a unique ID is found
        id = newId;
        usedIds.insert(id);
        description = new_description;
        return true;
    }

    unsigned char getId() { return id; }
    std::wstring getDescription() { return description; }
    bool isCompleted() { return completed; }

    void setCompleted(bool val) { completed = val; };
    static size_t getUsedIdsSize() { return usedIds.size(); }
    static void removeUsedId(unsigned char id) {
        usedIds.erase(id);
    }
};

std::set<unsigned char> TodoItem::usedIds;

int main()
{

    // Seed the random number generator
    char input_option;
    int input_id;
    std::wstring input_description;
    std::wstring version = L"v0.2.0"; 
    std::list<TodoItem> todoItems;
    std::list<TodoItem>::iterator it;

    srand(static_cast<unsigned int>(time(NULL)));

    todoItems.clear();

    // TodoItem test;
    // test.create("this is a test");
    // todoItems.push_back(test);

    while (1)
    {
        system("cls");
        std::wcout << L"Todo List Maker - " << version << std::endl;
        std::cout << std::endl << std::endl;

        for (it = todoItems.begin(); it != todoItems.end(); it++)
        {
            std::wstring completed = it->isCompleted() ? L"done" : L"not done";

            std::wcout << static_cast<unsigned int>(it->getId()) << " | " << it->getDescription() << " | " << completed << std::endl;
        }


        if (todoItems.empty())
        {
            std::cout << "Add your first todo!" << std::endl;
        }

        std::cout << std::endl << std::endl;

        if (TodoItem::getUsedIdsSize() < numberOfIds) {
            std::cout << "[a]dd a new Todo" << std::endl;
        }
        else {
            std::cout << "  You have reached the maximum number of Todos ( " << numberOfIds << " )!\n   Clear some currently existing Todos to add more.\n" << std::endl;
        }

        std::cout << "[c]omplete a Todo" << std::endl;
        std::cout << "[r]emove an existing Todo" << std::endl;
        std::cout << "[q]uit" << std::endl;

        std::cout << "choice: ";
        std::cin >> input_option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (input_option == 'q')
        {
            std::cout << "Have a great day now!" << std::endl;
            break;
        }
        else if (input_option == 'c')
        {
            std::cout << "Enter id to mark completed: ";
            std::cin >> input_id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (it = todoItems.begin(); it != todoItems.end(); it++)
            {
                if (input_id == it->getId())
                {
                    it->setCompleted(true);
                    break;
                }
            }
        }
        else if (input_option == 'a' && TodoItem::getUsedIdsSize() < numberOfIds)
        {
            std::cout << "Add a new description: ";
            std::cin.clear();
            std::cin.ignore();
            getline(std::wcin, input_description);

            TodoItem newItem;
            newItem.create(input_description);
            todoItems.push_back(newItem);
        }
        else if (input_option == 'r')
        {
            std::cout << "Enter id to remove: ";
            std::cin >> input_id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for (it = todoItems.begin(); it != todoItems.end();)
            {
                if (input_id == it->getId())
                {
                    TodoItem::removeUsedId(input_id);  
                    it = todoItems.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

    }

    return 0;
}