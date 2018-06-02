// Ex8_01.cpp
// Generating a succession of 8 seeds

#include <iostream> // For standard streams
#include <random>   // For random_device class

int main()
{
  std::random_device rd; // A function object for generating seeds
  for (size_t n{}; n < 8; ++n)
    std::cout << rd() << " ";
  std::cout << std::endl;
}