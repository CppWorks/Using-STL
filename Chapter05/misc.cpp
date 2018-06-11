#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <unordered_set>
#include <vector>

// four templates defining sets:
// set<T> - elements are ordered using less<T>, uses equivalence not equality, bidirectional iterators available, header <set>
// multiset<T> - sames as set<T> but duplicates allowed
// unordered_set<T> - uses hashed, elements are compared using equal_to<T>, only forward iterators available, header <unordered_set>
// unordered_multiset<T> - sames as unordered_set<T> but duplicates allowed

// The set containers have similar operations to the corresponding map containers, but
// generally they are used quite differently. You use map containers for storing and
// retrieving objects that are associated with a key. Finding an address or a phone number
// for a name is a typical example. The set containers apply when you are working with
// collections of objects where the membership of a given collection is important.

// The set containers store objects using the objects themselves as keys.

template <typename T, typename F = std::less<T>>
void printSet(const std::set<T, F>& aTSet)
{
  std::copy(std::begin(aTSet), std::end(aTSet),
            std::ostream_iterator<T>{ std::cout, " " });
  std::cout << std::endl << std::string(50, '-') << std::endl;
}

int main()
{
  {
    // Using set<T> Containers

    // Internal organization the same as that of a map<K,T> -> a balanced binary tree.

    // constructing with initializer list:
    std::set<int> numbers{ 8, 7, 6, 5, 4, 3, 2, 1 };

    // elements are in ascending sequence:
    printSet(numbers);

    // different comparison function:
    std::set<std::string, std::greater<std::string>> words{ "one",   "two",  "three",
                                                            "four",  "five", "six",
                                                            "seven", "eight" };
    printSet(words);

    // create from a range:
    std::set<std::string> words2{ std::begin(words), std::end(words) };
    std::set<std::string, std::greater<std::string>> words3{ ++std::begin(words2),
                                                             --std::end(words2) };
    printSet(words2);
    printSet(words3);

    // Adding and Removing Elements

    // Inserting a single element returns a pair<iterator,bool> object, and inserting a
    // single element with a hint just returns an iterator. Inserting multiple elements in
    // a range or an initializer list returns nothing.

    // insert(), emplace(), and emplace_hint() functions:
    std::set<int, std::less<int>> words4{ 1, 2, 3 };
    printSet(words4);
    // pr1.first points to new element. pr1.second is true:
    auto pr1 = words4.insert(4);
    printSet(words4);
    // Element is NOT inserted - pr2.first points to the existing element and pr.second is
    // false:
    auto pr2 = words4.insert(2);
    printSet(words4);
    // iter3 points to new element just before "four"
    auto iter3 = words4.insert(pr1.first, 7);
    printSet(words4);
    // Insert list of elements - no return value
    words4.insert({ 5, 6 });
    printSet(words4);
    int wrds[]{ 8, 9, 10 };
    words4.insert(std::begin(wrds), std::end(wrds)); // Inserts range - no return value
    printSet(words4);

    // creating elements in place with emplace emplace_hint:
    std::set<std::pair<std::string, std::string>> names;
    // The emplace() member returns a pair<iterator,bool> object, and the emplace_hint()
    // member returns just an iterator.
    // pr.first points to new element. pr.second is true:
    auto pr = names.emplace("Lisa", "Carr");
    auto iter = names.emplace_hint(pr.first, "Joe", "King");

    {
      std::set<int> numbers{ 2, 4, 6, 8, 10, 12, 14 };
      printSet(numbers);
      // Removes the 2nd element - 4. iter points to 6:
      auto iter = numbers.erase(++std::begin(numbers));
      printSet(numbers);
      // Returns no. of elements removed - 1
      auto n = numbers.erase(12);
      std::cout << "No. elements deleted: " << n << std::endl;
      printSet(numbers);
      // Returns no. of elements removed - 0
      n = numbers.erase(13);
      std::cout << "No. elements deleted: " << n << std::endl;
      printSet(numbers);
      // Removes all elements
      numbers.clear();
      printSet(numbers);
    }

    {
      // delete a range of elements:
      std::set<int> numbers{ 2, 4, 6, 8, 10, 12, 14 };
      std::cout << "Maximum number of elements: " << numbers.max_size() << ". Are you kidding me?\n";
      printSet(numbers);
      auto iter1 = std::begin(numbers);
      // Points to 6th element - 12:
      advance(iter1, 5);
      // Remove 2nd to 5th inclusive. iter points to 12:
      auto iter = numbers.erase(++std::begin(numbers), iter1);
      printSet(numbers);
    }
  }

  {
    // Accessing Elements

    // find() returns an iterator that points to the element that matches the argument
    // when it’s present; if the object is not in the set, the end iterator is returned.

    std::set<std::string> words {"one", "two", "three", "four", "five"};
    printSet(words);
    auto iter = words.find("one");
    std::cout << *iter << std::endl;
    iter = words.find(std::string{"two"});
    std::cout << *iter << std::endl;
    // iter is std::end(words)
    iter = words.find("six");
    if(iter == std::end(words))
      std::cout << "'six' not found!" << std::endl;
  }

  {
    // Set Iterators

    // NOTE: All iterators returned by function members of a set<T> container point to a const T
    // element. Thus an iterator iterator points to a const element, as does a
    // reverse_iterator iterator as well as the other types. This means that you cannot
    // modify an element. If you want to change an element in a set container, you must
    // first delete it and then insert the modified version.

    // NOTE: When you must be able to modify objects, and still group them in one or more set
    // containers, there’s still a way to do it. You store pointers to the objects in a
    // set container – preferably smart pointers. When you are using set containers,
    // you’ll typically store shared_ptr<T> or weak_ptr<T> objects.

    // Storing Pointers in a set Container

    // If the changes you want to make to objects could potentially alter the order of
    // pointers to those objects that you have stored in a set, THE COMPARISON FUNCTION
    // FOR THE POINTERS MUST NOT DEPEND ON THE OBJECTS. Most of the time, you won’t care
    // about the specific order of elements in a set, only whether or not a given element
    // is in the container. In this case you can use a comparison function object that
    // applies to the pointers without considering the objects to which they point. The
    // recommended option for comparing smart pointers in a container is to use an
    // instance of the owner_less<T> function object type that is defined in the memory
    // header.  An owner_less<T> instance implements a comparison by calling an
    // owner_before() function member of the smart pointer to T, which provide a less-than
    // comparison with another smart pointer. An owner_before<T>() instance returns true
    // when this smart pointer is less-than the smart pointer that is the argument, or
    // false otherwise. The comparison is based on the addresses of the objects that are
    // owned by the pointers and allows equivalence to be determined when two pointers
    // point to same object.

    // NOTE: A shared pointer can point to a different object from the object it owns.
  }

  {
    // Using multiset<T> Containers

    // Same as set<T> but insertions always succeed. The number of identical elements is
    // obtained by calling the count() member of the container with the element.

    // create
    std::multiset<std::string, std::greater<std::string>> words{
      { "dog", "cat", "mouse" }, std::greater<std::string>()
    };

    // In a multiset with a comparison operator comp, elements a and b are equivalent if
    // the expression !(a comp b)&&!(b comp a) evaluates to true.
  }

  {
    // unordered_set<T> Containers

    // 16 buckets
    std::unordered_set<std::string> things{ 16 };
    // Initializer list
    std::unordered_set<std::string> words{ "one", "two", "three", "four" };
    // Range
    std::unordered_set<std::string> some_words{ ++std::begin(words), std::end(words) };
    // Copy constructor
    std::unordered_set<std::string> copy_wrds{ words };

    // 8 buckets & hash function (see Ex4_01 - unordered_map<T>)
    // std::unordered_set<Name, Hash_Name> names{ 8, Hash_Name() };

    // Adding Elements

    // Returns a pair - an iterator & a bool value
    auto pr = words.insert("ninety");
    // 1st arg is a hint. Returns an iterator
    auto iter = words.insert(pr.first, "nine");
    // Inserting an initializer list
    words.insert({ "ten", "seven", "six" });
    // no return values when inserting range of values
    std::vector<std::string> more{ "twenty", "thirty", "forty" };
    words.insert(std::begin(more), std::end(more));
  }

  {
    // create in place

    class Hash_pair
    {
    public:
      size_t operator()(const std::pair<std::string, std::string>& pr) const
      {
        return std::hash<std::string>()(pr.first + pr.second);
      }
    };

    std::unordered_set<std::pair<std::string, std::string>, Hash_pair> names;
    // Returns pair<iterator, bool>
    auto pr = names.emplace("Jack", "Jones");
    // Returns an iterator
    auto iter = names.emplace_hint(pr.first, "John", "Smith");

    std::cout << std::endl << std::string(50, '-') << std::endl;

    // Producing a Bucket List
    for (size_t bucket_index{}; bucket_index < names.bucket_count(); ++bucket_index) {
      std::cout << "Bucket " << bucket_index << ":\n";
      for (auto iter = names.begin(bucket_index); iter != names.end(bucket_index);
           ++iter) {
        std::cout << " " << iter->first << " " << iter->second;
      }
      std::cout << std::endl;
    }

    std::cout << std::endl << std::string(50, '-') << std::endl;

    // list the elements from the names container along with their bucket numbers:
    for (const auto& pr : names)
      std::cout << pr.first << " " << pr.second << " is in bucket " << names.bucket(pr)
                << std::endl;

    // Retrieving Elements

    std::pair<std::string, std::string> person{ "John", "Smith" };
    iter = names.find(person);
    if (iter != std::end(names))
      names.erase(iter);

    // The easy and sensible way to delete the person object if it’s there, is to write this:
    auto n = names.erase(person);

    // Suppose that you need to remove all elements in the names container that have a
    // second name beginning with 'S'
    while (true) {
      auto iter = std::find_if(
        std::begin(names), std::end(names),
        [](const std::pair<std::string, std::string>& pr) { return pr.second[0] == 'S'; });
      if (iter == std::end(names))
        break;
      names.erase(iter);
    }

    // delete range of elements
    // this does not work as only forward iterators are available for unordered sets:
    // iter = names.erase(++std::begin(names), --std::end(names));
    iter = names.erase(++std::begin(names), std::end(names));

  }

  {
    // Operations on Sets

    // The set_union() Algorithm
    std::vector<int> set1{ 1, 2, 3, 4, 5, 6 }; // must be sorted
    std::vector<int> set2{ 4, 5, 6, 7, 8, 9 }; // must be sorted
    std::vector<int> result;

    std::set_union(
      std::begin(set1), std::end(set1), // Range for set that is left operand
      std::begin(set2), std::end(set2), // Range for set that is right operand
      std::back_inserter(result));      // Destination for the result: 1 2 3 4 5 6 7 8 9

    std::cout << std::endl << std::string(50, '-') << std::endl;
    std::copy(std::begin(result), std::end(result),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // output straight away
    std::set_union(std::begin(set1), std::end(set1), std::begin(set2), std::end(set2),
                   std::ostream_iterator<int> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;

    {
      // using comparison functions:
      std::set<int, std::greater<int>> set1{ 1, 2, 3, 4, 5, 6 }; // Contains 6 5 4 3 2 1
      std::set<int, std::greater<int>> set2{ 4, 5, 6, 7, 8, 9 }; // Contains 9 8 7 6 5 4
      std::set<int, std::greater<int>> result;
      // Elements in descending sequence
      std::set_union(
        std::begin(set1), std::end(set1), std::begin(set2), std::end(set2),
        // set doesn't have back inserter
        std::inserter(result, std::begin(result)), // Result destination: 9 8 7 6 5 4 3 2 1
        std::greater<int>());                      // Function object for comparing elements

      std::copy(std::begin(result), std::end(result),
                std::ostream_iterator<int>{ std::cout, " " });
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }
  }

  {
    // The set_intersection() Algorithm

    std::set<int> words1{ 1, 2, 3, 4, 5, 6 }; // must not be in order, will be in order when set is created
    std::set<int> words2{ 4, 5, 6, 7, 8, 9 };
    std::set<int> result;
    std::set_intersection(std::begin(words1), std::end(words1),
                          std::begin(words2), std::end(words2),
                          std::inserter(result, std::begin(result)));

    // Result: 4, 5, 6
    std::copy(std::begin(result), std::end(result),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // The set_difference() Algorithm

    std::set<int, std::greater<int>> words1{ 1, 2, 3, 4, 5, 6 }; // will be 6, 5, 4, 3, 2, 1
    std::set<int, std::greater<int>> words2{ 4, 5, 6, 7, 8, 9 };
    std::set<int, std::greater<int>> result;
    std::set_difference(std::begin(words1), std::end(words1),
                        std::begin(words2), std::end(words2),
                        std::inserter(result, std::begin(result)), // Result: "two" "three" "one"
                        std::greater<int>());              // Function object to compare elements

    // Result: 3, 2, 1
    std::copy(std::begin(result), std::end(result),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // The set_symmetric_difference() Algorithm

    std::set<int> words1{ 1, 2, 3, 4, 5, 6 };
    std::set<int> words2{ 4, 5, 6, 7, 8, 9 };
    std::set_symmetric_difference(std::begin(words1), std::end(words1),
                                  std::begin(words2), std::end(words2),
                                  std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // Result: 1, 2, 3, 7, 8, 9
  }

  {
    // The includes() Algorithm

    // The includes() algorithm compares two sets of elements and returns true if the
    // first set contains all the elements from the second set. It also returns true if
    // the second set is empty.

    std::set<int> words1{ 1, 2, 3, 4, 5, 6 };
    std::set<int> words2{ 4, 5, 6, 7, 8, 9 };
    std::multiset<int> words3;
    std::cout << std::boolalpha
              << std::includes(std::begin(words1), std::end(words1),
                               std::begin(words2), std::end(words2))
              << std::endl;
    // Output: false

    std::cout << std::boolalpha
              << std::includes(std::begin(words1), std::end(words1),
                               std::begin(words2), std::begin(words2))
              << std::endl;
    // Output: true

    std::set_union(std::begin(words1), std::end(words1),
                   std::begin(words2), std::end(words2),
                   std::inserter(words3, std::begin(words3)));
    std::cout << std::boolalpha
              << std::includes(std::begin(words3), std::end(words3),
                               std::begin(words2), std::end(words2))
              << std::endl;
    // Output: true
    std::cout << std::string(50, '-') << std::endl;
  }

  {
    // The union operation will only include one copy of each element that is duplicated.
    // Of course, if words1 and words2 were multiset containers each with duplicate words,
    // then the result may include duplicate elements:
    std::multiset<std::string> words1{ "one",   "two",  "nine", "nine", "one",
                                  "three", "four", "five", "six" };
    std::multiset<std::string> words2{ "four", "two", "seven", "seven", "nine", "nine" };
    std::multiset<std::string> words3;

    std::set_union(std::begin(words1), std::end(words1),
                   std::begin(words2), std::end(words2),
                   std::inserter(words3, std::begin(words3)));

    // When duplicates appear in both containers, they are duplicated in the result.
    std::copy(std::begin(words3), std::end(words3),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }
  return 0;
}
