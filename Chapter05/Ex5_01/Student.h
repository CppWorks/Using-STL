// Student.h
// Student class definition for Ex5_01

#ifndef STUDENT_H
#define STUDENT_H

#include <ostream> // For output streams
#include <string>  // For string class

class Student {
private:
  std::string first{};
  std::string second{};

public:
  Student(const std::string& name1, const std::string& name2)
    : first(name1)
    , second(name2)
  {
  }
  // Move constructor
  Student(Student&& student)
    : first(std::move(student.first))
    , second(std::move(student.second))
  {
  }
  // Copy constructor
  Student(const Student& student)
    : first(student.first)
    , second(student.second)
  {
  }
  // Default constructor
  Student() {}

  // Less-than operator
  bool operator<(const Student& student) const
  {
    return second < student.second || (second == student.second && first < student.first);
  }

  friend std::ostream& operator<<(std::ostream& out, const Student& student);
};

// Insertion operator overload
inline std::ostream& operator<<(std::ostream& out, const Student& student)
{
  out << student.first + " " + student.second;
  return out;
}
#endif
