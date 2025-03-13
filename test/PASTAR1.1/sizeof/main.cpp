#include <iostream>
#include "Coord.h"
#include "Node.h"

using namespace std;

int main(void)
{
    std::cout << "sizeof Node<3>: " << sizeof(Node<3>)
              << " sizeof Node<4>: " << sizeof(Node<4>)
              << " sizeof Node<5>: " << sizeof(Node<5>)
              << " sizeof Node<14>: " << sizeof(Node<14>)
              << std::endl;
    return 0;
}
