#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <set> // to ensure IDs don't duplicate.
#include <limits> // so can clear the input buffer to avoid bugs.



/*
Updates & Rationale:
- ID data type transitioned from "int" to "unsigned char" to achieve an extended ID range with memory efficiency.
- Introduced `std::set` for tracking and ensuring ID uniqueness.
- Integrated the constant `numberOfIds` for controlled testing purposes.
- Transitioned from `string` to `wstring` for enhanced MBCS support.
- Provided functionality to remove Todos when IDs become scarce.
- Implemented input buffer clearing to prevent potential input disruptions.
- Enhanced error handling in 'mark completed' and 'remove' functions to gracefully manage non-numeric (letter) inputs for IDs.
*/



// Commented out "using namespace std" to prevent potential namespace pollution and ambiguities.
//using namespace std;




//numberOfids should be equal to 255 to utilize the whole space available in 1 byte.
const unsigned char numberOfIds{ 255 }; // Implemented for debugging and testing purposes.




/*
 * Note: IDs are generated randomly as per the original design.
 * Optimization: Transitioned from 'int' to 'unsigned char' for ID storage, saving memory as the larger int type wasn't necessary.
 * Additionally, an efficient system has been implemented to ensure ID uniqueness, preserving unpredictability while avoiding duplication.
 * Precautionary steps have been taken for rudimentary error handling, such as input buffer clearing and conditions to prevent exceeding todo limits.
 */


class TodoItem
{
private:
    static std::set<unsigned char> usedIds;
    unsigned char id{};
    std::wstring description;
    bool completed;
public:

    TodoItem() : id(0), description(L""), completed(false) {}
    ~TodoItem() = default;

    bool create(std::wstring new_description)
    {
        unsigned char newId;
        do {
            newId = static_cast<unsigned char>(rand() % numberOfIds + 1);
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
    std::wstring version = L"v0.3.0";
    std::list<TodoItem> todoItems;
    std::list<TodoItem>::iterator it;

    srand(static_cast<unsigned int>(time(NULL)));

    todoItems.clear();

    // TodoItem test;
    // test.create("this is a test");
    // todoItems.push_back(test);

    while (1)
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
                std::cout << "You have reached the maximum number of Todos ( " << numberOfIds << " )!\n   Clear some currently existing Todos to add more.\n" << std::endl;
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
            else if (input_option == 'c' || input_option == 'r') // Unified error handling for ID inputs
            {
                std::cout << (input_option == 'c' ? "Enter id to mark completed: " : "Enter id to remove: ");
                std::wcin >> input_id;

                if (std::wcin.fail())  // If the user didn't enter a valid number
                {
                    std::wcin.clear(); // Reset the input failure
                    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    std::cout << "Invalid ID. Please enter a valid number." << std::endl;
                    continue; // Go back to the top of the while loop
                }

                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (input_option == 'c')
                {
                    for (it = todoItems.begin(); it != todoItems.end(); it++)
                    {
                        if (input_id == it->getId())
                        {
                            it->setCompleted(true);
                            break;
                        }
                    }
                }
                else
                {
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
            else if (input_option == 'a' && TodoItem::getUsedIdsSize() < numberOfIds)
            {
                std::cout << "Add a new description (max 200 characters): ";
                std::wcin.clear();
                getline(std::wcin, input_description);

                if (input_description.length() > 200) // Sanitize input
                {
                    std::wcout << L"Description is too long. Please limit to 200 characters." << std::endl;
                    continue; // Go back to the top of the while loop
                }

                TodoItem newItem;
                newItem.create(input_description);
                todoItems.push_back(newItem);
            }
        }

    return 0;
}
