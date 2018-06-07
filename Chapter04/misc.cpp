#include "Ex4_01/Name.h"

#include <iostream>
#include <map>
#include <iomanip>

int main() {
  // The elements in a map are objects of type pair<const K,T> that encapsulate an object
  // of type T and its associated key of type K. The key is const in a pair element in a
  // container because allowing the key to be modified would disrupt the sequence of
  // elements in the container.

  // Four varieties of map containers:
  // 1. map<K,T> - keys must be unique, elements are ordered using less<K>
  // 2. multimap<K,T> - duplicate keys are allowed, elements are ordered
  // 3. unordered_map<K,T> - elements are not ordered, elements are located using hash values
  // 4. unordered_multimap<K,T> - duplicate keys are allowed, elements are located using hash values

  // The multi prefix indicates that keys do not need to be unique; its absence indicates
  // that keys must be unique.

  // The unordered_ prefix indicates that the elements are positioned in the container
  // using hash values that are generated from the keys rather than comparing key values.
  // Its absence implies that elements are ordered by comparing keys.

  {
    // Using a map<K, T> Container

    // Don’t be misled by the use of less<K> to order the elements in a map – the elements
    // are not organized as a simple ordered sequence. There is no specific organization
    // required for an STL map container, but typically elements are stored in a balanced
    // binary tree.

    // Creating a map Container

    // a map container that stores age values as type size_t with names of type string as
    // the keys:
    std::map<std::string, size_t> people;

    // Using an initializer list:
    std::map<std::string, size_t> people1{ {"Ann", 25}, {"Bill", 46}, {"Jack", 32}, {"Jill", 32} };

    // or:
    std::map<std::string, size_t> people2{ std::make_pair("Ann", 25),
                                           std::make_pair("Bill", 46),
                                           std::make_pair("Jack", 32),
                                           std::make_pair("Jill", 32) };

    // Duplicate an existing container:
    std::map<std::string, size_t> personnel{ people };

    // Create a map from a range of pair elements from another container:
    std::map<std::string, size_t> personnel1{ std::begin(people), std::end(people) };

    // or with a subrange:
    std::map<std::string, size_t> personnel2 {++std::begin(people2), std::end(people2)};

    // Inserting Elements in a map
    // Elements are only inserted if they are not already present in the map.
    // Create a pair element...
    auto pr = std::make_pair("Fred", 22); // pair<const char*, int>
    // or without implicit conversion:
    // auto pr = std::make_pair<std::string, size_t>(std::string {"Fred"}, 22);

    // ..and insert it
    // The insert() function member returns a pair<iterator, bool> object. The first
    // member of the object is an iterator that points either to the element that was
    // inserted, or to the element that prevented its insertion.  The second member of the
    // object that is returned is a bool value that will be true if the insertion was
    // successful, and false otherwise.
    auto ret_pr = people1.insert(pr);

    // Fred 22 true
    std::cout << ret_pr.first->first << " " << ret_pr.first->second << " "
              << std::boolalpha << ret_pr.second << " \n";

    // The elements are in ascending order of the keys because the default less<string>
    // function object is used to order them in the map.
    for(const auto& p : people1)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    // inserting an existing key:
    ret_pr = people1.insert(std::make_pair("Bill", 84));
    std::cout << ret_pr.first->first << " " << ret_pr.first->second
              << " " << std::boolalpha << ret_pr.second << "\n";

    // Change value for a key:
    if(!ret_pr.second)
      ret_pr.first->second = 84;

    for(const auto& p : people1)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    // insert in one go:
    ret_pr = people1.insert(std::pair<const std::string, size_t> {"John", 33});

    for(const auto& p : people1)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    // A good hint can speed up the insertion operation; a bad hint can do the opposite.
    // Object will be inserted PRIOR to the element identified by the hint, and as close
    // as possible to it.
    ret_pr = people1.insert(std::make_pair("Jim", 48));

    // inserting with a hint
    // It’s a good idea to only provide a hint for an insertion when you’re sure the
    // element is not present.
    if(!people1.count("Ian"))
      people1.insert(ret_pr.first, std::make_pair("Ian", 83));

    for(const auto& p : people1)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    for(const auto& p : people1)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    // You can insert a range of elements from an external source into a map.
    std::map<std::string, size_t> crowd{
      { "May", 55 }, { "Pat", 66 }, { "Al", 22 }, { "Ben", 44 }
    };

    for(const auto& p : crowd)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    auto iter = std::begin(people1);
    std::advance(iter, 4); // begin iterator + 4
    // Insert elements (Bill, Fred, Ian) from people1 into crowd:
    crowd.insert(++std::begin(people1), iter); // 2nd to 4th element

    for(const auto& p : crowd)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    // insert() with initializer list:
    crowd.insert({{"Bert", 44}, {"Ellen", 99}});

    for (const auto& p : crowd)
      std::cout << std::setw(10) << std::left << p.first << " " << p.second << " \n";
    std::cout << std::string(50, '-') << std::endl;

    // You can use a using directive for the std namespace and completely eliminate the
    // need for the std name qualification, but I prefer not to do this because all names
    // in std are effectively imported so it nullifies the point of defining the
    // namespace!!!

    // Constructing map Elements in Place

    // emplace()
    std::map<Name, size_t> people3;
    auto prt = people3.emplace(Name{"Dan", "Druff"}, 77);

    // emplace() with hint
    prt = people3.emplace(Name{"Dan", "Druff"}, 77);
    auto iter1 = people3.emplace_hint(prt.first, Name{"Cal", "Cutta"}, 62);

    // check if emplace created a new entry:
    prt = people3.emplace(Name{ "Dan", "Druff" }, 77);
    auto count = people.size();
    iter1 = people3.emplace_hint(prt.first, Name{ "Cal", "Cutta" }, 62);
    if (count < people.size())
      std::cout << "Success!\n";
    else
      std::cout << "Failure!\n";

    // Accessing Elements in a map

    // The at() function member of a map returns the object associated with the key you
    // supply as the function argument. If the key is not present, an out_of_range
    // exception is thrown. Statements that call at() for a map need to be in a try block
    // – the program will be terminated if the exception is thrown and not caught.

    // The key variable is defined before the try block so this is still accessible from
    // within the catch block.
    Name key;
    try {
      key = Name{ "Dan", "Druff" };
      auto value = people3.at(key);
      std::cout << key << " is aged " << value << "." << std::endl;
      key = Name{ "Don", "Druff" };
      value = people3.at(key);
      std::cout << key << " is aged " << value << "." << std::endl;
    } catch (const std::out_of_range& e) {
      std::cerr << "Exception: " << e.what() << ": " << key << " was not found." << std::endl;
    }

    // Subscript operator
    auto age = people3[Name {"Dan", "Druff"}];
    // Creates a new element if the key is not there! Value will be the default (0).
    auto value = people3[Name {"Ned", "Kelly"}];

    // Sets the value associated with the key to 39.
    people3[Name{ "Ned", "Kelly" }] = 39;  // update
    people3[Name{ "John", "Smith" }] = 44; // creates a new record

    // A map container has the find() function member that returns an iterator that points
    // to the element with the key that matches the argument.
    std::map<std::string, size_t> people4{ { "Fred", 45 },
                                           { "Joan", 33 },
                                           { "Jill", 22 } };
    std::string name{ "Joan" };
    auto iter2 = people4.find(name);
    if (iter2 == std::end(people4))
      std::cout << "Not found.\n";
    else
      std::cout << name << " is " << iter->second << std::endl;

    // Deleting Elements
    {
      std::map<std::string, size_t> people{ { "Fred", 45 },
                                            { "Joan", 33 },
                                            { "Jill", 22 } };
      std::string name{ "Joan" };
      // returns the number of elements that were removed (0, 1):
      if (people.erase(name))
        std::cout << name << " was removed." << std::endl;
      else
        std::cout << name << " was not found." << std::endl;

      // You can also pass an iterator that points to the element to be removed as the
      // argument to erase(). In this case an iterator is returned that points to the
      // element following the one that was removed. The argument must be a valid iterator
      // for the container and must not be the end iterator. If the iterator argument
      // points to the last element in the container, the end iterator will be returned:
      auto iter = people.erase(std::begin(people));
      if(iter == std::end(people))
        std::cout << "The last element was removed." << std::endl;
      else
        std::cout << "The element preceding " << iter->first << " was removed." << std::endl;

      // There’s a further version of erase() that accepts two iterator arguments defining
      // a range of elements to be removed:
      iter = people.erase(std::begin(people),
                          --std::end(people)); // Erase all except the last

      // When you want to remove all the elements from a map, you can call the clear()
      // member.
      people.clear();
    }
  }
  return 0;
}
