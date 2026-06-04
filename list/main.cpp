#include <iostream>

#include "list.hpp"

int main() {
    DS::list<int> l;

    l.pushBack(1);
    l.pushBack(2);
    l.pushBack(3);
    std::cout << "after pushBack 1,2,3: ";
    l.print();

    l.pushFront(0);
    std::cout << "after pushFront 0:  ";
    l.print();

    l.pushBack(9, 3);
    std::cout << "after pushBack(9,3):";
    l.print();
    std::cout << "size: " << l.size() << "\n";

    l.popBack();
    l.popFront();
    std::cout << "after popBack/popFront: ";
    l.print();

    l.popBack(2);
    std::cout << "after popBack(2):   ";
    l.print();

    DS::list<int> copy = l;
    copy.pushBack(100);
    std::cout << "original: ";
    l.print();
    std::cout << "copy:     ";
    copy.print();

    DS::list<int> moved = std::move(copy);
    std::cout << "moved:    ";
    moved.print();
    std::cout << "moved-from empty? " << std::boolalpha << copy.empty() << "\n";

    DS::list<int> other;
    other.pushBack(7, 2);
    l.pushBack(other);
    std::cout << "after pushBack(list): ";
    l.print();

    return 0;
}
