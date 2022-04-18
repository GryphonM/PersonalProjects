#include <iostream>
#include "PhoneBook.h"

void Test1_LoadAndOutput(void)
{
    PhoneBook book("PhoneBook.txt");
    std::cout << book;
}

void Test2_LoadAndSave(void)
{
    PhoneBook book("PhoneBook.txt");
    book.AddEntry("Ashton", "Dub", "ash.dub@digipen.edu", 541, 823756);
    book.Save("PhoneBook_test2.txt");

    PhoneBook new_book("PhoneBook_test2.txt");
    std::cout << new_book;
}

void Test3_Sort(void)
{
    PhoneBook book("PhoneBook(Empty).txt");
    
    book.AddEntry("John", "Doe", "JDoe@hotmail.com", 206, 8793739);
    book.AddEntry("Eric", "Milov", "Eric@gmail.com", 425, 1234567);
    book.AddEntry("Christine", "Ericson", "ChrisE@hotmail.com", 206, 1534269);
    book.AddEntry("Will", "Johnson", "Will.J@arena.com", 215, 3935836);
    book.AddEntry("Ashton", "Dub", "ash.dub@digipen.edu", 541, 823756);

    book.SortByName();
    book.Save("PhoneBook_test3.txt");

    PhoneBook new_book("PhoneBook_test3.txt");
    std::cout << new_book;
}

void Test4_RemoveEntries(void)
{
    PhoneBook book("PhoneBook.txt");

    book.AddEntry("Jonathan", "Doe", "JDoe@hotmail.com", 206, 8793739);
    book.AddEntry("Eric", "Milov", "Eric@gmail.com", 425, 1234567);
    book.AddEntry("Ashton", "Dub", "ash.dub@digipen.edu", 541, 823756);

    std::cout << "Display book before removing elements containing 'on':";
    std::cout << std::endl;
    std::cout << "=======================================================";
    std::cout << std::endl << std::endl;

    std::cout << book;
    std::cout << std::endl;

    book.RemoveEntriesByName("on");

    std::cout << "Display book after removing elements containing 'on':";
    std::cout << std::endl;
    std::cout << "======================================================";
    std::cout << std::endl << std::endl;
    std::cout << book;
}

void Test5_TestConstructors_Assignment(void)
{
    PhoneBook book("PhoneBook.txt");
    std::cout << "Display book" << std::endl;
    std::cout << "=============" << std::endl;
    std::cout << book << std::endl;

    PhoneBook book2(book);
    std::cout << "Display book2" << std::endl;
    std::cout << "==============" << std::endl;
    std::cout << book2 << std::endl;

    PhoneBook book3 = book2;
    std::cout << "Display book3" << std::endl;
    std::cout << "==============" << std::endl;
    std::cout << book3 << std::endl;

    book.AddEntry("Ashton", "Dub", "ash.dub@digipen.edu", 541, 823756);
    book3 = book;

    std::cout << "Display book3 after assignment" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << book3 << std::endl;

}

int main(void)
{
    //Test1_LoadAndOutput();
    //Test2_LoadAndSave();
    //Test3_Sort();
    //Test4_RemoveEntries();
    Test5_TestConstructors_Assignment();

    //system("pause");
    return 0;
}