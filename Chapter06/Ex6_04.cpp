// Ex6_04.cpp
// Using partition_copy() to find values above average and below average

#include <algorithm> // For partition_copy(), copy()
#include <iostream>  // For standard streams
#include <iterator>  // For back_inserter, ostream_iterator
#include <numeric>   // For accumulate()
#include <vector>    // For vector container

int main()
{
  std::vector<double> temperatures{ 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
  std::vector<double> low_t;  // Stores below average temperatures
  std::vector<double> high_t; // Stores average or above temperatures

  auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0)
    / temperatures.size();
  std::cout << "Average temperature: " << average << std::endl;

  // Note that the code in main() uses back_insert_iterator objects that are created using
  // the back_inserter() helper function as the iterators for both destination containers
  // in the partition_copy() call. A back_insert_iterator calls push_back() to add a new
  // element to a container so using this approach avoids the necessity to know in advance
  // how many elements are to be stored. If you use a begin iterator for a destination
  // range, sufficient elements must already exist in the destination prior to the
  // operation to accommodate however many will be copied.
  std::partition_copy(std::begin(temperatures), std::end(temperatures),
                      std::back_inserter(low_t), std::back_inserter(high_t),
                      [average](double t) { return t < average; });

  // Output below average temperatures
  std::copy(std::begin(low_t), std::end(low_t),
            std::ostream_iterator<double>{ std::cout, " " });
  std::cout << std::endl;

  // Output average or above temperatures
  std::copy(std::begin(high_t), std::end(high_t),
            std::ostream_iterator<double>{ std::cout, " " });
  std::cout << std::endl;
}
