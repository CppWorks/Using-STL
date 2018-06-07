#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include <memory>
#include <numeric>

int main() {

  // Container Adapters

  // A container adapter is a class template that wraps one of the sequence containers:
  // 1. stack<T> - last-in first-out (LIFO) storage
  // 2. queue<T> - first-in first-out (FIFO) storage
  // 3. priority_queue<T> - largest element is always at the front

  {
    // Creating and Using a stack<T> Container Adapter

    // uses a deque by default:
    std::stack<std::string> words;
    // use another underlying container that supports back(), push_back(), pop_back(),
    // empty(), and size():
    std::stack<std::string, std::list<std::string>> fruit;

    // using an initializer list(?):
    // https://stackoverflow.com/questions/10293302/why-cant-i-construct-a-queue-stack-with-brace-enclosed-initializer-lists-c1
    // std::stack<double, std::list<double>> my_stack1 {1.414, 3.14159265, 2.71828};

    // using an existing container whose type - here list - must be used as underlying
    // container of the stack:
    std::list<double> values {1.414, 3.14159265, 2.71828};
    std::stack<double, std::list<double>> my_stack (values);

    // copy constructor:
    std::stack<double, std::list<double>> copy_stack {my_stack};

  }

  {
    // Creating and Using a queue<T> Container Adapter

    std::queue<std::string> words;

    // copy constructor
    std::queue<std::string> copy_words {words};

    // use a different underlying container from deque<T>:
    // The underlying container type must provide the operations front(), back(),
    // push_back(), and pop_front(), empty(), and size().
    std::queue<std::string, std::list<std::string>> words1;

    std::deque<double> values {1.5, 2.5, 3.5, 4.5};
    std::queue<double> numbers(values);
    while (!numbers.empty())
      // List the queue contents...
      {
        std ::cout << numbers.front() << " ";
        // Output the 1st element
        numbers.pop();
        // Delete the 1st element
      }
    std::cout << std::endl;

  }

  {
    // Creating a Priority Queue

    // A queue in which the elements are ordered; the element with the highest priority –
    // the largest element by default – will be at the front of the queue. Since it’s a
    // queue, only the first element is accessible, which implies that the element with
    // the highest priority will always be processed first.

    // template <typename T, typename Container=std::vector<T>, typename
    // Compare=std::less<T>> class priority_queue

    std::priority_queue<std::string> words;

    std::string wrds[]{ "one", "two", "three", "four" };
    std::priority_queue<std::string> words1{ std::begin(wrds), std::end(wrds) };

    // copy of words
    std::priority_queue<std::string> copy_words{ words };

    // When you want to order the contents in the opposite sense, with the smallest object
    // at the front of the priority queue, you must supply all three template type
    // arguments:
    std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>>
      words2{ std::begin(wrds), std::end(wrds) };

    // Using a deque as an underlying container. Must support  front(), push_back(),
    // pop_back(), size(), and empty().
    std::priority_queue<std::string, std::deque<std::string>> words3 {std::begin(wrds), std::end(wrds)};

    // Here's how you create a priority_queue that uses copies of the elements from a
    // vector container as the initial set of values:
    std::vector<int> values{21, 22, 12, 3, 24, 54, 56};
    std::priority_queue<int> numbers {std::less<int>(), values};

    //  If you want to use a function object of a different type, you must specify all the template type arguments. For example:
    std::priority_queue<int, std::vector<int>, std::greater<int>> numbers1{
      std::greater<int>(), values
    };

    // emplace() is faster than push():
    words.emplace("nine");
    words.push("nine");
  }

  {
    // Heaps

    // A heap is not a container, but it is a particular organization of data.

    // A heap is a complete binary tree, where each node is ordered relative to its child
    // nodes. A parent node is either always greater than or equal to its children, in
    // which case it is called a max heap, or always less than or equal to its children,
    // which is described as a min heap. Note that the child nodes for a given parent are
    // not necessarily ordered relative to each other in a heap.

    // Creating a Heap
    std::vector<double> numbers { 2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0 };
    std::make_heap(std::begin(numbers), std::end(numbers)); // Result: 12 | 10 3.5 | 6.5 8 2.5 1.5 | 6

    // A priority_queue is a heap! Under the covers, an instance of a priority_queue
    // creates a heap. So why does the STL have facilities for both a priority_queue,
    // which is a heap, and the ability to create a heap, especially since you can use a
    // heap as a priority queue? Well, a priority_queue provides an advantage over a heap;
    // the element order is maintained automatically. You can’t upset the ordered state of
    // a priority_queue because you have no direct access to any element other than the
    // first. This is a big plus if all you want is a priority queue.

    // The ability to create a heap in a standard sequence using function templates from
    // the algorithm header offers the same capability as a priority_queue container
    // adapter, but with the added flexibility to access the container that stores the
    // elements.

    // By specifying a function that defines the greater-than operator, you’ll create a
    // min heap. You can use a predicate from the functional header for this:
    std::make_heap(std::begin(numbers), std::end(numbers),
                   std::greater<>()); // Result: 1.5 | 6 2.5 | 6.5 8 12 3.5 | 10

    // Heap Operations

    // The push_heap() template function in the algorithm does that but the way it does it
    // may seem a little odd at first sight. To add an element to a heap you first append
    // the element to the sequence by whatever method works for the sequence. You then
    // call push_heap() to take care of inserting the last element – the element that you
    // appended – at the correct position in the sequence to maintain heap arrangement:
    std::make_heap(std::begin(numbers),
                   std::end(numbers)); // Result: 12 | 10 3.5 | 6.5 8 2.5 1.5 | 6
    numbers.push_back(11);  // Result: 12 | 10 3.5 | 6.5 8 2.5 1.5 | 6 11
    std::push_heap(std::begin(numbers),
                   std::end(numbers)); // Result: 12 | 11 3.5 | 10 8 2.5 1.5 | 6 6.5
    // push_back() adds the element to the end of the sequence and push_heap() restores
    // the heap order. By calling push_heap() you are signaling that you have appended an
    // element to a heap that may have messed up the heap order. The push_heap() function
    // therefore presumes that the last element is new, and rearranges the elements in the
    // sequence to maintain the heap.

    // While a priority queue is a heap, the ordering of elements in a heap is not
    // necessarily the same as in a priority queue as you can see.

    // If you create the heap with your own comparison function, you must use the same
    // comparison function with push_heap():
    numbers = { 2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0 };
    std::make_heap(std::begin(numbers), std::end(numbers),
                   std::greater<>()); // Result: 1.5 | 6 2.5 | 6.5 8 12 3.5 | 10
    numbers.push_back(1.2);
    // Result: 1.5 | 6 2.5 | 6.5 8 12 3.5 | 10 1.2
    std::push_heap(std::begin(numbers), std::end(numbers),
                   std::greater<>()); // Result: 1.2 | 1.5 2.5 | 6 8 12 3.5 | 10 6.5

    // Removing the largest element is similar to adding an element to a heap, but things
    // happen the other way round. You first call pop_heap() and then remove the largest
    // element from the container:
    numbers = { 2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0 };
    std::make_heap(std::begin(numbers),
                   std::end(numbers)); // Result: 12 | 10 3.5 | 6.5 8 2.5 1.5 | 6
    std::pop_heap(std::begin(numbers),
                  std::end(numbers)); // Result: 10 | 8 3.5 | 6.5 6 2.5 1.5 | 12
    numbers.pop_back();               // Result: 10 | 8 3.5 | 6.5 6 2.5 1.5

    // If you created the heap using your own comparison function with make_heap(), you
    // must also supply the function as the third argument to pop_heap():
    numbers = { 2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0 };
    std::make_heap(std::begin(numbers), std::end(numbers),
                   std::greater<>()); // Result: 1.5 | 6 2.5 | 6.5 8 12 3.5 | 10
    std::pop_heap(std::begin(numbers), std::end(numbers),
                  std::greater<>()); // Result: 2.5 | 6 3.5 | 6.5 8 12 10 | 1.5
    numbers.pop_back();              // Result: 2.5 | 6 3.5 | 6.5 8 12 10

    // The STL provides a way to check whether a sequences is still a heap:
    // If the heap was created using an instance of greater<>, the result will be wrong.
    // To get the correct result in this case you must use the expression
    // std::is_heap(std::begin(numbers),std::end(numbers),std::greater<>()).

    if (std::is_heap(std::begin(numbers), std::end(numbers)))
      std::cout << "Great! We still have a heap.\n";
    else
      std::cout << "Oh bother! We messed up the heap.\n";

    // Check that a range that is only partly a heap with is_heap_until(). The
    // is_heap_until() function returns an iterator that points to the first element in
    // the range that is not in heap order:

    numbers = { 2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0 };
    std::make_heap(std::begin(numbers), std::end(numbers),
                   std::greater<>()); // Result: 1.5 | 6 2.5 | 6.5 8 12 3.5 | 10
    std::pop_heap(std::begin(numbers), std::end(numbers),
                  std::greater<>()); // Result: 2.5 | 6 3.5 | 6.5 8 12 10 | 1.5
    auto iter
      = std::is_heap_until(std::begin(numbers), std::end(numbers), std::greater<>());
    if (iter != std::end(numbers))
      std::cout << "numbers is a heap up to " << *iter << std::endl;

    // sort_heap() sorts a range that is assumed to be a heap. If it isn’t a heap, you’ll get a crash at runtime!!!
    numbers = {2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
    std::make_heap(std::begin(numbers), std::end(numbers)); // Result: 12 10 3.5 6.5 8 2.5 1.5 6
    std::sort_heap(std::begin(numbers), std::end(numbers)); // Result: 1.5 2.5 3.5 6 6.5 8 10 12

    // The result of the sort operation is a min heap. Although a heap does not have to be
    // completely ordered, any sequence that is completely ordered is a heap.

    // With a min heap:
    numbers = {2.5, 10.0, 3.5, 6.5, 8.0, 12.0, 1.5, 6.0};
    std::make_heap(std::begin(numbers), std::end(numbers),
                   std::greater<>()); // Result: 1.5 6 2.5 6.5 8 12 3.5 10
    std::sort_heap(std::begin(numbers), std::end(numbers),
                   std::greater<>()); // Result: 12 10 8 6.5 6 3.5 2.5 1.5
    //  The result of sort_heap() on a min heap is a max heap.

    // You know that the algorithm header defines a template for a sort() function that
    // you could use to sort a heap, so why is there a sort_heap() function? The
    // sort_heap() function uses a special sort algorithm that by an incredible
    // coincidence is called Heap Sort. This first creates a heap, then sorts the data in
    // a way that makes use of the fact the data is partially ordered; sort_heap() assumes
    // the heap exists so it just does the second bit. Taking advantage of the partial
    // ordering of a heap can potentially make the sort faster, although this may not
    // always be the case.
  }

  {
    // Storing Pointers in a Container

    {
      // Pointers of type unique_ptr<T> can be stored in a container by moving them there:
      std::vector<std::unique_ptr<std::string>> words;
      // push_back() function with an rvalue reference parameter is called:
      words.push_back(std::make_unique<std::string>("one"));
      words.push_back(std::make_unique<std::string>("two"));
    }

    // Problems with raw pointers

    {
      std::vector<std::string*> words;
      std::string word;
      std::cout
        << "Enter words separated by spaces, enter Ctrl+D on a separate line to end:\n";
      while (true) {
        if ((std::cin >> word).eof()) {
          std::cin.clear();
          break;
        }
        // Create object and store its address
        words.push_back(new std::string{ word });
      }

      // display pointers
      for (auto& w : words)
        std::cout << w << " ";
      std::cout << std::endl;

      // display contents
      for (auto iter = std::begin(words); iter != std::end(words); ++iter)
        std::cout << **iter << " ";
      std::cout << std::endl;

      // problem: memory leaks
      for (auto iter = std::begin(words); iter != std::end(words);) {
        if (**iter == "one")
          // Memory leak! We lost the pointer and can't delete it any more.
          words.erase(iter);
        else
          ++iter;
      }

      // release memory first
      for (auto iter = std::begin(words); iter != std::end(words);) {
        if (**iter == "two") {
          // Release the memory...
          delete *iter;
          // ...then delete the pointer
          words.erase(iter);
        } else
          ++iter;
      }

      // display contents
      for (auto iter = std::begin(words); iter != std::end(words); ++iter)
        std::cout << **iter << " ";
      std::cout << std::endl;

      // Before the vector goes out of scope, you must remember to delete the string
      // objects from the free store.
      for (auto& w : words)
        delete w;    // Delete the string pointed to
      words.clear(); // Delete all the elements from the vector
    }

    {
      // smart pointers don't have this problem

      // Template type arguments can get a little cumbersome but you can always simplify
      // the appearance of the code with a using directive.
      using PString = std::shared_ptr<std::string>;

      // With this in effect you can define the vector container like this:
      std::vector<PString> words;

      std::string word;
      std::cout
        << "Enter words separated by spaces, enter Ctrl+D on a separate line to end:\n";

      while (true) {
        if ((std::cin >> word).eof()) {
          std::cin.clear();
          break;
        }
        // Create smart pointer to string & store it
        words.push_back(std::make_shared<std::string>(word));
      }

      {
        // To prevent a vector container from allocating additional memory for elements
        // too frequently, create the vector and then call reserve() to allocate an
        // initial amount of memory. For example:
        std::vector<std::shared_ptr<std::string>> words;
        words.reserve(100); // Space for 100 smart pointers

        // This is better than creating the vector with a predefined number of elements
        // because each element will be created by calling a shared_ptr<string>
        // constructor when you do this. This is not a big deal but there’s no point in
        // incurring overhead unnecessarily, even if it is small. Usually, the space
        // required for each smart pointer will be a lot less than the space required by
        // the object to which it points, so you can afford to be generous with the space
        // you allocate with reserve().
      }

      {
        // Storing shared_ptr<T> objects allows copies of the pointers to exist outside
        // the container. If you don’t need this capability, you should use unique_ptr<T>
        // objects. It’s essentially the same with ‘unique’ replacing ‘shared’ in the
        // code.

        std::vector<std::unique_ptr<std::string>> words;
        std::string word;
        std::cout
          << "Enter words separated by spaces, enter Ctrl+D on a separate line to end:\n";
        while (true) {
          if ((std::cin >> word).eof()) {
            std::cin.clear();
            break;
          }
          // Create smart pointer to string & store it
          words.push_back(std::make_unique<std::string>(word));
        }
      }
    }

    {
      // Storing Pointers in a Priority Queue

      // When raw pointers or smart pointers are stored, you’ll always need to supply the
      // comparison function that is to be used. If you don’t, the pointers will be
      // compared, not the objects they point to, which is almost certainly not what you
      // want.

      using std::string;
      using std::shared_ptr;
      using std::unique_ptr;
      using std::vector;

      using PString = shared_ptr<string>;

      auto comp = [](const PString& wp1, const PString& wp2) { return *wp1 < *wp2; };

      // We have to specify the third template type argument because the type of the
      // lambda expression will be different from the default comparison type,
      // std::less<T>.
      std::priority_queue<PString, vector<PString>, decltype(comp)> words1 {comp};

      // You can still specify an external container to initialize the priority_queue that
      // contains pointers:
      std::vector<PString> init{ std::make_shared<string>("one"),
                                 std::make_shared<string>("two"),
                                 std::make_shared<string>("three"),
                                 std::make_shared<string>("four") };
      std::priority_queue<PString, std::vector<PString>, decltype(comp)> words(comp,
                                                                               init);

      // If you don’t need to keep the initial set of elements, you could call the
      // emplace() member of the priority_queue object to create them in place in the
      // container:
      std::priority_queue<PString, std::vector<PString>, decltype(comp)> words2{ comp };
      // The emplace() member of words1 will call the constructor for the type of object
      // stored, which will be the shared_ptr<string> constructor. The argument to this
      // constructor is the address of a string object that is created in the free store
      // that is produced by the expression that is the argument to emplace().
      words2.emplace(new string {"one"});
      words2.emplace(new string {"two"});
      words2.emplace(new string {"three"});
      words2.emplace(new string {"five"});

      // Of course, if you don’t want to keep the initial set of elements, you could store
      // unique_ptr<string> elements in the priority queue instead.
      using UPString = unique_ptr<string>;

      auto ucomp = [](const UPString& wp1, const UPString& wp2) { return *wp1 < *wp2; };

      std::priority_queue<UPString, std::vector<UPString>, decltype(ucomp)> words3{ ucomp };

      words3.emplace(new string{ "one" });
      words3.emplace(new string{ "two" });
      words3.emplace(new string{ "three" });
      words3.emplace(new string{ "five" });

      // Alternatively, you can use push():
      words3.push(std::make_unique<string>("one"));
      words3.push(std::make_unique<string>("two"));
      words3.push(std::make_unique<string>("three"));
      words3.push(std::make_unique<string>("five"));

      // The object returned by make_unique<string>() will be moved into the container
      // because the version of push() with an rvalue reference parameter will be selected
      // automatically.
    }

    {
      // Heaps of Pointers

      using PString = std::shared_ptr<std::string>;

      std::vector<PString> words{ std::make_shared<std::string>("one"),
                                  std::make_shared<std::string>("two"),
                                  std::make_shared<std::string>("three"),
                                  std::make_shared<std::string>("four") };
      std::make_heap(std::begin(words), std::end(words),
                     // You need to supply a function pointer that compares objects when
                     // you create a heap of pointers.
                     [](const PString& wp1, const PString& wp2) { return *wp1 < *wp2; });

      // Unlike the class template for the priority_queue container adapter, the template
      // parameter has no default argument value so the compiler will deduce the type of
      // the function object from the third argument in the function call. If the third
      // type parameter to this function template had a default type specified, you would
      // have to specify the type argument, as was necessary in the case of the priority
      // queue template.

      // You must supply the same comparison function that you use with make_heap() as the
      // last argument in any calls of the functions push_heap(), pop_heap(), is_heap(),
      // is_heap_until() and sort_heap().
    }

    {
      // Containers of Base Class Pointers

      // You can store pointers to derived class objects in any container or container
      // adapter that is defined with elements of the base class type. This will enable
      // you to obtain polymorphic behavior with the objects pointed to by the container
      // elements.

      // By storing smart pointers to the base class in a container you get polymorphic
      // behavior automatically. You also get automatic release of free store memory. This
      // applies to any type of container or container adapter.
    }

    {
      // Applying Algorithms to a Range of Pointers

      // Using accumulate(start, end, init, function) to concatenate string objects that
      // are pointed to by shared_ptr<string> objects in a vector:
      using std::string;
      using word_ptr = std::shared_ptr<std::string>;

      std::vector<word_ptr> words{ std::make_shared<string>("one"),
                                   std::make_shared<string>("two"),
                                   std::make_shared<string>("three"),
                                   std::make_shared<string>("four") };
      auto str = std::accumulate(
        std::begin(words), std::end(words), string{ "" },
        [](const string& s, const word_ptr& pw) -> string { return s + *pw + " "; });

      std::cout << str << std::endl;

      // You need to account for the elements being pointers with function members of a
      // container that apply a predicate (e.g. remove_if()):
      std::list<word_ptr> wrds{ std::make_shared<string>("one"),
                                std::make_shared<string>("two"),
                                std::make_shared<string>("three"),
                                std::make_shared<string>("four") };
      // one four
      wrds.remove_if([](const word_ptr& pw) { return (*pw)[0] == 't'; });
    }
  }
  return 0;
}
