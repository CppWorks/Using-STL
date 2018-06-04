#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include <exception>
#include <memory>
#include <functional>

template <typename T>
T& larger(T& a, T& b)
{
  return a > b ? a : b;
}

// You can define class templates, function templates and type alias templates.

template <typename T>
class Array {
private:
  T* elements;  // Array of type T
  size_t count; // Number of array elements
public:
  explicit Array(size_t arraySize);
  Array(const Array& other);
  Array(Array&& other);
  virtual ~Array() {delete [] elements;};
  T& operator[](size_t index) {return elements[index];};
  const T& operator[](size_t index) const;

  // In general, if you need to define any of a copy or move constructor, a copy or move
  // assignment operator, or a destructor, you should define all five class members, or
  // specify the ones you don’t want as deleted.

  Array& operator=(const Array& rhs);

  // A class that implements a move constructor and a move assignment operator is said to
  // have move semantics.

  Array& operator=(Array&& rhs);

  // The size() member is implemented within the class template so it’s inline by default
  // and no external definition is necessary.

  size_t size()
  {
    return count;
  }
};

template <typename T>
// Catching exceptions from a constructor's initializer list(function try block):
// https://stackoverflow.com/a/160164/365425
// https://stackoverflow.com/a/5612508/365425
Array<T>::Array(size_t arraySize) try : elements {
  new T[arraySize]
}
, count{ arraySize } {}
catch (const std::exception& e)
{
  std::cerr << "Memory allocation failure in Array constructor." << std::endl;
}

// inline copy constructor
template <typename T>
inline Array<T>::Array(const Array& other)
  try : elements {new T[other.count]}, count {other.count}
{
  for (size_t i {}; i < count; ++i)
    elements[i] = other.elements[i];
}
catch (std::bad_alloc&)
  {
    std::cerr << "memory allocation failed for Array object copy." << std:: endl;
  }

// You can define templates for type aliases.
template<typename T> using ptr = std::shared_ptr<T>;

template <typename ForwardIter, typename F>
void change(ForwardIter first, ForwardIter last, F fun)
{
  for (auto iter = first; iter != last; ++iter)
    *iter = fun(*iter);
}

