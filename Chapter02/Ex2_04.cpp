// Ex2_04.cpp
// Using a deque container

#include <deque>
#include <iostream>
#include <iterator>

using std::string;

int main()
{
  std::deque<string> names;

  std::cout
    << "Enter first names separated by spaces. Enter Ctrl+D on a separate line to end:\n";

  std::copy(std::istream_iterator<string>{ std::cin }, std::istream_iterator<string>{},
            std::front_inserter(names));

  std::cout << "\nIn reverse order, the names you entered are:\n";

  std::copy(std::begin(names), std::end(names),
            std::ostream_iterator<string>{ std::cout, " " });

  std::cout << std::endl;
}
