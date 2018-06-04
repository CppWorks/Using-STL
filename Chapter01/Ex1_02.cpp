// Ex1_02.cpp
// Using stream iterators

#include <iostream> // For standard streams
#include <iterator> // For istream_iterator
#include <numeric>  // For accumulate() - sums a range of elements

int main()
{
  std::cout << "Enter numeric values separated by spaces and enter Ctrl+D on a separate "
               "line to end:"
            << std::endl;

  //  By default, an istream_iterator object ignores whitespace; you can override this by
  //  applying the std::noskipws manipulator to the underlying input stream.

  // When you create an ostream_iterator object, you can optionally specify a delimiter
  // string that is to be written following the output of each object.

  std::cout << "\nThe sum of the values you entered is "
            << std::accumulate(std::istream_iterator<double>(std::cin),
                               //  The no-arg constructor for istream_iterator<T> creates
                               //  an end iterator object that will be matched when the
                               //  end of a stream is reached.
                               std::istream_iterator<double>(), 0.0)
            << std::endl;
}
