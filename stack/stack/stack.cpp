#include <iostream>
#include <stack>

int main()
{
    int temp;
    std::stack <int> iStack;

    std::cout << "Type 3 integer values to add to a stack" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cin >> temp;
        iStack.push(temp);
    }
    
    std::cout << "Top element of your stack is: " << iStack.top() << std::endl;

    iStack.pop();

    std::cout << "Now we have deleted the previous top element so the new one will be: " << iStack.top() << std::endl;

    return 0;
}

