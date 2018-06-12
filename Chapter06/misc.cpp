#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>
#include <numeric>
#include <tuple>
#include <list>

int main() {
  {
    // Sorting a Range

    // Prerequisites for sort<Iter>() function template:
    // < operator
    // swappable; swap() function template
    // objects must implement a move constructor and a move assignment operator
    // Iter is a random access iterator
    // -> only array, vector, or deque containers are acceptable, or elements in a standard array
    // that's why list and forward_list have their own sort() member functions

    std::vector<int> numbers{ 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
    std::sort(std::begin(numbers), std::end(numbers));
    std::copy(std::begin(numbers), std::end(numbers),
              std::ostream_iterator<int>{ std::cout, " " });
    // Output: 11 22 33 44 66 77 88 99
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // sorting only a range:
    numbers = { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
    std::sort(++std::begin(numbers), --std::end(numbers));
    std::copy(std::begin(numbers), std::end(numbers),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // sorting into descending sequence:
    numbers = { 22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10 };
    std::sort(std::begin(numbers), std::end(numbers), std::greater<>());
    std::copy(std::begin(numbers), std::end(numbers),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // custom sorting function:
    // The result is the elements in descending sequence of their last letters.
    std::deque<std::string> words {"one", "two", "nine", "nine", "one", "three", "four", "five", "six"};
    std::sort(std::begin(words), std::end(words),
              [](const std::string& s1, const std::string& s2){ return s1.back() > s2.back(); });
    std::copy(std::begin(words), std::end(words),
              std::ostream_iterator<std::string> {std::cout, " "}); // six four two one nine nine one three five
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Sorting and the Order of Equal Elements

    // The stable_sort() algorithm provides what you need in this instance. It sorts the
    // elements in a range and ensures that equal elements remain in their original
    // sequence.

    // The difference is that with stable_sort() it is guaranteed that the order of equal
    // elements will not be changed, which is not the case with the sort() algorithm
  }

  {
    // Partial Sorting

    //  Suppose that you have a container in which you have collected a few million
    //  values, but you are only interested in the lowest 100 of these. You could sort the
    //  entire contents of the container and select the first 100, but this could be
    //  somewhat time consuming. What you need is a partial sort, where only the lowest n
    //  of a larger number of values in a range are placed in order. There’s a special
    //  algorithm for this, the partial_sort() algorithm, which expects three arguments
    //  that are random access iterators. If the function parameters are first, second,
    //  and last, the algorithm is applied to elements in the range [first,last). After
    //  executing the algorithm, the range [first,second) will contain the lowest
    //  second-first elements from the range [first,last) in ascending sequence.

    size_t count {5};
    std::vector<int> numbers {22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10};
    std::partial_sort(std::begin(numbers), std::begin(numbers) + count, std::end(numbers));
    std::copy(std::begin(numbers), std::end(numbers),
              std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // Note that the original order of the elements that are not sorted is not maintained.

    // Using a custom comparison function:
    numbers = {22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10};
    std::partial_sort(std::begin(numbers), std::begin(numbers) + count, std::end(numbers),
                      std::greater<>());
    std::copy(std::begin(numbers), std::end(numbers),
              std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // The partial_sort_copy() algorithm does essentially the same as partial_sort()
    // except that the sorted elements are copied to a different range – in another
    // container. The first two arguments are the iterators specifying the range to which
    // the partial sort is to be applied; the third and fourth arguments are the iterators
    // identifying the range where the result is to be stored. The number of elements in
    // the destination range determines the number of elements from the input range that
    // will be sorted.

    numbers = {22, 7, 93, 45, 19, 56, 88, 12, 8, 7, 15, 10};
    std::vector<int> result(count);
    // Destination for the results - count elements
    std::partial_sort_copy(std::begin(numbers), std::end(numbers),
                           std::begin(result),  std::end(result));
    std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl;
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // using a custom comparison function:
    std::partial_sort_copy(std::begin(numbers), std::end(numbers),
                           std::begin(result),  std::end(result), std::greater<>());
    std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl;
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // Executing nth_element() will result in the nth element being set to the element
    // that would be there if the range was fully sorted. All the elements that precede
    // the nth element in the range will be less than the nth element, and all the
    // elements that follow it will be greater.

    std::nth_element(std::begin(numbers), std::begin(numbers) + count, std::end(numbers));
    std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // nth-element is 15. Everything before is smaller than 15, everything after is bigger
    // than 15. But not necessarily in order. Only 15 is in the right spot assumed the
    // whole range would be sorted.

    // same with a custom  comparison function:
    std::nth_element(std::begin(numbers), std::begin(numbers) + count,
                     std::end(numbers), std::greater<>());
    std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // 19 is pivot point
  }

  {
    // Testing for Sorted Ranges

    // is_sorted()
    std::vector<int> numbers{ 22, 7, 93, 45, 19 };
    std::vector<double> data{ 1.5, 2.5, 3.5, 4.5 };
    std::cout << "numbers is "
              << (std::is_sorted(std::begin(numbers), std::end(numbers)) ? "" : "not ")
              << "in ascending sequence.\n";
    std::cout << "data is "
              << (std::is_sorted(std::begin(data), std::end(data)) ? "" : "not ")
              << "in ascending sequence." << std::endl;

    // using reverse direction and custom comparison function:
    std::cout << "data reversed is "
              << (std::is_sorted(std::rbegin(data), std::rend(data), std::greater<>()) ? "": "not ")
              << "in descending sequence." << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    // is_sorted_until()
    std::vector<std::string> pets{ "cat",   "chicken", "dog", "pig",
                                   "llama", "coati",   "goat" };
    std::cout << "The pets in ascending sequence are:\n";
    // This function returns an iterator that is the upper bound of elements from the
    // range that are in ascending sequence.
    std::copy(std::begin(pets), std::is_sorted_until(std::begin(pets), std::end(pets)),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // same with custom comparison function:
    pets = {"dog", "coati", "cat", "chicken", "pig", "llama", "goat"};
    std::cout << "The pets in descending sequence are:\n";
    std::copy(std::begin(pets),
              std::is_sorted_until(std::begin(pets), std::end(pets), std::greater<>()),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Merging Ranges

    // A merge operation combines elements from two ranges that are ordered in the same
    // sense. The result is a range containing copies of the elements from both input
    // ranges with the result ordered in the same way as the original ranges.

    // The merge() algorithm merges two ranges and stores the result in a third range. The
    // elements in the destination range in the example must already exist. No allocation
    // by the merge() algorithm. Except of course, if you specify the destination by an
    // insert iterator, elements will be created automatically. The merge() algorithm
    // returns an iterator that points to one past the last element in the merged range.

    std::vector<int> these{ 2, 15, 4, 11, 6, 7 };
    std::vector<int> those{ 5, 2, 3, 2, 14, 11, 6 };
    std::stable_sort(std::begin(these), std::end(these), std::greater<>());
    std::stable_sort(std::begin(those), std::end(those), std::greater<>());
    std::vector<int> result(these.size() + those.size());
    auto end_iter  = std::merge(std::begin(these), std::end(these),
                                std::begin(those), std::end(those),
                                std::begin(result), std::greater<>());
    std::copy(std::begin(result), end_iter, std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // The inplace_merge() algorithm merges two consecutive sorted sequences of elements
    // in the same range in place. At number 9 is the pivot point.
    std::vector<int> data{ 5, 17, 19, 20, 24, 30, 9, 13, 19, 25, 29, 31, 40, 41 };
    std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl;
    std::inplace_merge(std::begin(data), std::begin(data) + 6, std::end(data));
    std::copy(std::begin(data), std::end(data), std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Searching a Range

    // find(), find_if(), find_if_not(). Each algorithm returns an iterator that points to
    // the object that was found, or the end iterator of the range if the object was not
    // found.

    std::vector<int> numbers{ 5, 46, -5, -6, 23, 17, 5, 9, 6, 5 };
    int value{ 23 };
    auto iter = std::find(std::begin(numbers), std::end(numbers), value);
    if (iter != std::end(numbers))
      std::cout << value << " was found.\n";
    std::cout << std::string(50, '-') << std::endl;

    // using find() repeatedly:
    size_t count{};
    int five{ 5 };
    auto start_iter = std::begin(numbers);
    auto end_iter = std::end(numbers);
    while ((start_iter = std::find(start_iter, end_iter, five)) != end_iter) {
      ++count;
      ++start_iter;
    }
    std::cout << five << " was found " << count << " times." << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    // 3 times

    // find the first element in numbers that is greater than value:
    auto iter1 = std::find_if(std::begin(numbers), std::end(numbers),
                              [value](int n) { return n > value; });
    if (iter1 != std::end(numbers))
      std::cout << *iter1 << " was found greater than " << value << ".\n";
    std::cout << std::string(50, '-') << std::endl;

    // Using find_if_not() algorithm to find elements for which a predicate is false:
    start_iter = std::begin(numbers);
    end_iter = std::end(numbers);
    while ((start_iter
            = std::find_if_not(start_iter, end_iter, [five](int n) { return n > five; }))
           != end_iter) {
      ++count;
      ++start_iter;
    }
    std::cout << count << " elements were found that are not greater than " << five
              << std::endl;
    std::cout << std::string(50, '-') << std::endl;
  }

  {
    // Finding any of a Range of Elements in a Range

    // find_first_of() algorithm searches a range for the first occurrence of any element
    // from a second range. This code searches text for the first occurrence of any of the
    // characters in vowels:
    std::string text{ "The world of searching" };
    std::string vowels{ "aeiou" };
    auto iter = std::find_first_of(std::begin(text), std::end(text), std::begin(vowels),
                                   std::end(vowels));
    if (iter != std::end(text))
      std::cout << "We found '" << *iter << "'." << std::endl; // We found 'e'.
    std::cout << std::string(50, '-') << std::endl;

    // find all occurrences in text of any character from vowels:
    std::string found{}; // Records characters that are found
    for (auto iter = std::begin(text);
         (iter = std::find_first_of(iter, std::end(text), std::begin(vowels), std::end(vowels))) != std::end(text)
           ;)
      found += *(iter++);
    std::cout << "The characters \"" << found << "\" were found in text." << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    {
      // find_first_of() with custom comparison function:
      std::vector<long> numbers{ 64L, 46L, -65L, -128L, 121L, 17L, 35L, 9L, 91L, 5L };
      int factors[]{ 7, 11, 13 };
      auto iter = std::find_first_of(
        std::begin(numbers), std::end(numbers),     // The range to be searched
        std::begin(factors), std::end(factors),     // Elements sought
        [](long v, long d) { return v % d == 0; }); // Predicate - true for a match
      if (iter != std::end(numbers))
        std::cout << *iter << " was found." << std::endl; // -65 ( -65 / 13 = 5 )
      std::cout << std::string(50, '-') << std::endl;
    }

    {
      // the same but collecting all the numbers:
      std::vector<long> numbers{ 64L, 46L, -65L, -128L, 121L, 17L, 35L, 9L, 91L, 5L };
      int factors[]{ 7, 11, 13 };
      std::vector<long> results; // Stores elements found
      auto iter = std::begin(numbers);
      while ((iter = std::find_first_of(
                iter, std::end(numbers),                    // Range searched
                std::begin(factors), std::end(factors),     // Elements sought
                [](long v, long d) { return v % d == 0; })) // Predicate
             != std::end(numbers))
        results.push_back(*iter++);
      std::cout << results.size() << " values were found:\n";
      std::copy(std::begin(results), std::end(results),
                std::ostream_iterator<long>{ std::cout, " " });
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }
  }

  {
    // Finding Multiple Elements from a Range

    // The adjacent_find() algorithm searches for two successive elements in a range that
    // are identical. An iterator that points to the first of the first two equal elements
    // is returned.
    std::string saying{ "Children should be seen and not heard." };
    auto iter = std::adjacent_find(std::begin(saying), std::end(saying));
    if (iter != std::end(saying))
      std::cout << "In the following text:\n\"" << saying << "\"\n'" << *iter
                << "' is repeated starting at index position "
                << std::distance(std::begin(saying), iter) << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    // adjacent_find() with a custom predicate:
    std::vector<long> numbers{ 64L, 46L, -65L, -128L, 121L, 17L, 35L, 9L, 91L, 5L };
    auto iter1 = std::adjacent_find(std::begin(numbers), std::end(numbers),
                                   [](long n1, long n2) { return n1 % 2 && n2 % 2; });
    if (iter1 != std::end(numbers))
      std::cout << "The first pair of odd numbers is " << *iter1 << " and " << *(iter1 + 1);
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // The find_end() algorithm finds the last occurrence in a range of a second range of
    // elements. You can visualize this as finding the last occurrence of a subsequence in
    // a sequence of elements of any type.
    std::string text{ "Smith, where Jones had had \"had\", had had \"had had\"."
                 " \"Had had\" had had the examiners\' approval." };
    std::cout << text << std::endl;
    std::string phrase{ "had had" };
    auto iter2 = std::find_end(std::begin(text), std::end(text),
                               std::begin(phrase), std::end(phrase));
    if (iter2 != std::end(text))
      std::cout << "The last \"" << phrase << "\" was found at index "
                << std::distance(std::begin(text), iter2);
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // searching for all occurrences of phrase in text
    size_t count{};
    iter2 = std::end(text);
    auto end_iter = iter2;
    while ((iter2 = std::find_end(std::begin(text), end_iter,
                                  std::begin(phrase), std::end(phrase)))
           != end_iter) {
      ++count;
      end_iter = iter2;
    }
    std::cout << "\"" << phrase << "\" was found " << count << " times.";
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // find_end() with a binary predicate:
    count = {};
    iter2 = std::end(text);
    end_iter = iter2;
    while ((iter2 = std::find_end(
              std::begin(text), end_iter, std::begin(phrase), std::end(phrase),
              // binary predicate as a fifth argument that is used to compare elements:
              [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }))
           != end_iter) {
      ++count;
      end_iter = iter2;
    }
    std::cout << "\"" << phrase << "\" was found " << count << " times.";
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // The search() algorithm is similar to find_end() in that it finds a subsequence in a
    // sequence, but it finds the first occurrence rather than the last.

    std::string text {"Smith, where Jones had had \"had\", had had \"had had\"."
        " \"Had had\" had had the examiners\' approval."};
    std::cout << text << std::endl;
    std::string phrase {"had had"};
    size_t count {};
    auto iter = std::begin(text);
    auto end_iter = end(text);
    while((iter = std::search(iter, end_iter, std::begin(phrase), std::end(phrase),
                              [](char ch1, char ch2){ return std::toupper(ch1) == std::toupper(ch2); })) != end_iter)
      {
        ++count;
        // Move to beyond end of subsequence found:
        std::advance(iter, phrase.size());
      }
    std::cout << "\"" << phrase << "\" was found " << count << " times.";
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // The search_n() algorithm searches a range for a given number of successive
    // occurrences of an element.
    std::vector<double> values{ 2.7, 2.7, 2.7, 3.14, 3.14, 3.14, 2.7, 2.7 };
    double value{ 3.14 };
    int times{ 3 };
    auto iter = std::search_n(std::begin(values), std::end(values), times, value);
    if (iter != std::end(values))
      std::cout << times << " successive instances of " << value
                << " found starting index " << std::distance(std::begin(values), iter);
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Partitioning a Range with partition()

    // Partitioning the elements in a range rearranges the elements such that all the
    // elements for which a given predicate returns true precede all the elements for
    // which the predicate returns false. partition() returns iterator pointing to pivot
    // point (= first false).

    //  Using the partition() algorithm to rearrange a sequence of values so that all
    //  those less than the average precede all those greater than the average:
    std::vector<double> temperatures {65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50};
    std::copy(std::begin(temperatures), std::end(temperatures),
              std::ostream_iterator<double>{std::cout, " "});
    std::cout << std::endl;

    auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0)
      / temperatures.size();
    std::cout << "Average temperature: " << average << std::endl;

    // returns iterator pointing to pivot point (= first false)
    auto firstFalse = std::partition(std::begin(temperatures),
                                     std::end(temperatures),
                                     [average](double t) { return t < average; });
    std::cout << *firstFalse << std::endl;
    std::copy(std::begin(temperatures),
              std::end(temperatures),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // The elements 44 and 41 follow 40 in the original range but after the operation that
    // is no longer the case. To maintain the relative order of elements, you use the
    // stable_partition() algorithm.
    temperatures = {65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50};
    firstFalse = std::stable_partition(std::begin(temperatures),
                                       std::end(temperatures),
                                       [average](double t) { return t < average; });
    std::cout << "Average temperature: " << average << std::endl;
    std::cout << *firstFalse << std::endl;
    std::copy(std::begin(temperatures),
              std::end(temperatures),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // You use the partition_point() algorithm to obtain the end iterator for the first
    // partition in a partitioned range. The first two arguments are forward iterators
    // defining the range to be examined, and the last argument is the predicate that was
    // used to partition the range. You will not typically know how many elements there
    // are in each partition so this algorithm enables you to extract or access the
    // elements in either partition. Corresponds to return value of stable_partition():
    std::vector<double> temperatures{ 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
    auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0)
      / temperatures.size();
    std::cout << "Average temperatures: " << average << std::endl;
    auto predicate = [average](double t) { return t < average; };
    std::stable_partition(std::begin(temperatures), std::end(temperatures), predicate);
    auto iter
      = std::partition_point(std::begin(temperatures), std::end(temperatures), predicate);
    std::cout << "Elements in the first partition: ";
    std::copy(std::begin(temperatures), iter,
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << "\nElements in the second partition: ";
    std::copy(iter, std::end(temperatures),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // partition by gender:
    using gender = char;
    using first = std::string;
    using second = std::string;
    using Name = std::tuple<first, second, gender>;
    std::vector<Name> names{ std::make_tuple("Dan", "Old", 'm'),
                             std::make_tuple("Ann", "Old", 'f'),
                             std::make_tuple("Ed", "Old", 'm'),
                             std::make_tuple("Jan", "Old", 'f'),
                             std::make_tuple("Edna", "Old", 'f') };
    std::partition(std::begin(names), std::end(names),
                   // Partition names by gender
                   [](const Name& name) { return std::get<gender>(name) == 'f'; });
    for (const auto& name : names)
      std::cout << std::get<0>(name) << " " << std::get<1>(name) << std::endl;
    std::cout << std::string(50, '-') << std::endl;
  }

  {
    // The partition_copy() Algorithm

    // The partition_copy() algorithm partitions a range in the same way as
    // stable_partition(), but the elements for which the predicate return true are copied
    // to a separate range, and elements for which the predicate returns false are copied
    // to the third range. The operation leaves the original range unchanged.

    // The source range is identified by the first two arguments. The beginning of the
    // destination range for elements for which the predicate returns true is identified
    // by the third argument, and the beginning of the destination for elements for which
    // the predicate is false is the fourth argument. The fifth argument is the predicate
    // that is to be used for partitioning the elements.
  }

  {
    // Verify that the temperatures range is partitioned:
    std::vector<double> temperatures{ 65, 75, 56, 48, 31, 28, 32, 29, 40, 41, 44, 50 };
    auto average = std::accumulate(std::begin(temperatures), std::end(temperatures), 0.0)
      / temperatures.size();
    std::cout << "Average temperatures: " << average << std::endl;
    auto predicate = [average](double t) { return t < average; };
    // std::stable_partition(std::begin(temperatures), std::end(temperatures), predicate);
    if (std::is_partitioned(std::begin(temperatures), std::end(temperatures),
                            predicate)) {
      std::cout << "Range is partitioned." << std::endl;
      auto iter = std::partition_point(std::begin(temperatures), std::end(temperatures),
                                       [average](double t) { return t < average; });
      std::cout << "Elements in the first partition: ";
      std::copy(std::begin(temperatures), iter,
                std::ostream_iterator<double>{ std::cout, " " });
      std::cout << "\nElements in the second partition: ";
      std::copy(iter, std::end(temperatures),
                std::ostream_iterator<double>{ std::cout, " " });
      std::cout << std::endl;
    } else
      std::cout << "Range is not partitioned." << std::endl;
    std::cout << std::string(50, '-') << std::endl;
  }

  {
    // Binary Search Algorithms

    // The binary search algorithms are typically faster than a sequential search, but
    // require that the elements in the range to which they are applied are sorted.

    // The binary_search() algorithm returns a bool value that is true if the third
    // argument is found, or false otherwise, so it just tells you whether or not the
    // element is present, but not where it is when it is. Of course, if you must know
    // where it is, you can use one of the find algorithms you have already seen, or
    // lower_bound(), upper_bound() or equal_range().
    std::list<int> values{ 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
    values.sort();
    int wanted{ 22 };
    if (std::binary_search(std::begin(values), std::end(values), wanted))
      std::cout << wanted << " is definitely in there - somewhere..." << std::endl;
    else
      std::cout << wanted << " cannot be found - maybe you got it wrong..." << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    {
      // binary_search() with predicate, must be used in sorting and searching:
      std::list<int> values{ 17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43 };
      auto predicate = [](int a, int b) { return a > b; };
      values.sort(predicate); // Sort into descending sequence
      int wanted{ 22 };
      if (std::binary_search(std::begin(values), std::end(values), wanted, predicate))
        std::cout << wanted << " is definitely in there - somewhere...";
      else
        std::cout << wanted << " cannot be found - maybe you got it wrong...";
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }

    {
      // The lower_bound() algorithm finds the element in the range specified by the first
      // two arguments that is not less than the third argument – in other words, the
      // first element that is GREATER THAN OR EQUAL to the third argument.

      //  The upper_bound() algorithm finds the first element in the range defined by its
      //  first two arguments that is GREATER THAN the third argument.
      std::list<int> values {17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43};
      values.sort();
      std::copy(std::begin(values), std::end(values), std::ostream_iterator<int>{ std::cout, " " });
      std::cout << std::endl;
      int wanted{ 36 };
      std::cout << "The lower bound for " << wanted << " is "
                << *std::lower_bound(std::begin(values), std::end(values), wanted)
                << std::endl;
      std::cout << "The upper bound for " << wanted << " is " << *std::upper_bound(std::begin(values), std::end(values), wanted)
                << std::endl;
      std::cout << std::string(50, '-') << std::endl;
    }

    {
      // The equal_range() algorithm finds all elements in a sorted range that are
      // equivalent to a given element. The algorithm returns a pair object with members
      // that are forward iterators, the first of which points to the element that is not
      // less than the third argument and the second points to the element that is greater
      // than the third argument. Thus you get the result of calling lower_bound() and
      // upper_bound() in a single call.
      std::list<int> values {17, 11, 40, 36, 22, 54, 48, 70, 61, 82, 78, 89, 99, 92, 43};
      values.sort();
      int wanted{ 36 };
      auto pr = std::equal_range(std::begin(values), std::end(values), wanted);
      std::cout << "the lower bound for " << wanted << " is " << *pr.first << std::endl;
      std::cout << "the upper bound for " << wanted << " is " << *pr.second << std::endl;
      std::cout << std::string(50, '-') << std::endl;
    }

    {
      // All the binary search algorithms will also work with ranges that are partitioned
      // in a particular way. For a given wanted value, the elements in the range must be
      // partitioned with respect to (element < wanted), and partitioned with respect to
      // !(wanted < element).
      std::list<int> values{ 17, 11, 40, 13, 22, 54, 48, 70, 22,
                             61, 82, 78, 22, 89, 99, 92, 43 };
      std::copy(std::begin(values), std::end(values),
                std::ostream_iterator<int>{ std::cout, " " });
      std::cout << std::endl;
      int wanted{ 22 };
      // The first partition operation ensures that all elements that are strictly less
      // than wanted are in the left partition; these elements are not necessarily in
      // order. This operation also ensures that all elements that are not less than
      // wanted – so elements that are greater than or equal to wanted – are in the right
      // partition, so they follow it in sequence, and are also not necessarily in order.
      // All occurrences of wanted will be in the right partition, but mixed up with the
      // elements that are greater than wanted:
      std::partition(std::begin(values), std::end(values),
                     // Partition the values wrt value < wanted
                     [wanted](double value) { return value < wanted; });
      std::copy(std::begin(values), std::end(values),
                std::ostream_iterator<int>{ std::cout, " " });
      std::cout << std::endl;
      // The second partition operation is applied to the result of the first. The
      // expression !(wanted < value) is equivalent to (value <= wanted). Thus all
      // elements that are less than or equal to wanted will be in the left partition as a
      // result of this, and all elements strictly greater than wanted will be in the
      // right partition. The effect of this is to move all instances of wanted into the
      // left partition so they are together as a sequence as the last elements in the
      // left partition:
      std::partition(std::begin(values),
                     std::end(values),
                     // Partition the values wrt !(wanted < value)
                     [wanted](double value) { return (value <= wanted); });
      std::copy(std::begin(values), std::end(values),
                std::ostream_iterator<int>{ std::cout, " " });
      std::cout << std::endl;
      auto pr = std::equal_range(std::begin(values), std::end(values), wanted);
      std::cout << "the lower bound for " << wanted << " is " << *pr.first << std::endl;
      std::cout << "the upper bound for " << wanted << " is " << *pr.second << std::endl;
    }
  }
  return 0;
}
