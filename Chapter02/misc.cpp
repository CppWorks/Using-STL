#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <deque>
#include <vector>
#include <list>
#include <iomanip>
#include <forward_list>

template <typename T, int N>
void printArray(const std::array<T, N>& array)
{
  for (auto item : array)
    std::cout << item << " ";
  std::cout << "\n";
}

template<typename T>
void printVector(const std::vector<T> & vector) {
  for (auto item : vector)
    std::cout << item << " ";
  std::cout << "\n";
}

template<typename C, typename T>
void printContainer(const C & container){
  std::copy(std::begin(container), std::end(container),
            std::ostream_iterator<T>(std::cout, " "));
  std::cout << std::endl;
}

int main() {

  // array<T, N> - N elements of type T (fixed), access random elements

  {
    // elements not initialized
    std::array<double, 100> data1;
    printArray<double, 100>(data1);

    // elements initialized to 0.0
    std::array<double, 100> data2 {};
    printArray<double, 100>(data2);

    // 5th and subsequent elements are 0.0
    std::array<double, 10> values {0.5, 1.0, 1.5, 2.0};
    printArray<double, 10>(values); // 0.5 1 1.5 2 0 0 0 0 0 0

    values.fill(M_PI);
    printArray<double, 10>(values); // 3.14159 3.14159 3.14159 3.14159 3.14159
                                    // 3.14159 3.14159 3.14159 3.14159 3.14159

    // no bounds checking
    values[4] = values[3] + 2.0 * values[1];
    // with bounds checking
    values.at(4) = values.at(3) + 2.0 * values.at(1);

    try {
      values.at(100) = M_PI;
    } catch (const std::out_of_range& e) {
      std::cerr << "Index out of range: " << e.what() << std::endl;
    } catch (...) {
      std::cerr << "Something happened. Don't know what.\n";
    }

    double total{};
    for (size_t i{}; i < values.size(); ++i) {
      total += values[i];
    }
    std::cout << "\nTotal: " << total << "\n\n";

    // It’s hard to visualize how an array container would have no elements because the
    // number of elements is fixed when you create it and cannot be changed. The only way
    // to create an empty array container instance is to specify the argument for the
    // second template parameter as zero – an unlikely occurrence.

    if (values.empty())
      std::cout << "The container has no elements.\n";
    else
      std::cout << "The container has " << values.size() << " elements.\n";

    total = 0.0;
    for(auto&& value : values)
      total += value;
    std::cout << "\nTotal: " << total << "\n\n";

    // The front() and back() function members of an array container return references to
    // the first and last elements respectively. There is also the data() function member
    // that returns &front(), which is the address of the underlying standard array that
    // stores the elements. You are unlikely to need this facility often.

    auto front = values.front();
    auto back = values.back();
    auto data = values.data();

    // There is a function template for a get<n>() helper function to access the nth
    // element from an array container; the argument for the template parameter must be a
    // constant expression that can be evaluated at compile time

    std::array<std::string, 5> words{ "one", "two", "three", "four", "five" };
    std::cout << std::get<3>(words) << std::endl; // Output words[3] -> "four"
    // std::cout << std::get<6>(words) << std::endl; // Compiler error message!

    // iterators
    total = 0.0;
    auto first = values.begin();
    auto last = values.end();
    while (first != last) {
      *first++ = total++;
    }
    printArray<double, 10>(values);

    // better to use global functions
    total = 0.0;
    auto first1 = std::begin(values);
    auto last1 = std::end(values);
    while (first1 != last1) {
      *first1++ = total++;
    }
    printArray<double, 10>(values);

    // you could also use generate function:
    total = 0.0;
    std::generate(std::begin(values), std::end(values),
                  [total]() mutable { return total++; });
    printArray<double, 10>(values);
    std::cout << "Total: " << total << "\n\n";

    // for comparison with a reference:
    total = 0.0;
    std::generate(std::begin(values), std::end(values),
                  [&total]() { return total++; });
    printArray<double, 10>(values);
    std::cout << "Total: " << total << "\n\n";

    // 10.5 11.5 12.5 13.5 14.5 15.5 16.5 17.5 18.5 19.5
    // The range of elements to be set can be of any type that supports operator++().
    std::iota(std::begin(values), std::end(values), 10.5);
    printArray<double, 10>(values);
  }

  {
    // Iterators

    // An array container defines cbegin() and cend() function members that return const
    // iterators; you should use const iterators when you only want to access elements,
    // and not modify them.

    // reverse constant iterators
    std::array<double, 5> these{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    double sum{};
    auto start = std::crbegin(these);
    auto finish = std::crend(these);
    while (start != finish)
      sum += *(start++);
    std::cout << "The sum of elements in reverse order is " << sum << "." << std::endl;

    // with a for loop:
    sum = 0.0;
    for(auto iter = std::crbegin(these); iter != std::crend(these); ++iter)
      sum += *iter;
    std::cout << "The sum of elements in reverse order is " << sum << ".\n";
  }

  {
    // Comparing array containers

    // Must be of same type and size. Containers are compared element by element.

    std::array<double, 4> these{ 1.0, 2.0, 3.0, 4.0 };
    std::array<double, 4> those{ 1.0, 2.0, 3.0, 4.0 };
    std::array<double, 4> them{ 1.0, 3.0, 3.0, 2.0 };
    if (these == those)
      std::cout << "these and those are equal." << std::endl;
    if (those != them)
      std::cout << "those and them are not equal." << std::endl;
    if (those < them)
      std::cout << "those are less than them." << std::endl;
    if (them > those)
      std::cout << "them are greater than those." << std::endl;

    // Copy all elements of those to them
    printArray<double, 4>(them);
    printArray<double, 4>(those);
    them = those;
    printArray<double, 4>(them);
    printArray<double, 4>(those);
  }

  // vector<T> - dynamically sizeable, delete from end, insert at end, access random elements

  {

    // has no elements:
    std::vector<double> values;
    printVector(values);

    // You can increase the capacity by calling reserve() for the container object. If
    // the memory is increased by the call, any existing iterators, such as begin and end
    // iterators, will be invalidated so you must recreate them.
    values.reserve(20);
    printVector(values);

    // Using an initializer list:
    std::vector<unsigned int> primes {2u, 3u, 5u, 7u, 11u, 13u, 17u, 19u};
    printVector(primes);

    // Create vector with initial size and default values (0.0):
    std::vector<double> values1(20);
    printVector(values1);

    // Do not confuse!
    // There is one element initialized to 20:
    std::vector<double> values2 {20};
    printVector(values2);

    // Specify default value.
    // Size is 20 long values - all initialized with 99. The first argument that specifies
    // the number of elements in the vector does not need to be a constant expression. It
    // could be the result of an expression executed at runtime or read in from the
    // keyboard.
    std::vector<long> numbers(20, 99L);
    printVector(numbers);

    // Initialize from another container using iterators:
    std::array<std::string, 5> words {"one", "two", "three", "four", "five"};
    std::vector<std::string> words_copy {std::begin(words), std::end(words)};
    printArray<std::string, 5>(words);
    printVector(words_copy);

    // Using move iterators:
    std::vector<std::string> words_copy1{ std::make_move_iterator(std::begin(words)),
                                          std::make_move_iterator(std::end(words)) };
    printArray<std::string, 5>(words); // is empty now
    printVector(words_copy1);
   }

  {
    // Capacity and Size of a Vector

    std::vector<size_t> primes { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 ,43 ,47 };
    std::cout << "The size is " << primes.size() << std::endl;
    std::cout << "The capacity is " << primes.capacity() << std::endl;
    primes.push_back(51);
    std::cout << "The size is " << primes.size() << std::endl;
    std::cout << "The capacity is " << primes.capacity() << std::endl;

    // Store the number of elements
    auto nElements = primes.size();

    for(auto& prime : primes)
      prime *= 2;
    printVector(primes);

    std::vector<int> values{ 1, 2, 3 }; // 1 2 3 : size is 3
    printVector(values);
    values.resize(5);                   // 1 2 3 0 0 : size is 5
    printVector(values);
    values.resize(7, 99);               // 1 2 3 0 0 99 99 : size is 7
    printVector(values);
    values.resize(6);                   // 1 2 3 0 0 99 : size is 6
    printVector(values);
  }

  {
    // Accessing Elements

    // You can always reference existing elements using an index between square brackets
    // but you cannot create new elements this way – you must use push_back(), insert(),
    // emplace(), or emplace_back().

    std::vector<double> values(20);          // Container with 20 elements created
    values[0] = 3.14159;                     // Pi
    values[1] = 5.0;                         // Radius of a circle
    values[2] = 2.0 * values[0] * values[1]; // Circumference of a circle
    printVector(values);

    std::cout << values.front() << std::endl; // Outputs 3.14159

    // front() and back() return references:
    values.front() = 2.71828; // 1st element changed to 2.71828
    printVector(values);

    // You need to have a very good reason for using data(). Very, very rarely used.
    auto pData = values.data();
    std::cout << *pData << std::endl;
  }

  {
    // Using Iterators with a vector Container

    // No push_front(), only push_back().

    // The copy() algorithm copies elements from the range specified by the iterators
    // supplied as the first two arguments to the destination specified by the iterator
    // that is the third argument.
    std::vector<double> data{ 32.5, 30.1, 36.3, 40.0, 39.2 };
    std::cout << "Enter additional data values separated by spaces or Ctrl+D on a "
                 "separate line to end:"
              << std::endl;
    std::copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(),
              std::back_inserter(data));
    std::copy(std::begin(data), std::end(data),
              std::ostream_iterator<double>(std::cout, " "));
    std::cout << std::endl;

    printContainer<std::vector<double>, double>(data);
  }

  {
    // Adding New Elements to a vector Container

    // Keep in mind that the ONLY way to add elements to a container is to call a member
    // function.

    // Appending Elements
    std::vector<double> values;
    values.push_back(3.1415926);
    printVector(values);

    std::vector<std::string> words;
    // Move string("adiabatic") into the vector
    words.push_back(std::string("adiabatic"));
    // same
    words.push_back("adiabatic");
    printVector(words);

    // emplace_back() is a better way for appending:
    std::vector<std::string> words1;
    words1.push_back(std::string("facetious"));
    // The arguments to the emplace_back() function are the arguments required by the
    // constructor for the object to be appended to the container. The emplace_back()
    // member creates the object in place in the container by calling the constructor for
    // the object type using the argument or arguments you supply, thus eliminating the
    // move operation for the object that push_back() would execute in this case.
    words1.emplace_back("abstemious");
    printVector(words1);

    std::string str {"alleged"};
    // Create string object corresponding to "leg" in place. The emplace() function will
    // call the string constructor that accepts the three arguments:
    words1.emplace_back(str, 2, 3); // 2 = start, 3 = length
    printVector(words1);
  }

  {
    // Inserting Elements

    {
      // You can insert a new element in the interior of a vector sequence using the
      // emplace() function member. The object is created in place rather than creating
      // the object as a separate step, then passing it as the argument. The first
      // argument to emplace() is an iterator that specifies the position where the object
      // is to be created. The object will be inserted BEFORE the element specified by
      // the iterator. The second and any subsequent arguments are passed to the
      // constructor for the element to be inserted.

      std::vector<std::string> words{ "first", "second" };
      // Inserts string(5, 'A') as 2nd element.
      // The emplace() function returns an iterator that points to the inserted element:
      auto iter = words.emplace(++std::begin(words), 5, 'A');
      // Inserts string("$$$$") as 3rd element
      words.emplace(++iter, "$$$$");
      printVector(words);
    }

    {
      // The insert() function member can insert one or more elements in a vector. The
      // first argument is always a const or non-const iterator that points to the
      // insertion point. The element or elements are inserted immediately BEFORE the
      // element pointed to by the first argument unless it is a reverse iterator, in
      // which case elements are inserted immediately AFTER the insertion point. The
      // iterator that is returned points to the first element that was inserted.

      // Keep in mind that all insertions other than at the end of a vector carry
      // overhead. All the elements that follow the insertion point have to be shuffled
      // along to make room for the new element or elements.

      // Vector with 3 elements:
      std::vector<std::string> words{ "one", "three", "eight" };
      // There are two insert() overloads that insert a single object, one with the second
      // parameter as type const T& and the other with the second parameter as type T&& –
      // an rvalue reference. Because the second argument above is a temporary object, the
      // second of these overloads will be called and the temporary object will be moved,
      // rather than copied:
      auto iter = words.insert(++std::begin(words), "two");
      printVector(words);

      //  With the insert() call, the constructor call string("two") is executed to create
      //  the object that is then passed as the second argument. With emplace() the second
      //  argument is used to construct the string object in place in the container.

      std::string more[]{ "five", "six", "seven" }; // Array elements to be inserted
      iter = words.insert(--std::end(words), std::begin(more), std::end(more));
      printVector(words);

      // This just illustrates that it works when the first argument is not pointing to an
      // element, but one past the last element:
      iter = words.insert(std::end(words), "ten");
      printVector(words);

      // Insert multiples of a single element at the insertion point:
      iter = words.insert(std::cend(words)-1, 2, "nine");
      printVector(words);

      // Insert elements specified by an initializer list at the insertion point:
      iter = words.insert(std::end(words),
                          { std::string{ "twelve" }, std::string{ "thirteen" } });
      printVector(words);

      // The insert() member of a vector expects you to use a standard iterator to specify
      // the insertion point; a reverse iterator won’t be accepted – it won’t compile. The
      // need to use reverse iterators could arise when you want to find the last
      // occurrence of a given object in a sequence and insert a new element adjacent to
      // it. The base() function member of a reverse iterator will help:
      std::vector<std::string> str {"one", "two", "one", "three"};
      auto riter = std::find(std::rbegin(str), std::rend(str), "one");
      // A reverse_iterator object has a base() function member that returns the
      // underlying iterator, which, because it is a standard iterator, works in the
      // opposite sense to the reverse iterator. The base iterator for a reverse iterator,
      // riter, points to the next element toward the end of the range. Calling the base()
      // function member of riter returns the standard iterator corresponding to the
      // position preceding iter in the reverse sense, that is, toward the end of the
      // sequence. Since riter will point to the third element, which contains "one",
      // riter.base() will point to the fourth element that contains "three". Using
      // riter.base() as the first argument to insert() results in "five" being inserted
      // before that position, which is after the element to which riter points:
      str.insert(riter.base(), "five");
      // str.insert(riter, "five"); // reverse iterator does not even compile!
      printVector(str); // one two one five three
    }

    {
      // Deleting Elements

      // You can only delete elements from a container by calling a function member of the
      // container object.

      {
        // Remove all the elements from a vector object by calling its clear() member:
        std::vector<int> data(10, 99); // Contains 10 elements initialized to 99
        printVector(data);
        data.clear(); // Remove all elements
        printVector(data);
      }

      {
        // Delete the last element from a vector object by calling its pop_back()
        // function:
        std::vector<int> data(10, 99); // Contains 10 elements initialized to 99
        data.pop_back();               // Remove the last element (no return value)
        printVector(data);
      }

      {
        // AS LONG AS YOU DON’T CARE ABOUT THE ORDER OF THE ELEMENTS!!!
        // Suppose you want to delete the second element from the vector. Here’s how
        // you could do that:

        std::vector<int> data(10);
        std::iota(std::begin(data), std::end(data), -4);
        printVector(data); // -4 -3 -2 -1 0 1 2 3 4 5

        // Interchange 2nd element with the last:
        std::iter_swap(std::begin(data) + 1, std::end(data) - 1);
        data.pop_back(); // Remove the last element
        printVector(data); // -4 5 -2 -1 0 1 2 3 4

        // If you don’t need the excess capacity in a container any more:
        data.shrink_to_fit(); // Reduce the capacity to that needed for elements

        // To delete one elements:
        auto iter = data.erase(std::begin(data) + 1); // Delete the second element
        printVector(data); // -4 -2 -1 0 1 2 3 4

        // Delete more than one element. Here the 2nd and 3rd elements:
        iter = data.erase(std::begin(data)+1, std::begin(data)+3);
        printVector(data); // -4 0 1 2 3 4

        // Don’t forget – the second iterator in a range specification points to one after
        // the last element in the range. This erases the elements at positions
        // std::begin(data)+1 and std::begin(data)+2. The iterator that is returned points
        // to the element following the deleted elements so it will be std::begin(data)+1
        // or std::end(data) if the last element was deleted.
      }

      {
        // The remove() algorithm that is produced by a template that is defined in the
        // algorithm header removes elements from a range that match a specific value.
        // Here’s an example:
        std::vector<std::string> words{ "one",  "none", "some", "all",
                                        "none", "most", "many" };
        std::cout << "Size: " << words.size() << std::endl;
        auto iter = std::remove(std::begin(words), std::end(words), "none");
        printVector(words); // one some all most many
        std::cout << "Size: " << words.size() << std::endl;

        // "none"'s have been replaced by ""'s. To really delete them:
        words.erase(iter, std::end(words)); // Remove surplus elements
        printVector(words); // one some all most many
        std::cout << "Size: " << words.size() << std::endl;

        // This is called the ERASE-REMOVE IDIOM!!!
      }

      {
        // ERASE-REMOVE IDIOM
        std::vector<std::string> words{ "one",  "none", "some", "all",
                                        "none", "most", "many" };
        // In s single statement:
        words.erase(std::remove(std::begin(words), std::end(words), "none"),
                    std::end(words));
        printVector(words); // one some all most many
      }
    }
  }

  // deque (Double-Ended QUEue) -> insert at either end, delete at either end, access random elements

  {
    // Creating deque Containers

    // A deque container with no elements
    std::deque<int> a_deque;
    printContainer<std::deque<int>, int>(a_deque);

    // A deque container with 10 elements
    std::deque<int> my_deque(10);
    printContainer<std::deque<int>, int>(my_deque);

    //  If you create a deque with a given number of string elements, each element will be
    //  initialized by calling the string() constructor. You can also create a deque and
    //  initialize it using an initializer list:
    std::deque<std::string> words{ "one", "none", "some", "all", "none", "most", "many" };
    printContainer<std::deque<std::string>, std::string>(words);

    // Makes a copy of the words container
    std::deque<std::string> words_copy { words };
    printContainer<std::deque<std::string>, std::string>(words_copy);

    // Using a range while copying. Copy could be from any container, not just another deque:
    std::deque<std::string> words_part { std::begin(words), std::begin(words) + 5 };
    // one none some all none
    printContainer<std::deque<std::string>, std::string>(words_part);
  }

  {
    // Accessing Elements
    std::deque<std::string> words{ "one", "none", "some", "all", "none", "most", "many" };
    std::cout << "No bounds checking: " << words[2] << "\tWith bounds checking: " << words.at(2) << std::endl;
    // No capacity(). size always = capacity:
    std::cout << "Size: " << words.size() << std::endl;
    std::cout << "Front: " << words.front() << "\tBack: " << words.back() <<  std::endl;
    // You can resize a deque the same way as for a vector:
    words.resize(3);
    printContainer<std::deque<std::string>, std::string>(words);
  }

  {
    // Adding and Removing Elements

    std::deque<int> numbers{ 2, 3, 4 };
    numbers.push_front(11); // 11 2 3 4
    numbers.push_back(12);  // 11 2 3 4 12
    numbers.pop_front();    // 2 3 4 12
    printContainer<std::deque<int>, int>(numbers);

    numbers.emplace_front(17);
    numbers.emplace_back(19);
    printContainer<std::deque<int>, int>(numbers); // 17 2 3 4 12 19
    // remove is not enough:
    std::remove(std::begin(numbers), std::end(numbers), 3);
    printContainer<std::deque<int>, int>(numbers); // 17 2 4 12 19 19
    // we need erase-remove idiom again:
    numbers = { 17,  2, 3, 4, 12, 19};
    numbers.erase(std::remove(std::begin(numbers), std::end(numbers), 3), std::end(numbers));
    printContainer<std::deque<int>, int>(numbers); // 17 2 4 12 19

    // Delete all:
    numbers.clear();
    printContainer<std::deque<int>, int>(numbers);
  }

  {
    // Replacing the Contents of a deque Container

    // 1. Assign with initializer list:
    std::deque<std::string> words{ "one", "two", "three", "four" };
    auto init_list
      = { std::string{ "seven" }, std::string{ "eight" }, std::string{ "nine" } };
    words.assign(init_list);
    printContainer<std::deque<std::string>, std::string>(words);

    // or:
    {
      std::deque<std::string> words{ "one", "two", "three", "four" };
      words.assign({ "seven", "eight", "nine" });
      printContainer<std::deque<std::string>, std::string>(words);
    }

    // or easier:
    words = { "seven", "eight", "nine" };
    printContainer<std::deque<std::string>, std::string>(words);

    // 2. Assign using ranges copying from another container:
    std::vector<std::string> wordset{ "this", "that", "these", "those" };
    words.assign(std::begin(wordset) + 1,
                 --std::end(wordset)); // Assigns "that" and "these"
    printContainer<std::deque<std::string>, std::string>(words);

    // 3. Assign by repetition:
    words.assign(8, "eight"); // Assign eight instances of string("eight")
    printContainer<std::deque<std::string>, std::string>(words);

    {
      // Using assignment operator:
      std::deque<std::string> words{ "one", "two", "three", "four" };
      printContainer<std::deque<std::string>, std::string>(words);
      std::deque<std::string> other_words;
      other_words = words;                  // other_words same contents as words
      words = { "seven", "eight", "nine" }; // words contents replaced
      printContainer<std::deque<std::string>, std::string>(other_words);
      printContainer<std::deque<std::string>, std::string>(words);
    }
  }

  // list<T> - doubly linked list, insert at any position, delete element at any position, no indexed positions (needs traversal)

  {
    // Creating list Containers

    // empty list:
    std::list<std::string> words;
    printContainer<std::list<std::string>, std::string>(words);

    // A list of 20 empty strings:
    std::list<std::string> sayings {20};
    printContainer<std::list<std::string>, std::string>(sayings);

    // repetition:
    std::list<double> values(5, 3.14159);
    printContainer<std::list<double>, double>(values);

    // copy constructor:
    std::list<double> save_values {values};
    printContainer<std::list<double>, double>(save_values);

    // Using ranges. The only way to modify a bidirectional list iterator is to use the
    // increment or decrement operator. You can use global std::advance function to move
    // iterator.
    std::list<double> samples{ ++cbegin(values), --cend(values) };
    printContainer<std::list<double>, double>(samples);
  }

  {
    // Adding Elements

    std::list<std::string> names{ "Jane", "Jim", "Jules", "Janet" };
    names.push_front("Ian");  // Ian Jane Jim Jules Janet
    names.push_back("Kitty"); // Ian Jane Jim Jules Janet Kitty
    printContainer<std::list<std::string>, std::string>(names);

    // emplace() even more performant than moves. Constructors calles in place. No moves
    // necessary.
    names.emplace_front("Robin"); // Robin Ian Jane Jim Jules Janet Kitty
    names.emplace_back("Canter"); // Robin Ian Jane Jim Jules Janet Kitty Canter
    printContainer<std::list<std::string>, std::string>(names);

    // Using insert:
    std::list<int> data(5, 55); // List of 5elements with value 5
    // Note: std:: in std::begin not necessary (?).
    data.insert(++begin(data), 66); // Insert 66 as the second element
    printContainer<std::list<int>, int>(data);

    // several copies:
    auto iter = begin(data);
    std::advance(iter, 2);    // Increase iter by 2
    data.insert(iter, 3, 88); // Insert 3 copies of 88 starting at the 3rd
    printContainer<std::list<int>, int>(data); // 55 66 88 88 88 55 55 55 55

    // Insert a sequence of elements into the data list:
    std::vector<int> numbers(10, 3);  // Vector of 10 elements with value 3
    data.insert(--(--end(data)), cbegin(numbers), cend(numbers));
    // 55 66 88 88 88 55 55 3 3 3 3 3 3 3 3 3 3 55 55
    printContainer<std::list<int>, int>(data);

    {
      // Construct an element in place (emplace(), emplace_back(), emplace_front()):

      std::list<std::string> names{ "Jane", "Jim", "Jules", "Janet" };
      names.emplace_back("Ann");
      std::string name("Alan");
      std::cout << name << std::endl;
      names.emplace_back(std::move(name));
      std::cout << name << std::endl; // name has been moved
      names.emplace_front("Hugo");
      names.emplace(++begin(names), "Hannah");
      // Hugo Hannah Jane Jim Jules Janet Ann Alan
      printContainer<std::list<std::string>, std::string>(names);
    }
  }

  {
    // Removing Elements

    std::list<int> numbers{ 2, 5, 2, 3, 6, 7, 8, 2, 9 };
    // Erase not necessary:
    numbers.remove(2); // 5 3 6 7 8 9
    printContainer<std::list<int>, int>(numbers);

    // remove_if()
    // Remove even numbers:
    numbers.remove_if([](int n){return n%2 == 0;});
    printContainer<std::list<int>, int>(numbers);

    // unique()
    // removes consecutive duplicate elements
    std::list<std::string> words {"one", "two", "two", "two", "three", "four", "four", "one"};
    words.unique(); // one two three four one
    // You could apply unique() after sorting the elements to ensure that all duplicates
    // are removed from a sequence.
    printContainer<std::list<std::string>, std::string>(words);

    // An overload of unique() accepts a binary predicate as the argument, and elements
    // for which the predicate returns true are regarded as equal.
    words = {"one", "two", "two", "two", "three", "four", "four", "one"};
    words.unique([](std::string first, std::string second) {return first.length() == second.length();});
    // one three four one
    printContainer<std::list<std::string>, std::string>(words);
  }
  {
    // Sorting and Merging Elements

    // sort() in <algorithm> not usable as it needs random access iterator. list<T> has
    // only bidirectional iterator. Must use member function:
    std::list<std::string> names{ "Jane",   "Jim",  "Jules", "Janet",
                                  "Hannah", "Hugo", "Alan",  "Ann" };
    // Names in descending sequence
    names.sort(std::greater<std::string>());
    printContainer<std::list<std::string>, std::string>(names);

    // Names in ascending sequence
    names.sort();
    printContainer<std::list<std::string>, std::string>(names);

    // Function object uses perfect forwarding
    names.sort(std::greater<>());
    // A transparent function object accepts arguments of any type and uses perfect
    // forwarding to avoid unnecessary copying of them. Therefore it will be faster
    // because the arguments to be compared will be moved, not copied.
    printContainer<std::list<std::string>, std::string>(names);

    // Order strings by length when the initial letters are the same
    class my_greater
    {
    public:
      bool operator()(const std::string& s1, const std::string& s2)
      {
        if (s1[0] == s2[0])
          return s1.length() > s2.length();
        else
          return s1 > s2;
      }
    };
    names.sort(my_greater());
    printContainer<std::list<std::string>, std::string>(names);

    // doing the same using a lambda:
    names = { "Jane", "Jim", "Jules", "Janet", "Hannah", "Hugo", "Alan", "Ann" };
    printContainer<std::list<std::string>, std::string>(names);
    names.sort([](const std::string& s1, const std::string& s2) {
      if (s1[0] == s2[0])
        return s1.length() > s2.length();
      else
        return s1 > s2;
    });
    printContainer<std::list<std::string>, std::string>(names);

    // Merging

    // The elements in both containers must be in ascending sequence.
    std::list<int> my_values {2, 4, 6, 14};
    std::list<int> your_values{ -2, 1, 7, 10};
    my_values.merge(your_values);     // my_values contains: -2 1 2 4 6 7 10 14
    printContainer<std::list<int>, int>(my_values);
    // The elements are transferred from your_values to my_values, not copied, so
    // your_values will contain no elements after the operation:
    std::cout << std::boolalpha << "Merged list empty: " << your_values.empty() << std::endl;

    std::list<std::string> my_words {"three", "six", "eight"};
    std::list<std::string> your_words{ "seven", "four", "nine" };
    auto comp_str
      = [](const std::string& s1, const std::string& s2) { return s1[0] < s2[0]; };
    my_words.sort(comp_str);              // "eight" "six" "three"
    your_words.sort(comp_str);            // "four" "nine" "seven"
    my_words.merge(your_words, comp_str); // "eight" "four" "nine" "six" "seven" "three"
    printContainer<std::list<std::string>, std::string>(my_words);

    // Splicing
    {
      // splicing a single element
      std::list<std::string> my_words{ "three", "six", "eight" };
      std::list<std::string> your_words{ "seven", "four", "nine" };
      // my_words.splice(destination, source, from);
      my_words.splice(++std::begin(my_words), your_words, ++std::begin(your_words));
      printContainer<std::list<std::string>, std::string>(my_words); // three four six eight
      printContainer<std::list<std::string>, std::string>(your_words); // seven nine

      // splicing a range of elements
      my_words = { "three", "six", "eight" };
      your_words = { "seven", "four", "nine" };
      my_words.splice(++std::begin(my_words), your_words, ++std::begin(your_words),
                      std::end(your_words));
      // three four nine six eight
      printContainer<std::list<std::string>, std::string>(my_words);
      // seven
      printContainer<std::list<std::string>, std::string>(your_words);

      my_words = { "three", "six", "eight" };
      your_words = { "seven", "four", "nine" };
      my_words.splice(std::begin(my_words), your_words);
      // seven four nine three six eight
      printContainer<std::list<std::string>, std::string>(my_words);
      // (empty)
      printContainer<std::list<std::string>, std::string>(your_words);
    }

    // Accessing Elements

    {
      std::list<std::string> names{ "Jane", "Jim", "Jules", "Janet" };
      names.emplace_back("Ann");
      std::string name("Alan");
      names.emplace_back(std::move(name));
      names.emplace_front("Hugo");
      names.emplace(++begin(names), "Hannah");
      for (const auto& name : names)
        std::cout << name << " ";
      std::cout << std::endl;
    }
  }

  // forward_list<T> - singly linked list, only forward iterators, insert at any point,
  // delete element at any point

  {
    std::forward_list<std::string> my_words {"three", "six", "eight"};
    // there’s no size() member:
    auto count = std::distance(std::begin(my_words), std::end(my_words)); // Result is 3
    std::cout << "Size: " << count << std::endl;

    // move more than one step:
    std::forward_list<int> data {10, 21, 43, 87, 175, 351};
    auto iter = std::begin(data);
    size_t n {3};
    // increments the iterator that is the first argument but does not return it – the
    // return type for advance() is void.
    std::advance(iter, n);
    std::cout << "The " << n + 1 << "th element is " << *iter << std::endl; // Outputs 87

    // splice can only occur after element -> splice_after():
    my_words = {"three", "six", "eight"};
    std::forward_list<std::string> your_words {"seven", "four", "nine"};
    my_words.splice_after(my_words.before_begin(), your_words, ++std::begin(your_words));
    // nine three six eight
    printContainer<std::forward_list<std::string>, std::string>(my_words);
    // seven four
    printContainer<std::forward_list<std::string>, std::string>(your_words);

    // with ranges
    my_words.splice_after(my_words.before_begin(), your_words, ++std::begin(your_words),
                          std::end(your_words));
    // nine three six eight
    printContainer<std::forward_list<std::string>, std::string>(my_words);
    // seven four
    printContainer<std::forward_list<std::string>, std::string>(your_words);

    // another splice
    my_words.splice_after(my_words.before_begin(), your_words);
    printContainer<std::forward_list<std::string>, std::string>(my_words);
    printContainer<std::forward_list<std::string>, std::string>(your_words);
  }
}
