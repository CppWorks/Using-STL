// Ex1_01.cpp
// Using iterators

#include <iostream>
#include <numeric>

int main()
{
  double data[]{ 2.5, 4.5, 6.5, 5.5, 8.5 };

  std::cout << "The array contains:\n";

  for (auto iter = std::begin(data); iter != std::end(data); ++iter)
    std::cout << *iter << " ";
  std::cout << std::endl;

  for(auto& item : data)
    std::cout << item << " ";
  std::cout << std::endl;

  auto total = std::accumulate(std::begin(data), std::end(data), 0.0);
  std::cout << "\nThe sum of the array elements is " << total << std::endl;
}
