// Ex1_03.cpp
// Passing functions to an algorithm

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>

class Root {
public:
  double operator()(double x)
  {
    return std::sqrt(x);
  };
};

int main()
{
  double data[]{ 1.0, 2.0, 3.0, 4.0, 5.0 };

  std::cout << "Original data:\n";
  for (auto item : data)
    std::cout << item << " ";
  std::cout << std::endl;

  // Passing a function object
  Root root; // Function object
  std::cout << "\nSquare roots are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
                 std::ostream_iterator<double>(std::cout, " "), root);

  // Using an lambda expression as an argument
  std::cout << "\n\nCubes are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
                 std::ostream_iterator<double>(std::cout, " "),
                 [](double x) { return x * x * x; });

  // Using a variable of type std::function<> as argument
  std::function<double(double)> square{ [](double x) { return x * x * x; } };
  std::cout << "\n\nSquares are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
                 std::ostream_iterator<double>(std::cout, " "), square);

  // Using a lambda expression that calls another lambda expression as argument
  std::cout << "\n\n4th powers are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
                 std::ostream_iterator<double>(std::cout, " "),
                 [&square](double x) { return square(x) * square(x); });
  std::cout << std::endl;
}
