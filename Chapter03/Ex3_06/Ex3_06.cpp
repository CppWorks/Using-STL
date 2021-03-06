// Ex3_06.cpp
// Storing derived class objects in a container of base pointers

#include "Box.h"
#include "Carton.h"
#include <iostream> // For standard streams
#include <memory>   // For smart pointers
#include <vector>   // For the vector container

using std::make_unique;
using std::unique_ptr;

int main()
{
  std::vector<unique_ptr<Box>> boxes;
  boxes.push_back(make_unique<Box>(1, 2, 3));
  boxes.push_back(make_unique<Carton>(1, 2, 3));
  boxes.push_back(make_unique<Carton>(4, 5, 6));
  boxes.push_back(make_unique<Box>(4, 5, 6));
  for (auto&& ptr : boxes)
    std::cout << *ptr << " volume is " << ptr->volume() << std::endl;
}
