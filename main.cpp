#include <iostream>
#include "list.h"

template <class T>
void PrintList(const List<T>& list)
{
    for (const auto& value : list) {
        std::cout << value << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    List<int> list = { 25, 22, 90 };

    list.PushFront(7);
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);

    list.InsertAfter(list.Find(90), 4);

    list.Erase(3);
    list.PushFront(40);
    list.Erase(90);

    PrintList(list);

    std::cout << list.PopFront().value() << std::endl;

    PrintList(list);

    List<int> list2 = list;

    std::cout << "List2 (copied): ";

    PrintList(list2);

    List<int> list3(std::move(list2));

    std::cout << "List3 (moved): ";

    PrintList(list3);
}