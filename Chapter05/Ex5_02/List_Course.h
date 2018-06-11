// List_Courses.h
// Function object to output the students in a group for Ex5_02

#ifndef LIST_COURSE_H
#define LIST_COURSE_H

#include "Student.h"

#include <algorithm> // For copy()
#include <iostream>  // For standard streams
#include <iterator>  // For ostream_iterator
#include <memory>
#include <set>    // For set container
#include <string> // For string class

// A course subject
using Subject = std::string;
// A student group for a subject
using Group = std::set<std::weak_ptr<Student>, std::owner_less<std::weak_ptr<Student>>>;
// A pair representing a course
using Course = std::pair<Subject, Group>;

class List_Course {
public:
  void operator()(const Course& course)
  {
    std::cout << "\n\n"
              << course.first << "  " << course.second.size() << " students:\n  ";
    std::copy(std::begin(course.second), std::end(course.second),
              std::ostream_iterator<std::weak_ptr<Student>>(std::cout, "  "));
  }
};

inline std::ostream& operator<<(std::ostream& out, const std::weak_ptr<Student>& wss)
{
  out << *wss.lock();
  return out;
}

#endif
