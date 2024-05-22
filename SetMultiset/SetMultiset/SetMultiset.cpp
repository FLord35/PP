#include <iostream>
#include <set>
#include <string>
#include <iterator>

void DoPush(std::set <int> &set)
{
    std::set <int>::iterator it;
    int temp;
    std::cin >> temp;

    set.insert(temp);
    
    std::cout << "Your current set is: ";
    copy(set.begin(), set.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

void DoDelete(std::set <int> &set)
{
    std::set <int>::iterator it;
    int temp;
    std::cin >> temp;

    set.erase(temp);
    
    std::cout << "Your current set is: ";
    copy(set.begin(), set.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main()
{
    std::set <int> iSet;
    std::string userCommand;

    std::cout << "Enter a command or type 'exit' to leave" << std::endl;
    std::cout << "List of commands:" << std::endl;
    std::cout << "1)'push <value>' to add an element to the set" << std::endl;
    std::cout << "2)'delete <value>' to delete an element from the set" << std::endl;

    while (true)
    {
        std::cin >> userCommand;
        if (userCommand == "exit")
            return 0;
        else if (userCommand == "push")
            DoPush(iSet);
        else if (userCommand == "delete")
            DoDelete(iSet);
        else std::cout << "Undefined command, try again" << std::endl;
    }
}
