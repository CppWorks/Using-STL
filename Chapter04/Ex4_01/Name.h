// Name.h for Ex4_01
// Defines a person's name

#ifndef NAME_H
#define NAME_H

#include <istream> // For input streams
#include <ostream> // For output streams
#include <string>  // For string class

class Name {
private:
  std::string firstName{};
  std::string secondName{};

public:
  Name(const std::string& name1, const std::string& name2)
    : firstName(name1)
    , secondName(name2)
  {
  }
  Name() = default;

  // Less-than operator
  bool operator<(const Name& name) const
  {
    return secondName < name.secondName || (secondName == name.secondName && firstName < name.firstName);
  }

  friend std::istream& operator>>(std::istream& in, Name& name);
  friend std::ostream& operator<<(std::ostream& out, const Name& name);
};

// Extraction operator overload
inline std::istream& operator>>(std::istream& in, Name& name)
{
  in >> name.firstName >> name.secondName;
  return in;
}

// Insertion operator overload
inline std::ostream& operator<<(std::ostream& out, const Name& name)
{
  out << name.firstName + " " + name.secondName;
  return out;
}

#endif
