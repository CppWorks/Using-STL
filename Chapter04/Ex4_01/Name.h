// Name.h for Ex4_01
// Defines a person's name

#ifndef NAME_H
#define NAME_H

#include <istream> // For input streams
#include <ostream> // For output streams
#include <string>  // For string class

class Name {
public:
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

  // Greater-than operator
  bool operator>(const Name& name) const
  {
    return secondName > name.secondName || (secondName == name.secondName && firstName > name.firstName);
  }

  // hash function
  size_t hash() const { return std::hash<std::string>()(firstName + secondName); }

  // equal operator
  bool operator==(const Name &name) const {
    return firstName == name.firstName && secondName == name.secondName;
  }

  friend class Name_Equal;
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

// classes Hash_Name and Name_Equal are functors! You have to specify operator()()!
class Hash_Name {
public:
  // The hash function that an unordered_map container requires must accept a
  // single argument of the same type as the key, and return the hash value as
  // type size_t.
  size_t operator()(const Name &name) const { return name.hash(); }
};

class Name_Equal {
public:
  bool operator()(const Name &name, const Name &otherName) const {
    return (name.firstName == otherName.firstName &&
            name.secondName == otherName.secondName);
  }
};

#endif
