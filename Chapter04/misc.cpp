#include "Ex4_01/Name.h"
#include "../Chapter02/Ex2_06/Box.h"

#include <iostream>
#include <map>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

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

  {
    // Using pair<> and tuple<> Objects

    // Operations with a pair

    // Two public member functions: first(), second(). Several constructors:
    std::string s1 {"test"}, s2{"that"};
    std::pair<std::string, std::string> my_pair{s1, s2};
    std::pair<std::string, std::string> your_pair{std::string {"test"}, std::string {"that"}};
    std::pair<std::string, std::string> his_pair{"test", std::string {"that"}};
    std::pair<std::string, std::string> her_pair{"test", "that"};

    // Because of the provision of rvalue reference versions of the constructor,
    // either or both pair template type arguments can be a unique_ptr<T>.

    // The make_pair<T1, T2>() function template is a helper function that
    // creates and returns a pair<T1,T2> object.
    {
      // If the template type arguments were omitted in the last two statements,
      // the objects would be of types pair<const char*, string> and pair<const
      // char*, const char*>.

      auto my_pair = std::make_pair(s1, s2);
      auto your_pair = std::make_pair(std::string {"test"}, std::string {"that"});
      auto his_pair = std::make_pair<std::string, std::string>("test", std::string {"that"});
      auto her_pair = std::make_pair<std::string, std::string>("test", "that");

      // A pair object is also copy or move constructible as long as its members are.
      // Copy constructor:
      std::pair<std::string, std::string> new_pair{my_pair};
      //  move constructor:
      std::pair<std::string, std::string> old_pair{std::make_pair(std::string{"his"}, std::string{"hers"})};

      // Construction from a tuple:
      std::pair<Name, Name> couple{
          std::piecewise_construct, // piecewise_construct_t - empty type that
                                    // is used as a tag or marker
          std::forward_as_tuple("Jack", "Jones"),
          std::forward_as_tuple("Jill", "Smith")};

      // The only purpose for the piecewise_construct argument is to
      // differentiate between this constructor call, and a constructor call
      // where the two tuple arguments are to be used as values for the first
      // and second members of the pair.

      // forward_as_tuple() is a function template that creates a tuple of
      // references to its arguments that can then be forwarded on.

      //  You are not likely to need this pair constructor often, but it
      //  provides the unique ability to create a pair<T1, T2> object where the
      //  types T1 and T2 do not support copy or move operations – they can only
      //  be created in place.
    }

    {
      // Note that forward_as_tuple() will create a tuple of rvalue references
      // if the arguments are temporary objects. Here c is tuple<int&&, int&&>,
      // with the members as rvalue references:
      int a {1}, b {2};
      const auto& c = std::forward_as_tuple(a,b);

      {
        // Copy and move assignment is supported for pair objects if the members
        // can be copied or moved.

        // Default constructor: members are empty string objects.
        std::pair<std::string, std::string> old_pair;

        std::pair<std::string, std::string> new_pair{std::string{"his"},
                                                     std::string{"hers"}};
        old_pair = new_pair; // Copy assignment
        new_pair = std::pair<std::string, std::string>{
            std::string{"these"}, std::string{"those"}}; // Move assignment

        // You can also assign one pair to another when the pair objects contain
        // members of different types, as long as the types of the members of
        // the
        // pair that is the right operand are implicitly convertible to the
        // types
        // of the members of the pair that is the left operand.

        auto pr1 =
            std::make_pair("these",
                           "those"); // Type pair<const char*, const char*>
        std::pair<std::string, std::string> pr2; // Type pair<string, string>
        pr2 = pr1;                               // OK in this case

        {
          // You have the full set of comparison operators for pair objects, ==,
          // !=,
          // <, <=, >, and >=. For these to work, the pair objects that are the
          // operands must be of the same type and their members must be
          // comparable
          // in the same way.
          std::pair<std::string, std::string> new_pair;
          new_pair.first = "his";
          new_pair.second = "hers";
          if (new_pair == std::pair<std::string, std::string>{"his", "hers"})
            std::cout << "Equality!\n";

          std::pair<int, int> p1{10, 9};
          std::pair<int, int> p2{10, 11};
          std::pair<int, int> p3{11, 9};
          std::cout << std::boolalpha << (p1 < p2) << " " << (p1 > p3) << " "
                    << (p3 > p2) << std::endl;
          // Outputs "true", "false", "true"

          {
            // The swap() member of a pair object swaps its first and second
            // members with those of the pair that is passed as the argument.
            std::pair<int, int> p1{10, 11};
            std::pair<int, int> p2{11, 9};
            p1.swap(p2);
          }
        }
      }
    }
  }

  {
    // Operations with a tuple

    // The easiest way to create a tuple object is to use the make_tuple()
    // helper function. The my_tuple object will be of type tuple<Name, int,
    // string>:
    auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42, std::string{"914 626 7890"});

    // Several constructors:
    std::tuple<std::string, size_t> my_t1; // Default initialization
    std::tuple<Name, std::string> my_t2{Name{"Andy", "Capp"},
                                        std::string{"Programmer"}};
    std::tuple<Name, std::string> copy_my_t2{my_t2}; // Copy constructor
    std::tuple<std::string, std::string> my_t3{"this",
                                               "that"}; // Implicit conversion

    // You can construct a tuple from a pair:
    auto the_pair = std::make_pair("these", "those");
    std::tuple<std::string, std::string> my_t4{the_pair};
    std::tuple<std::string, std::string> my_t5{
        std::pair<std::string, std::string>{"this", "that"}};

    // Comparison
    std::cout << std::boolalpha << (my_t4 < my_t5) << std::endl; // true

    // Swapping
    my_t4.swap(my_t5); // member function
    std::swap(my_t4, my_t5); // global function

    {
      // Accessing elements using the get<>() template function.
      auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42,
                                      std::string{"914 626 7890"});
      std::cout << std::get<0>(my_tuple) << " age = " << std::get<1>(my_tuple)
                << " tel: " << std::get<2>(my_tuple) << std::endl;

      {
        // You can also obtain an element from a tuple using get<>() based on
        // the type, as long as there is only one element of that type.
        auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42,
                                        std::string{"914 626 7890"});
        std::cout << std::get<Name>(my_tuple)
                  << " age = " << std::get<int>(my_tuple)
                  << " tel: " << std::get<std::string>(my_tuple) << std::endl;
      }

      {
        // Using global tie() function:
        auto my_tuple = std::make_tuple(Name{"Peter", "Piper"}, 42,
                                        std::string{"914 626 7890"});
        Name name{};
        size_t age{};
        std::string phone{};
        std::tie(name, age, phone) = my_tuple;
        std::cout << name << " " << age << " " << phone << std::endl;
        // leaving out a tuple member:
        std::tie(name, std::ignore, phone) = my_tuple;

        // You can also use the tie() function to implement a lexicographical
        // comparison of the data members of a class.
        // bool Name::operator<(const Name& name) const
        // {
        //   return std::tie(second, first) < std::tie(name.second, name.first);
        // }
      }
    }

    {
      // Using a multimap Container

      // The insert() member of a multimap container inserts one or more
      // elements and always succeeds. Returns an iterator that points to the
      // element that was inserted:

      std::multimap<std::string, std::string> pets; // Element is pair{pet_type, pet_name}
      auto iter =
        pets.insert(std::pair<std::string, std::string>{std::string{"dog"}, std::string{"Fang"}});
      iter = pets.insert(iter, std::make_pair("dog", "Spot"));    // Insert Spot BEFORE Fang
      pets.insert(std::make_pair("dog", "Rover")); // Inserts Rover AFTER Fang
      pets.insert(std::make_pair("cat", "Korky")); // Inserts Korky before all dogs
      pets.insert({{"rat", "Roland"},
                   {"pig", "Pinky"},
                   {"pig", "Perky"}}); // Inserts list elements

      // The first argument in the third statement is an iterator that is a hint
      // as to where the element should be placed. The element is inserted
      // immediately before the element pointed to by iter, so this allows you
      // to override the default insertion position, which would be following
      // the previous element that was inserted with a key equivalent to "dog".

      // constructing a new element in place:
      iter = pets.emplace("rabbit", "Flopsy");
      iter = pets.emplace_hint(iter, "rabbit", "Mopsy");  // Create preceding Flopsy

      // The subscript operator is not supported by a multimap because a key
      // does not necessarily identify a unique element. Similarly the at()
      // function you have for a map container is not available with a multimap.

      // using find(); finds the first occurence:
      {
        std::multimap<std::string, size_t> people{{"Ann", 25},  {"Bill", 46}, {"Ann", 88},
                                                  {"Jack", 77}, {"Jack", 32},
                                                  {"Jill", 32}, {"Ann", 35}};
        std::string name{"Bill"};
        auto iter = people.find(name);
        if (iter != std::end(people))
          std::cout << name << " is " << iter->second << std::endl;

        // string literal as an argument, which demonstrates that the argument
        // does not have to be the same type as the key. You can pass any value
        // or object as the argument that can be compared to the key using the
        // function object that is in effect for the container.
        iter = people.find("Ann");
        if (iter != std::end(people))
          std::cout << iter->first << " is " << iter->second << std::endl;

        // If you want all occurences of "Ann", use equal_range():
        auto pr = people.equal_range("Ann");
        // The range of elements with keys equivalent to the argument is
        // returned as a pair of iterators encapsulated in a pair object:
        if (pr.first != std::end(people)) {
          for (auto iter = pr.first; iter != pr.second; ++iter)
            std::cout << iter->first << " is " << iter->second << std::endl;
        }

        std::cout << std::string(50, '-') << std::endl;

        // equal_range in terms of lower_bound() and upper_bound():
        auto iter1 = people.lower_bound("Ann");
        auto iter2 = people.upper_bound("Ann");
        if (iter1 != std::end(people)) {
          for (auto iter = iter1; iter != iter2; ++iter)
            std::cout << iter->first << " is " << iter->second << std::endl;
        }

        // number of elements of a certain key:
        std::cout << "Number of Ann's: " << people.count("Ann") << std::endl;

        // you could do the same with distance():
        std::string key{"Ann"};
        std::cout << "Number of Ann's: "
                  << std::distance(people.lower_bound(key),
                                   people.upper_bound(key))
                  << std::endl;

        // three different types of erase() functions (see Ex4_05):
        // 1. iterator pointing to an element to delete that element, returns nothing.
        // 2. accepts a key, returns  number of elements removed.
        // 3. accepts two iterators that define a range,  returns an iterator hat points to the element that follows the last element removed.
      }
    }
  }
  {
    // Changing the Comparison Function for a map or a multimap

    // CAUTION: A comparison function for a map container must not return true for equality.

    // In other words, you MUST NOT USE <= or >= comparisons. A map or multimap
    // container uses equivalence to determine when keys are equal. Two keys,
    // key1 and key2, are equivalent and therefore considered to be equal if the
    // expressions key1 < key2 and key2 < key1 both result in false.

    std::cout << std::string(50, '-') << std::endl;

    std::map<Name, size_t> people{{Name{"Al", "Bedo"}, 53},
                                  {Name{"Woody", "Leave"}, 33},
                                  {Name{"Noah", "Lot"}, 43}};

    for( const auto& p : people)
      std::cout << p.first << " " << p.second << " \n";

    std::cout << std::string(50, '-') << std::endl;

    // The three elements will now be ordered in descending sequence:
    std::map<Name, size_t, std::greater<Name>> people1{
        {Name{"Al", "Bedo"}, 53},
        {Name{"Woody", "Leave"}, 33},
        {Name{"Noah", "Lot"}, 43}};

    for( const auto& p : people1)
      std::cout << p.first << " " << p.second << " \n";
  }

  {
    // Defining Your Own Function Object for Comparing Elements
    using PUString = std::unique_ptr<std::string>;

    class Key_compare {
    public:
      bool operator()(const PUString &p1, const PUString &p2) const {
        return *p1 < *p2;
      }
    };

    std::map<PUString, std::string, Key_compare> phonebook;

    std::cout << std::string(50, '-') << std::endl;

    // We can’t use an initializer list with this map because an initializer
    // list involves copying, and unique_ptr objects cannot be copied.

    // There’s a pair constructor that can move the arguments:
    phonebook.emplace(std::make_unique<std::string>("Fred"), "914 626 7897");
    // insert() member; this will also move the element:
    phonebook.insert(std::make_pair(std::make_unique<std::string>("Lily"), "212 896 4337"));

    // Range-based for loop:
    for (const auto &p : phonebook)
      std::cout << *p.first << " " << p.second << std::endl;

    std::cout << std::string(50, '-') << std::endl;

    // Using iterators:
    for(auto iter = std::begin(phonebook); iter != std::end(phonebook); ++iter)
      std::cout << *iter->first << " " << iter->second << std::endl;
  }

  {
    // Hashing

    // Functions That Generate Hash Values

    // The functional header defines specializations of a hash<K> template. The
    // operator()() member of a hash<K> instance accepts a single argument of
    // type K and returns the hash value as type size_t.

    // hashing ints:
    std::hash<int> hash_int;
    std::vector<int> n{-5, -2, 2, 5, 10};
    std::cout << std::string(50, '-') << std::endl;
    // Note that the conditions for C++14 conformance does not exclude
    // the possibility that hash values for a given type of key may be identical
    // to the key.
    std::transform(std::begin(n), std::end(n),
                   std::ostream_iterator<size_t>(std::cout, " "), hash_int);
    std::cout << std::endl;

    std::cout << std::string(50, '-') << std::endl;

    // hashing floats:
    std::hash<double> hash_double;
    std::vector<double> x{3.14, -2.71828, 99.0, 1.61803399, 6.62606957E-34};
    std::transform(std::begin(x), std::end(x),
                   std::ostream_iterator<size_t>(std::cout, " "), hash_double);
    std::cout << std::endl;

    // hashing pointers:
    std::hash<Box *> hash_box;
    Box box{1, 2, 3};
    std::cout << std::string(50, '-') << "\nHash value = " << hash_box(&box)
              << std::endl;

    // hashing smart pointers:
    auto upbox = std::make_unique<Box>(1, 2, 3);
    std::cout << std::string(50, '-')
              << "\nHash value = " << hash_box(upbox.get()) << std::endl;

    // There is actually a specialization of the hash<K> template for
    // unique_ptr<T> and shared_ptr<T> objects:
    std::hash<std::unique_ptr<Box>> hash_sp_box;
    upbox = std::make_unique<Box>(1, 2, 3);
    std::cout << std::string(50, '-') << "\nHash value = " << hash_sp_box(upbox)
              << std::endl;

    // But remember: You are hashing an address, not the object itself! There
    // needs to be a way to generate a hash value for whatever type of key you
    // are using. One option is to use the hash functions that the STL provides
    // to generate a hash value from the data members of your class.

    // Here’s an example of hashing a string object:
    std::hash<std::string> hash_str; // template specialisation defined in <string>
    std::string food{"corned beef"};
    std::cout << "corned beef hash is " << hash_str(food) << std::endl;

    // NOTE: There is no specific provision for hashing C-style strings. Using
    // the hash<T> template with type const char* will use the specialization
    // for pointers. If you want to obtain a hash value for a C-style string as
    // a hash of the character sequence, you can create a string object from it
    // and use a hash<string> function object.
  }

  {
    // Using an unordered_map Container

    // Elements are stored in a hash table where entries in the table are
    // referred to as buckets and a bucket can hold several elements.

    // An unordered_map has to be able to compare keys for equality. This is
    // necessary to identify the specific element to be retrieved from a bucket
    // that contains more than one element and to decide when the same key is
    // already in the container. By default the container will use an instance
    // of the equal_to<K> template that is defined in the functional header.
    // This will use the == operator to compare keys so the container is
    // determining that keys are the same when they are equal, which is
    // different from a map container that uses equivalence. If the keys you are
    // using are of a class type that does not implement operator==(), you will
    // need to supply a function object that will compare your keys.

    // Creating and Managing unordered_map Containers

    // You can create an unordered_map container as simply as you can create a
    // map, as long as the key type, K, can be hashed using a hash<K> instance
    // and keys can be compared using the == operator:

    // Name,age
    std::unordered_map<std::string, size_t> people{
        {"Jan", 44}, {"Jim", 33}, {"Joe", 99}};

    // You can specify the number of buckets:
    std::unordered_map<std::string, size_t> people1 {{{"Jan", 44}, {"Jim", 33}, {"Joe", 99}}, 10};

    // from an existing container:
    std::vector<std::pair<std::string, size_t>> folks{{"Jan", 44}, {"Jim", 33},
                                                      {"Joe", 99}, {"Dan", 22},
                                                      {"Ann", 55}, {"Don", 77}};
    std::unordered_map<std::string, size_t> neighbors{std::begin(folks),
                                                      std::end(folks), 500};

    // The elements will be pair<Name, size_t> objects:
    // Specify hash function (Name.h).
    std::unordered_map<Name, size_t, Hash_Name> people2{
        // The innermost braces enclose the arguments
        // to the Name constructor. The next level
        // braces enclose the arguments to the
        // pair<Name,size_t> constructor.
        {{{"Ann", "Ounce"}, 25},
         {{"Bill", "Bao"}, 46},
         {{"Jack", "Sprat"}, 77}},
        500,          // Bucket count
        Hash_Name()}; // Hash function for keys

    // Specify equality (in Name.h):
    std::unordered_map<Name, size_t, Hash_Name, Name_Equal> people3{
        {{{"Ann", "Ounce"}, 25},
         {{"Bill", "Bao"}, 46},
         {{"Jack", "Sprat"}, 77}},
        500,           // Bucket count
        Hash_Name(),   // Hash function for keys
        Name_Equal()}; // Equality comparison for keys

    std::cout << std::string(50, '-') << std::endl;
    for(auto& item : people3) {
      std::cout << item.first.getFirstName() << " " << item.first.getSecondName() << " " << item.second << std::endl;
    }
  }
  return 0;
}
