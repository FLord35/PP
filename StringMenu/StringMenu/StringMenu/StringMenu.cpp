#include <iostream>

void UseFrontAndBack()
{
    std::string userString;

    std::cout << "Введите строку для использования на ней методов front и back" << std::endl;
    std::cin >> userString;

    std::cout << "front = " << userString.front() << std::endl;
    std::cout << "back = " << userString.back() << std::endl;
}

std::string RedactStringInsert(std::string userString)
{
    int num;
    std::string newString;

    std::cout << "Введите позицию, начиная с которой вы бы хотели добавить строку" << std::endl;
    std::cin >> num;
    std::cout << "Теперь введите добавляемую строку" << std::endl;
    std::cin >> newString;

    std::cout << "Отредактированная строка: " << userString.insert(num, newString) << std::endl;
    return userString.insert(num, newString);
}

std::string RedactStringErase(std::string userString)
{
    int pos;
    int quant;

    std::cout << "Введите позицию, начиная с которой вы бы хотели удалить строку" << std::endl;
    std::cin >> pos;
    std::cout << "Теперь введите количество символов, которые нужно удалить" << std::endl;
    std::cin >> quant;

    std::cout << "Отредактированная строка: " << userString.erase(pos, quant) << std::endl;
    return userString.erase(pos, quant);
}

std::string RedactStringReplace(std::string userString)
{
    int pos;
    int quant;
    std::string newString;

    std::cout << "Введите позицию, начиная с которой вы бы хотели заменить строку" << std::endl;
    std::cin >> pos;
    std::cout << "Теперь введите количество символов, которые нужно заменить" << std::endl;
    std::cin >> quant;
    std::cout << "Далее введите строку, на которую будет заменена часть существующей строки" << std::endl;
    std::cin >> newString;

    std::cout << "Отредактированная строка: " << userString.replace(pos, quant, newString) << std::endl;
    return userString.replace(pos, quant, newString);
}

void RedactStringFind(std::string userString)
{
    std::string newString;

    std::cout << "Введите подстроку, на наличие которой в существующей строке будет произведён поиск" << std::endl;
    std::cin >> newString;

    switch (userString.find(newString))
    {
        case -1:
            std::cout << "Строка не была найдена" << std::endl;
            break;
        default:
            std::cout << "Индекс вхождения строки = " << userString.find(newString) << std::endl;
    }
}

void RedactString()
{
    std::string userString;
    std::string userCommand;
    bool toMenu = false;

    std::cout << "Введите строку для дальнейшего использования" << std::endl;
    std::cin >> userString;

    while (toMenu != true)
    {
        std::cout << std::endl;

        std::cout << "Выберите способ редактирования строки:" << std::endl;
        std::cout << "Для добавления символов в любую часть строки введите 'insert'" << std::endl;
        std::cout << "Для удаления части строки введите 'erase'" << std::endl;
        std::cout << "Для замены части строки введите 'replace'" << std::endl;
        std::cout << "Для проверки вхождения подстроки введите 'find'" << std::endl;
        std::cout << "Для выхода в главное меню введите 'menu'" << std::endl;

        std::cin >> userCommand;

        if (userCommand == "insert")
            userString = RedactStringInsert(userString);

        else if (userCommand == "erase")
            userString = RedactStringErase(userString);

        else if (userCommand == "replace")
            userString = RedactStringReplace(userString);

        else if (userCommand == "find")
            RedactStringFind(userString);

        else if (userCommand == "menu")
            toMenu = true;

        else std::cout << "Неизвестная команда для редактирования" << std::endl;
    }
}

void CompareStrings()
{
    std::string userStringFirst;
    std::string userStringSecond;

    std::cout << "Введите две строки для их сравнения с помощью метода compare" << std::endl;
    std::cin >> userStringFirst;
    std::cin >> userStringSecond;

    switch (userStringFirst.compare(userStringSecond))
    {
        case 1:
            std::cout << "Первая строка лексикографически больше второй";
            break;
        case -1:
            std::cout << "Вторая строка лексикографически больше первой";
            break;
        case 0:
            std::cout << "Строки равны лексикографически";
            break;
    }
    std::cout << std::endl;
}

int main()
{
    setlocale(0, "Rus");
    std::locale::global(std::locale("Russian_Russia"));

    std::string userCommand = "null";

    while (true)
    {
        std::cout << std::endl;

        std::cout << "Выберите задание:" << std::endl;
        std::cout << "1)Использование front и back" << std::endl;
        std::cout << "2)Редактирование строки" << std::endl;
        std::cout << "3)Сравнение строк с помощью compare" << std::endl;
        std::cout << "Для выбора команды введите её номер. Для выхода введите 'exit'" << std::endl;

        std::cin >> userCommand;

        if (userCommand == "exit")
            return 0;

        switch (userCommand.front())
        {
            case '1':
                UseFrontAndBack();
                break;
            case '2':
                RedactString();
                break;
            case '3':
                CompareStrings();
                break;
            default: std::cout << "Неизвестная команда. Введите номер команды от 1 до 3 или 'exit'" << std::endl;
        }
    }

    return 0;
}

