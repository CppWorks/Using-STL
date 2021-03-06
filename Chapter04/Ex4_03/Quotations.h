#ifndef QUOTATIONS_H
#define QUOTATIONS_H

#include <exception> // For out_of_range exception
#include <stdexcept>
#include <string> // For string class
#include <vector> // For vector container

class Quotations {
private:
  std::vector<std::string> quotes; // Container for the quotations

public:
  // Stores a new quotation that is created from a string literal
  Quotations& operator<<(const char* quote)
  {
    quotes.emplace_back(quote);
    return *this;
  }

  // Copies a new quotation in the vector from a string object
  Quotations& operator<<(const std::string& quote)
  {
    quotes.push_back(quote);
    return *this;
  }

  // Moves a quotation into the vector
  Quotations& operator<<(std::string&& quote)
  {
    // When you access an rvalue reference parameter in the body of a function by name, it
    // will be an lvalue, so you must use move() to pass the argument on to the
    // push_back() member of the vector as an rvalue. This will enable the object to be
    // moved all the way, with no copying.
    quotes.push_back(std::move(quote));
    return *this;
  }

  // Returns a quotation for an index
  std::string& operator[](size_t index)
  {
    if (index < quotes.size())
      return quotes[index];
    else
      throw std::out_of_range{ "Invalid index to quotations." };
  }

  size_t size() const
  {
    return quotes.size();
  } // Returns the number of quotations

  // Returns the begin iterator for the quotations
  std::vector<std::string>::iterator begin()
  {
    return std::begin(quotes);
  }

  // Returns the const begin iterator for the quotations
  std::vector<std::string>::const_iterator begin() const
  {
    return std::begin(quotes);
  }

  // Returns the end iterator for the quotations
  std::vector<std::string>::iterator end()
  {
    return std::end(quotes);
  }

  // Returns the const end iterator for the quotations
  std::vector<std::string>::const_iterator end() const
  {
    return std::end(quotes);
  }
};
#endif