int main()
{
  {
  std::vector<double> values;

  std::cout << "Enter values separated by one or more spaces. Enter Ctrl+D on a separate "
               "line to end:\n ";

  values.insert(std::begin(values), std::istream_iterator<double>(std::cin),
                std::istream_iterator<double>());

  std::cout << "The average is "
            << std::accumulate(std::begin(values), std::end(values), 0.0) / values.size()
            << std::endl;
  }

  {
    std::string first {"To be or not to be."};
    std::string second {"That is the question."};
    std::cout << larger(first, second) << std::endl;

    double a = 2.0;
    double b = 3.5;
    auto whatever = larger(a, b);
    std::cout << whatever << std::endl;
  }

  {
    //  The compiler only compiles the member functions that the program uses, so you
    //  don’t necessarily get the entire class that would result from a simple
    //  substitution of the argument for the template parameter.

    Array<int> data {40};
    std::cout << data[0] << std::endl;
  }

  {
    using std::string;

    // Now you can define a shared pointer more easily:
    ptr<string> my_pointer;
  }

  // It’s important to appreciate that unless the objects are rvalues – temporary objects
  // – of a type that has move semantics, all the STL containers store copies of the
  // objects that you store in them. The STL also requires that the move constructor and
  // assignment operator must be specified as noexcept, which indicates they do not throw
  // exceptions. If you add an object of a type that does not have move semantics to a
  // container and modify the original, the original and the object in the container will
  // be different. However, when you retrieve an object, you get a reference to the object
  // in the container so you can modify stored objects. The copies that are stored are
  // created using the copy constructor for the type of object. For some objects, copying
  // can be a process that carries a lot of overhead. In this case, it will be better to
  // either store pointers to the objects in the container, or to move objects into the
  // container assuming that move semantics have been implemented for the type.

  // Caution Don’t store derived class objects in a container that stores elements of a
  // base class type. This will cause slicing of the derived class objects. If you want to
  // access derived class objects in a container with a view to obtaining polymorphic
  // behavior, store pointers to the objects in a container that stores base class
  // pointers – or better still – smart pointers to the base type.

  // Note: If the type of your objects does not meet the requirements of a container that
  // you are using, or you misuse the container template in some other way, you will often
  // get compiler error messages relating to code that is deep in a Standard Library
  // header file. When this occurs, don’t rush to report errors in the Standard Library.
  // Look for errors in your code that is using the STL!

  // The bare minimum for type T objects to be stored in a container:
  // (Considering that the compiler provides default implementations for all the members
  // in many circumstances, most class types should meet these requirements.)

  // class T {
  // public:
  //   T();
  //   T(const T& t);
  //   ~T();
  //   T& operator=(const T& t);
  // };

  {
    int data[] {1, 2, 3, 4, 5, 6};
    auto iter = std::begin(data);
    std::advance(iter, 3);
    std::cout << "Fourth element is " << *iter << std::endl;
  }

  {
    int data[] {1, 2, 3, 4, 5, 6};
    std::cout << "The number of elements in data is "
              << std::distance(std::begin(data), std::end(data)) << std::endl;
  }

  {
    int data[] {1, 2, 3, 4, 5, 6};
    auto iter = std::begin(data);
    auto fourth = std::next(iter, 3);
    std::cout << "1st element is " << *iter << " and the 4th is " << *fourth << std::endl;
  }

  {
    int data[] {1, 2, 3, 4, 5, 6};
    auto iter = std::end(data);
    std::cout << "Fourth element is " << *std::prev(iter, 3) << std::endl;
  }

  {
    std::unique_ptr<std::string> pname1 {new std::string {"Algernon"}};
    auto pname2 = std::make_unique<std::string>("Algernon");
    // You supply as many arguments to the make_unique<T>() function as the T constructor
    // requires:
    auto pstr = std::make_unique<std::string>(6, '*');

    size_t len{10};
    std::unique_ptr<int[]> pnumbers1 {new int[len]};

    auto pnumbers2 = std::make_unique<int[]>(len);

    for(size_t i{} ; i < len ; ++i)
      pnumbers1[i] = i*i;

    for(size_t i{} ; i < len ; ++i)
      std::cout << pnumbers1[i] << " ";
    std::cout << std::endl;

    std::cout << *pname1 << std::endl;
    std::cout << *pname2 << std::endl;
    std::cout << *pstr << std::endl;

    // You cannot pass a unique_ptr<T> object to a function by value because it CANNOT BE
    // COPIED. You must use a reference parameter in a function to allow a unique_ptr<T>
    // object as an argument. You can return a unique_ptr<T> from a function because it
    // will not be copied, but will be returned by an implicit move operation.

    // Here’s how you obtain a raw pointer from a unique_ptr<T>:
    auto unique_p = std::make_unique<std::string>(6, '*');
    std::string* rawpstr {unique_p.get()};

  }

  {
    auto pname = std::make_unique<std::string>("Algernon");
    //  Calling reset() for a unique_ptr<T> object with no argument destroys the object
    //  that is pointed to and replaces the raw pointer in the unique_ptr<T> object with
    //  nullptr:
    pname.reset();  // Release memory for string object
  }

  {
    auto pname = std::make_unique<std::string>("Algernon");

    // You can pass the address of a new T object in the free store to reset(), and the
    // previous object that was pointed to will be destroyed and its address will be
    // replaced by that of the new object:
    pname.reset(new std::string{ "Fred" });
  }

  {
    // The release() member of up_name returns the original raw pointer to the string
    // object containing Algernon" so after executing the second statement, up_name will
    // contain nullptr, and up_new_name will point to the original "Algernon" string
    // object. The effect is to transfer ownership of the object in the free store from
    // one unique pointer to another:

    auto up_name = std::make_unique<std::string>("Algernon");
    std::unique_ptr<std::string> up_new_name{up_name.release()};
  }

  {
    // You can interchange the objects owned by two unique_ptr<T> pointers with swap():
    auto pn1 = std::make_unique<std::string>("Jack");
    auto pn2 = std::make_unique<std::string>("Jill");
    pn1.swap(pn2);
  }

  {
    // unique_ptr<T> objects are implicitly convertible to type bool. If the objects
    // contains nullptr the result of the conversion is false; otherwise the result is
    // true. This means you can use an if statement to check for a non-null unique_ptr<T>
    // object:

    auto up_name = std::make_unique<std::string>("Algernon");
    std::unique_ptr<std::string> up_new{up_name.release()};
    if(up_new)
      // true if not nullptr
      std::cout << "The name is " << *up_new << "." << std::endl;
    if(!up_name)
      // true if nullptr
      std::cout << "The unique pointer is nullptr." << std::endl;
  }

  {
    std::shared_ptr<double> pdata {new double{999.0}};
    *pdata = 8888.0;
    std::cout << *pdata << std::endl;
    *pdata = 8889.0;
    std::cout << *pdata << std::endl;
  }

  {
    // Don’t forget, you should not use an initializer list when you specify a type as
    // auto because the type will be deduced to be std::initializer_list.
    auto pdata = std::make_shared<double>(999.0);

    std::shared_ptr<double> pdata2 {pdata};
  }

  {
    std::shared_ptr<double> pdata{ new double{ 999.0 } };
    std::shared_ptr<double> pdata2;  // Pointer contains nullptr
    pdata2 = pdata;  // Copy pointer - both point to the same variable
    std::cout << *pdata << std::endl;  // Outputs 999.0

    // pvalue is raw pointer of type double* and points to 999.0
    auto pvalue = pdata.get();

    // Caution Duplicates of a shared_ptr<T> object should only be created by the copy
    // constructor or the copy assignment operator. Creating a shared_ptr<T> using the raw
    // pointer returned by get() for a different pointer will result in undefined
    // behavior, which in most cases means a program crash.
  }

  // Note: It is possible to create a shared_ptr<T> object that points to an array. This
  // involves supplying a definition for a deleter function that the smart pointer is to
  // use to release the heap memory for the array. The details of how you do this are out
  // of scope.

  {
    // If you assign nullptr to a shared_ptr<T> object the address stored will be replaced
    // by nullptr, which has the effect of reducing the reference count for pointers to
    // the object by 1.
    auto pname = std::make_shared<std::string>("Charles Dickens"); // Points to a string object
    // ... lots of other stuff happening...
    pname = nullptr;  // Reset pname to nullptr and decrements reference counter

    // You can obtain the same result by calling reset() for the shared_ptr<T> object with
    // no argument value:
    pname.reset();  // Reset to nullptr

    // You can pass a raw pointer to reset() to change what the shared pointer points to.
    // For example:
    pname.reset(new std::string{ "Jane Austen" }); // pname points to new string
    // The argument to reset() must be an address of the same type as was originally
    // stored in the smart pointer, or must be implicitly convertible to that type.
  }

  {
    auto pA = std::make_shared<std::string>("Charles Dickens");
    auto pB = std::make_shared<std::string>("Jane Austen");

    // Comparint shared pointers:
    if((pA == pB) && (pA != nullptr))
      std::cout << " Both pointers point to the same object.\n";
    else
      std::cout << " Both pointers do not point to the same object.\n";

    // implicitly converted to type bool
    if(pA && (pA == pB))
      std::cout << " Both pointers point to the same object.\n";
    else
      std::cout << " Both pointers do not point to the same object.\n";
  }

  {
    // You can also check whether a shared_ptr<T> object has any duplicates:
    auto pname = std::make_shared<std::string>("Charles Dickens");
    if (pname.unique())
      std::cout << "there is only one... " << std::endl;
    else
      std::cout << "there is more than one... " << std::endl;

    // The use_count() member return the number of instances. Returns 0 if the
    // share_ptr<T> object contains nullptr.
    std::cout << pname.use_count() << std::endl;
  }

  {
    // weak_ptr<T> Pointers

    // A weak_ptr<T> object can only be created from a shared_ptr<T> object. weak_ptr<T>
    // pointers are typically used as class members that store an address of another
    // instance of the same class, when objects of the class are created in the free
    // store. Using a shared_ptr<T> member to point to another object of the same type in
    // such circumstances has the potential for creating a reference cycle, which would
    // prevent objects of the class type from being deleted from the free store
    // automatically.

    auto pData
      = std::make_shared<double>(); // Create a shared pointer to an object of type double
    std::weak_ptr<double> pwData{ pData };   // Create a weak pointer from shared pointer
    std::weak_ptr<double> pwData2{ pwData }; // Create a weak pointer from another

    // Thus you can create a weak_ptr<T> from a shared_ptr<T> or from an existing
    // weak_ptr<T>. You can’t do very much with a weak pointer – you can’t dereference it
    // to access the object it points to, for example. You can do two things with a
    // weak_ptr<T> object:

    // 1. You can test whether the object it points to still exists, which means there’s a
    // shared_ptr<T> still around that points to it.

    // 2. You can create a shared_ptr<T> object from a weak_ptr<T> object.

    // Here’s how you can test for the existence of the object that a weak pointer
    // references:
    if(pwData.expired())
      std::cout << "Object no longer exists.\n";
    else
      std::cout << "Object still exists.\n";

    // You can create a shared pointer from a weak pointer like this:
    std::shared_ptr<double> pNew {pwData.lock()};

    // The lock() function locks the object if it exists by returning a new shared_ptr<X>
    // object that initializes pNew. If the object does not exist, the lock() function
    // will return a shared_ptr<X> object containing nullptr.

    if(pNew)
      std::cout << "Shared pointer to object created.\n";
    else
      std::cout << "Object no longer exists.\n";
  }

  {
    // Function objects – which are also referred to as functors – are objects of classes
    // that overload the function call operator, operator()()

    class Volume {
    public:
      double operator()(double x, double y, double z)
      {
        return x * y * z;
      }
    };

    Volume volume;                      // Create a functor
    double room{ volume(16, 12, 8.5) }; // Room volume in cubic feet

    std::cout << room << std::endl;
  }

  {
    class Volume;

    class Box {
      double length, width, height;
    public:
      Box(double length, double width, double height)
        : length(length)
        , width(width)
        , height(height)
      {
      }

      double getLength() const {
        return length;
      }

      double getWidth() const {
        return width;
      }

      double getHeight() const {
        return height;
      }
    };

    // Multiple call operators:
    class Volume {
    public:
      double operator()(double x, double y, double z)
      {
        return x * y * z;
      }

      double operator()(const Box& box)
      {
        return box.getLength() * box.getWidth() * box.getHeight();
      }
    };

    Box box{3.5, 2.0, 3.0};
    Volume volume;
    std::cout << "The volume of the box is " << volume(box) << "." << std::endl;
  }

  {
    // You can also specify default values for parameters in a lambda expression. You can
    // specify the return type using the trailing return type syntax. In general, you
    // don’t know the type of a lambda expression. There’s no generic “lambda expression
    // type.”
    auto cube_me1 = [] (double value = 5.0)           { return value*value*value; };
    auto cube_me2 = [] (double value = 5.0) -> double { return value*value*value; };

    double x{2.5};
    std::cout << x << " cubed is " << cube_me1(x) << std::endl;
    std::cout << x << " cubed is " << cube_me1(x) << std::endl;
    std::cout << "5.0 cubed is " << cube_me1() << std::endl;
  }

  {
    int data[] {1, 2, 3, 4};
    change(std::begin(data), std::end(data), [] (int value){ return value*value; });

    for (auto item : data)
      std::cout << item << " "; // 1 4 9 16
    std::cout << std::endl;

    // The functional header in the Standard Library defines a template type,
    // std::function<>, that is a wrapper for any kind of pointer to a function with a
    // given set of return and parameter types. The type argument for the std::function
    // template is of the form Return_Type(Param_Types).
    std::function<double(double)> cube { [] (double value) { return value*value*value; } };

    double x{2.5};
    std::cout << x << " cubed is " << cube(x) << std::endl;
  }

  {
    // [capture_list](parameter_list) mutable -> return_type {body}

    // '=' -> copy; by value. You can modify the copy of a variable in the enclosing scope
    // from within the lambda if you add the mutable keyword to the lambda definition
    // following the parentheses enclosing the parameter list. A lambda remembers the
    // local value of the copy of a variable captured by value from one execution of the
    // lambda to the next, so the copy is effectively static

    // & -> by reference. Values can be changed by the code in the body of the lambda. The
    // mutable keyword is not necessary in this case.

    // [=, &factor] -> access to factor by reference and any other variables in the
    // enclosing scope by value

    // [&, factor] -> captures factor by value and all other variables by reference. You
    // would also need to specify the mutable keyword to modify the copy of factor.

    // Warning: Capturing all the variables in the enclosing scope by value in a lambda
    // expression can add a lot of overhead because they will each have a copy created –
    // whether or not you refer to them. It’s much more sensible to capture only those
    // that you need.
  }
}
