#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <unordered_set>
#include <deque>
#include <list>
#include <set>

int main() {
  {
    // Testing Element Properties

    // all_of() algorithm -> true for all
    // any_of() algorithm -> true for at least one
    // none_of() algorithm -> false for all

    // none_of()
    std::vector<int> ages{ 22, 19, 46, 75, 54, 19, 27, 66, 61, 33, 22, 19 };
    int min_age{ 18 };
    std::cout << "There are "
              << (std::none_of(std::begin(ages), std::end(ages),
                               [min_age](int age) { return age < min_age; })
                    ? "no"
                    : "some")
              << " people under " << min_age << "." << std::endl;

    // the same with any_of()
    std::cout << "There are "
              << (std::any_of(std::begin(ages), std::end(ages),
                              [min_age](int age) { return age < min_age; })
                    ? "some"
                    : "no")
              << " people under " << min_age << "." << std::endl;

    // all_of()
    int good_age{ 100 };
    std::cout << (std::all_of(std::begin(ages), std::end(ages),
                              [good_age](int age) { return age < good_age; })
                    ? "None"
                    : "Some")
              << " of the people are centenarians.";
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // The count() and count_if() algorithms tell you how many elements meet some
    // condition.

    // When you want to know the specifics - which elements in a range match - you can use
    // the find algorithms.

    // count()
    std::vector<int> ages{ 22, 19, 46, 75, 54, 19, 27, 66, 61, 33, 22, 19 };
    int the_age{ 19 };
    std::cout << "There are " << std::count(std::begin(ages), std::end(ages), the_age)
              << " people aged " << the_age << "." << std::endl;

    // count_if()
    int max_age{ 60 };
    std::cout << "There are "
              << std::count_if(std::begin(ages), std::end(ages),
                               [max_age](int age) { return age > max_age; })
              << " people aged over " << max_age << ".";
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Comparing Ranges

    // equal(): it's recommended that you always use the version of equal() that accepts
    // four arguments (begin and end iterators of both ranges) because it cannot result in
    // undefined behavior.

    // Although you can use equal() to compare the entire contents of two containers of
    // the same type, it’s better to use the operator==() member of a container to do
    // this.

    // equal() with predicate with 3 and 4 arguments:
    std::vector<std::string> r1{ "three", "two", "ten" };
    std::vector<std::string> r2{ "twelve", "ten", "twenty" };
    std::cout << std::boolalpha
              << std::equal(std::begin(r1), std::end(r1), std::begin(r2),
                            [](const std::string& s1, const std::string& s2) {
                              return s1[0] == s2[0];
                            })
              << std::endl;
    // true
    std::cout << std::boolalpha
              << std::equal(std::begin(r1), std::end(r1), std::begin(r2), std::end(r2),
                            [](const std::string& s1, const std::string& s2) {
                              return s1[0] == s2[0];
                            });
    // true
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // NOTE: You should not use equal() to compare ranges of elements from unordered map
    // or set containers. The order of a given set of elements in one unordered container
    // may well be different from an identical set of elements stored in another unordered
    // container because the allocation of elements to buckets can vary between
    // containers.
  }

  {
    // Finding Where Ranges Differ

    // The mismatch() algorithm tells you whether or not two ranges match and where they
    // differ if they don’t match. The mismatch() algorithm returns a pair object
    // containing two iterators.  When the ranges don’t match, the pair contains iterators
    // that point to the first pair of elements that do not match; thus the object will be
    // pair<iter1 + n, iter2 + n> where the elements at index n in the ranges are the
    // first elements that do not match. See the details in the documentation (p. 290).

    // When the second range is completely specified (two iterators), the shortest range
    // determines how many elements are compared.

    // mismatch() with predicate:
    std::vector<std::string> range1{ "one", "three", "five", "ten" };
    std::vector<std::string> range2{ "nine", "five", "eighteen", "seven" };
    auto pr
      = std::mismatch(std::begin(range1), std::end(range1), std::begin(range2),
                      std::end(range2), [](const std::string& s1, const std::string& s2) {
                        // compare last characters:
                        return s1.back() == s2.back();
                      });
    if (pr.first == std::end(range1) || pr.second == std::end(range2))
      std::cout << "The ranges are identical." << std::endl;
    else
      std::cout << *pr.first << " is not equal to " << *pr.second;
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Lexicographical Range Comparisons

    // lexicographical_compare() algorithm compares two ranges. The algorithm returns true
    // if the first range is lexicographically less than the second range and false
    // otherwise. Thus a false return implies that the first range is greater than or
    // equal to the second.

    std::vector<std::string> phrase1{ "the", "tigers", "of", "wrath" };
    std::vector<std::string> phrase2{ "the", "horses", "of", "instruction" };
    auto less = std::lexicographical_compare(std::begin(phrase1), std::end(phrase1),
                                             std::begin(phrase2), std::end(phrase2));
    std::copy(std::begin(phrase1), std::end(phrase1),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << (less ? "are" : "are not") << " less than ";
    std::copy(std::begin(phrase2), std::end(phrase2),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // with predicate:
    less = std::lexicographical_compare(std::begin(phrase1), std::end(phrase1),
                                        std::begin(phrase2), std::end(phrase2),
                                        [](const std::string& s1, const std::string& s2) {
                                          return s1.length() < s2.length();
                                        });
    std::copy(std::begin(phrase1), std::end(phrase1),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << (less ? "are" : "are not") << " less than ";
    std::copy(std::begin(phrase2), std::end(phrase2),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Permutations of Ranges

    // The next_permutation() algorithm generates a rearrangement of a range in place
    // that is the next permutation in lexicographic sequence of all those possible.

    // The function returns a bool value that is true when the new permutation is greater
    // than the previous arrangement of the elements and false if the previous arrangement
    // was the greatest in the sequence, thus the lexicographically smallest permutation
    // was created.

    std::vector<int> range{ 1, 2, 3 };
    do {
      std::copy(std::begin(range), std::end(range),
                std::ostream_iterator<int>{ std::cout, " " });
      std::cout << std::endl;
    } while (std::next_permutation(std::begin(range), std::end(range)));
    std::cout << std::string(50, '-') << std::endl;

    // One way to guarantee that you create all permutations is to use next_permutation()
    // to get the minimum:
    std::vector<std::string> words{
      "one",
      "two",
      "three",
    };

    while (std::next_permutation(std::begin(words), std::end(words)))
      // Change to minimum
      ;

    do {
      std::copy(std::begin(words), std::end(words),
                std::ostream_iterator<std::string>{ std::cout, " " });
      std::cout << std::endl;
    } while (std::next_permutation(std::begin(words), std::end(words)));
    std::cout << std::string(50, '-') << std::endl;

    // alternative: creating the minimum permutation
    words = { "one",  "two", "three" };
    for (auto iter = std::begin(words); iter != std::end(words) - 1; ++iter)
      std::iter_swap(iter, std::min_element(iter, std::end(words)));

    std::copy(std::begin(words), std::end(words),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // alternative: cycle till you are at the start again:
    words = { "one", "two", "three" };
    auto words_copy = words; // Copy the original
    do {
      std::copy(std::begin(words), std::end(words),
                std::ostream_iterator<std::string>{ std::cout, " " });
      std::cout << std::endl;
      std::next_permutation(std::begin(words), std::end(words));
    } while (words != words_copy); // Continue until back to the original!
    std::cout << std::string(50, '-') << std::endl;

    //  next_permutation() with a comparison function
    words = { "one", "two", "four" };
    do {
      std::copy(std::begin(words), std::end(words),
                std::ostream_iterator<std::string>{ std::cout, " " });
      std::cout << std::endl;
    } while (std::next_permutation(
      std::begin(words), std::end(words),
      // permute based on last character:
      [](const std::string& s1, const std::string& s2) { return s1.back() < s2.back(); }));
    std::cout << std::string(50, '-') << std::endl;
  }

  {
    // prev_permutation(): permutations in descending sequence. Returns false when the
    // permutation that it creates is the maximum permutation.
    std::vector<double> data{ 44.5, 22.0, 15.6 };
    do {
      std::copy(std::begin(data), std::end(data),
                std::ostream_iterator<double>{ std::cout, " " });
      std::cout << std::endl;
    } while (std::prev_permutation(std::begin(data), std::end(data)));
    std::cout << std::string(50, '-') << std::endl;
  }

  {
    // test whether one sequence is a permutation of another using the is_permutation()
    // algorithm.
    std::vector<double> data1 {44.5, 22.0, 15.6, 1.5};
    std::vector<double> data2 {22.5, 44.5, 1.5, 15.6};
    std::vector<double> data3 {1.5, 44.5, 15.6, 22.0};
    // Lambda expressions that use auto to specify the parameter types are called generic
    // lambdas.
    auto test = [](const auto& d1, const auto& d2)
      {
        std::copy(std::begin(d1), std::end(d1), std::ostream_iterator<double> {std::cout, " "});
        std::cout << (is_permutation(std::begin(d1), std::end(d1), std::begin(d2), std::end(d2)) ?
                      "is": "is not")
        << " a permutation of ";
        std::copy(std::begin(d2), std::end(d2), std::ostream_iterator<double> {std::cout, " "});
        std::cout << std::endl;
      };
    test(data1, data2);
    test(data1, data3);
    test(data3,data2);
    std::cout << std::string(50, '-') << std::endl;
  }

  {
    // is_permutation with only begin() for the second range. Be careful with second
    // ranges that are smaller than the first range. This leads to undefined behavior.
    std::vector<double> data1{ 44.5, 22.0, 15.6, 1.5 };
    std::vector<double> data3{ 1.5, 44.5, 15.6, 22.0, 88.0, 999.0 };
    std::copy(std::begin(data1), std::end(data1),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << (is_permutation(std::begin(data1), std::end(data1), std::begin(data3))
                    ? "is"
                    : "is not")
              << " a permutation of ";
    std::copy(std::begin(data3), std::end(data3),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Copying a Number of Elements

    // The copy_n() algorithm copies a specific number of elements from a source to a
    // destination. Returns an iterator that points to one past the last element copied,
    // or just the third argument - the output iterator - if the second argument is zero.
    std::vector<std::string> names{ "Al",   "Beth",   "Carol", "Dan",  "Eve",
                                    "Fred", "George", "Harry", "Iain", "Joe" };
    std::unordered_set<std::string> more_names{ "Janet", "John" };
    std::copy_n(std::begin(names) + 1, 3,
                std::inserter(more_names, std::begin(more_names)));
    std::copy(std::begin(more_names), std::end(more_names),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // of course, the destination in a copy_n() operation can be a stream iterator:
    std::copy_n(std::begin(more_names), more_names.size()-1,
                std::ostream_iterator<std::string> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;

  }

  {
    // Conditional Copying

    // The copy_if() algorithm copies elements from a source range for which a predicate
    // returns true.

    std::vector<std::string> names{ "Al",   "Beth",   "Carol", "Dan",  "Eve",
                                    "Fred", "George", "Harry", "Iain", "Joe" };
    std::unordered_set<std::string> more_names{ "Jean", "John" };
    size_t max_length{ 4 };
    std::copy_if(std::begin(names), std::end(names),
                 std::inserter(more_names, std::begin(more_names)),
                 [max_length](const std::string& s) { return s.length() <= max_length; });
    std::copy(std::begin(more_names), std::end(more_names),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // Of course, the destination for copy_if() can also be a stream iterator:
    std::copy_if(std::begin(names), std::end(names),
                 std::ostream_iterator<std::string>{ std::cout, " " },
                 [max_length](const std::string& s) { return s.length() > max_length; });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // You can use an input stream iterator as the source for the copy_if() algorithm, as
    // you can with other algorithms that require input iterators.
    std::unordered_set<std::string> names1;
    std::cout << "Enter names of less than 5 letters. Enter Ctrl+D on a separate line to end:\n";
    std::copy_if(std::istream_iterator<std::string>{std::cin}, std::istream_iterator<std::string>{},
                 std::inserter(names1, std::begin(names1)),
                 [max_length](const std::string& s) { return s.length() <= max_length; });
    std::copy(std::begin(names1), std::end(names1), std::ostream_iterator<std::string> {std::cout, " "});
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Reverse Order Copying

    // The copy_backward() algorithm copies starting from the last element and working
    // back to the first. Returns an iterator that points to the last element copied,
    // which will be the begin iterator for the range in its new position

    // You may wonder what advantages copy_backward() offers over the regular copy()
    // algorithm. -> for copying to the right of overlapping ranges. For copying to the
    // left of overlapping regions use copy().
    std::deque<std::string> song{ "jingle", "bells", "jingle", "all", "the", "way" };
    song.resize(song.size() + 2); // Add 2 elements
    std::copy_backward(std::begin(song), std::begin(song) + 6, std::end(song));
    std::copy(std::begin(song), std::end(song),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Copying and Reversing the Order of Elements

    // The reverse_copy() algorithm copies a source range to a destination range so that
    // the elements in the destination are in reverse order. Returns an output iterator
    // that points to one past the last element in the destination range.

    // The reverse() algorithm reverses the elements in the range specified by its two
    // bidirectional iterator arguments in place.
  }

  {
    // Copying a Range Removing Adjacent Duplicates

    // The unique_copy() copies one range to another while removing successive duplicate
    // elements. Returns an output iterator that points to one past the last element in
    // the destination.

    std::string text {"Have you seen how green the trees seem?"};
    std::string result{};
    std::unique_copy(std::begin(text), std::end(text), std::back_inserter(result));
    std::cout << result;
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // unique_copy with comparison function. Remove whitespace:
    text = "There's    no    air   in    spaaaaaace!";
    result = {};
    std::unique_copy(std::begin(text), std::end(text), std::back_inserter(result),
                     [](char ch1, char ch2) { return ch1 == ' ' && ch1 == ch2; });
    std::cout << result;
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // Removing Adjacent Duplicates from a Range

    // You also have the unique() algorithm available that removes duplicates from a
    // sequence in place. This requires forward iterators to specify the range to be
    // processed. It returns a forward iterator that is the end iterator for the new range
    // after removing duplicates.
    std::vector<std::string> words{ "one", "two", "two", "three", "two", "two", "two" };
    auto end_iter = std::unique(std::begin(words), std::end(words));
    std::copy(std::begin(words), end_iter,
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    {
      // it’s a good idea to truncate the original range after executing unique(). See page 305:
      std::vector<std::string> words{ "one", "two", "two", "three", "two", "two", "two" };
      auto end_iter = std::unique(std::begin(words), std::end(words));
      words.erase(end_iter, std::end(words));
      std::copy(std::begin(words), std::end(words), std::ostream_iterator<std::string> {std::cout, " "});
      std::cout << std::endl << std::string(50, '-') << std::endl;

      // Of course, you can apply unique() to characters in a string:
      std::string text{ "There's    no air in    spaaaaaace!" };
      text.erase(std::unique(std::begin(text), std::end(text),
                             [](char ch1, char ch2) { return ch1 == ' ' && ch1 == ch2; }),
                 std::end(text));
      std::cout << text;
      // Outputs: There's no air in spaaaaaace!
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }
  }

  {
    // Rotating Ranges

    // The rotate() algorithm rotates a sequence of elements left.  The algorithm returns
    // an iterator that points to the original first element in its new position.

    std::vector<std::string> words{ "one",  "two", "three", "four",
                                    "five", "six", "seven", "eight" };
    auto iter = std::rotate(std::begin(words), std::begin(words) + 3, std::end(words));
    std::copy(std::begin(words), std::end(words),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << "First element before rotation: " << *iter;
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // Of course, the range that you rotate does not have to be all the elements in a
    // container. For example:
    words = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };
    auto start = std::find(std::begin(words), std::end(words), "two");
    auto end_iter = std::find(std::begin(words), std::end(words), "eight");
    iter = std::rotate(start, std::find(std::begin(words), std::end(words), "five"),
                       end_iter);
    std::copy(std::begin(words), std::end(words),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << "First element before rotation: " << *iter;
    std::cout << std::endl << std::string(50, '-') << std::endl;
  }

  {
    // The rotate_copy() algorithm generates a rotated copy of a range in a new range,
    // leaving the original undisturbed.
    std::vector<std::string> words{ "one", "two",   "three", "four", "five",
                                    "six", "seven", "eight", "nine", "ten" };
    auto start = std::find(std::begin(words), std::end(words), "two");
    auto end_iter = std::find(std::begin(words), std::end(words), "eight");
    std::vector<std::string> words_copy;
    std::rotate_copy(start, std::find(std::begin(words), std::end(words), "five"),
                     end_iter, std::back_inserter(words_copy));
    std::copy(std::begin(words_copy), std::end(words_copy),
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // five six seven two three four
  }

  {
    // rotate_copy() returns here is the end iterator for the elements in words_copy
    std::vector<std::string> words{ "one", "two",   "three", "four", "five",
                                    "six", "seven", "eight", "nine", "ten" };
    auto start = std::find(std::begin(words), std::end(words), "two");
    auto end_iter = std::find(std::begin(words), std::end(words), "eight");
    std::vector<std::string> words_copy{ 20 };
    auto end_copy_iter
      = std::rotate_copy(start, std::find(std::begin(words), std::end(words), "five"),
                         end_iter, std::begin(words_copy));
    std::copy(std::begin(words_copy), end_copy_iter,
              std::ostream_iterator<std::string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // five six seven two three four
  }

  {
    // Moving a Range

    // The move() algorithm moves the range to a destination. This is a move operation, so
    // there is no guarantee that the input range of elements remains the same after the
    // operation; the source elements will still exist, but may not have the same values
    // so you should not use them after the move.
    std::vector<int> srce{ 1, 2, 3, 4 };
    std::deque<int> dest{ 5, 6, 7, 8 };
    std::move(std::begin(srce), std::end(srce), std::back_inserter(dest));
    std::copy(std::begin(srce), std::end(srce),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl;
    std::copy(std::begin(dest), std::end(dest),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // 5 6 7 8 1 2 3 4

    // you can do overlapping moves if they do not cross, moving left:
    std::vector<int> data{ 1, 2, 3, 4, 5, 6, 7, 8 };
    std::move(std::begin(data) + 2, std::end(data), std::begin(data));
    // Erase moved elements
    data.erase(std::end(data) - 2, std::end(data));
    std::copy(std::begin(data), std::end(data),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // 3, 4, 5, 6, 7, 8

    {
      // moving right with move_backward():
      std::deque<int> data{ 1, 2, 3, 4, 5, 6, 7, 8 };
      std::move_backward(std::begin(data), std::end(data) - 2, std::end(data));
      // Reset moved elements
      data[0] = data[1] = 0;
      std::copy(std::begin(data), std::end(data),
                std::ostream_iterator<int>{ std::cout, " " });
      std::cout << std::endl << std::string(50, '-') << std::endl;
      // 0, 0, 1, 2, 3, 4, 5, 6
    }
  }

  {
    // You can interchange two ranges using the swap_ranges() algorithm. Returns an
    // iterator for the second range that points to one past the last element swapped:
    using std::string;
    using Name = std::pair<string, string>;
    // First and second name
    std::vector<Name> people{ Name{ "Al", "Bedo" }, Name{ "Ann", "Ounce" },
                              Name{ "Jo", "King" } };
    std::list<Name> folks{ Name{ "Stan", "Down" }, Name{ "Dan", "Druff" },
                           Name{ "Bea", "Gone" } };
    std::swap_ranges(std::begin(people), std::begin(people) + 2, ++std::begin(folks));
    // There’s no operator<<() function overload for writing pair objects to a stream so
    // copy() can’t be used with an output stream iterator listing the containers. I chose
    // to use the for_each() algorithm to produce the output by applying a lambda
    // expression to each element in the containers.
    std::for_each(std::begin(people), std::end(people), [](const Name& name) {
      std::cout << '"' << name.first << " " << name.second << "\" ";
    });
    std::cout << std::endl;
    // "Dan Druff" "Bea Gone" "Jo King"
    std::for_each(std::begin(folks), std::end(folks), [](const Name& name) {
      std::cout << '"' << name.first << " " << name.second << "\" ";
    });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // "Stan Down" "Al Bedo" "Ann Ounce"
  }

  {
    // Removing Elements from a Range

    // It’s impossible to remove elements from a range without knowing their context - the
    // container in which the elements are stored. Thus the algorithms that ‘remove’
    // elements don’t, they just overwrite selected elements or omit to copy elements.

    // remove(), remove_copy(), remove_if(), remove_copy_if()

    //  remove():
    std::deque<double> samples{ 1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.1, 0.0, 6.7, 0.0 };
    // remove all 0.0's:
    samples.erase(std::remove(std::begin(samples), std::end(samples), 0.0),
                  std::end(samples));
    std::copy(std::begin(samples), std::end(samples),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // 1.5 2.6 3.1 4.1 6.7

    // Using remove_copy() when you need to retain the original range and create a new
    // range that is a copy with selected elements removed:
    samples = { 1.5, 2.6, 0.0, 3.1, 0.0, 0.0, 4.1, 0.0, 6.7, 0.0 };
    std::vector<double> edited_samples;
    std::remove_copy(std::begin(samples), std::end(samples),
                     std::back_inserter(edited_samples), 0.0);
    std::copy(std::begin(samples), std::end(samples),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl;
    std::copy(std::begin(edited_samples), std::end(edited_samples),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    // remove_if() is remove() with a predicate:
    using std::string;
    using Name = std::pair<string, string>;
    // remove blacklisted persons:
    std::set<Name> blacklist{ Name{ "Al", "Bedo" }, Name{ "Ann", "Ounce" },
                              Name{ "Jo", "King" } };
    std::deque<Name> candidates{ Name{ "Stan", "Down" }, Name{ "Al", "Bedo" },
                                 Name{ "Dan", "Druff" }, Name{ "Di", "Gress" },
                                 Name{ "Ann", "Ounce" }, Name{ "Bea", "Gone" } };
    candidates.erase(
      std::remove_if(std::begin(candidates), std::end(candidates),
                     [&blacklist](const Name& name) { return blacklist.count(name); }),
      std::end(candidates));
    std::for_each(std::begin(candidates), std::end(candidates), [](const Name& name) {
      std::cout << '"' << name.first << " " << name.second << "\" ";
    });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // "Stan Down" "Dan Druff" "Di Gress" "Bea Gone"

    {
      // the same with remove_copy_if():
      std::set<Name> blacklist{ Name{ "Al", "Bedo" }, Name{ "Ann", "Ounce" },
                                Name{ "Jo", "King" } };
      std::deque<Name> candidates{ Name{ "Stan", "Down" }, Name{ "Al", "Bedo" },
                                   Name{ "Dan", "Druff" }, Name{ "Di", "Gress" },
                                   Name{ "Ann", "Ounce" }, Name{ "Bea", "Gone" } };
      std::deque<Name> validated;
      std::remove_copy_if(
        std::begin(candidates), std::end(candidates), std::back_inserter(validated),
        [&blacklist](const Name& name) { return blacklist.count(name); });

      std::for_each(std::begin(validated), std::end(validated), [](const Name& name) {
          std::cout << '"' << name.first << " " << name.second << "\" ";
        });
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }
  }

  {
    // Setting and Modifying Elements in a Range

    // fill()
    std::vector<std::string> data {12};
    std::fill(std::begin(data), std::end(data), "none");  // Set all elements to "none"

    // fill_n(). The arguments to fill_n() are a forward iterator pointing to the first
    // element in the range to be modified, the number of elements to be modified, and the
    // value to be set.
  }

  {
    // Generating Element Values with a Function

    // generate(): The first two arguments are forward iterators that specify a range, and
    // the third argument is a function object defining a function of the form: T fun();
    // T is a type that can be assigned to an element in the range

    // To make the algorithm useful, you need to be able to generate different values to
    // be assigned to different elements within a function with no parameters. One
    // possibility is to define the third argument to generate() as a function object that
    // captures one or more external variables:
    std::string chars(30, ' '); // 30 space characters
    char ch{ 'a' };
    int incr{};
    std::generate(std::begin(chars), std::end(chars), [ch, &incr] {
      incr += 3;
      return ch + (incr % 26);
    });
    std::cout << chars;
    // chars is: dgjmpsvybehknqtwzcfiloruxadgjm
    std::cout << std::endl << std::string(50, '-') << std::endl;

    {
      // generate_n():
      std::string chars(30, ' '); // 30 space characters
      char ch{ 'a' };
      int incr{};
      std::generate_n(std::begin(chars), chars.size() / 2, [ch, &incr] {
        incr += 3;
        return ch + (incr % 26);
      });
      std::cout << chars;
      // chars is: dgjmpsvybehknqt
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }
  }

  {
    // Transforming a Range

    // transform():
    std::vector<double> deg_C{ 21.0, 30.5, 0.0, 3.2, 100.0 };
    std::vector<double> deg_F(deg_C.size());
    std::transform(std::begin(deg_C), std::end(deg_C), std::begin(deg_F),
                   [](double temp) {
                     return 32.0 + 9.0 * temp / 5.0;
                   }); // Result 69.8 86.9 32 37.76 212
    std::copy(std::begin(deg_F), std::end(deg_F),
              std::ostream_iterator<double>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;

    {
      // The same with back_insert_iterator:
      std::vector<double> deg_F;
      // Empty container
      std::transform(std::begin(deg_C), std::end(deg_C), std::back_inserter(deg_F),
                     [](double temp) {
                       return 32.0 + 9.0 * temp / 5.0;
                     }); // Result 69.8 86.9 32 37.76 212
      std::copy(std::begin(deg_F), std::end(deg_F),
                std::ostream_iterator<double>{ std::cout, " " });
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }

    {
      // The third argument can be an iterator pointing to an element in the input
      // container. For example:
      std::vector<double> temps{ 21.0, 30.5, 0.0, 3.2, 100.0 };
      std::transform(std::begin(temps), std::end(temps), std::begin(temps),
                     [](double temp) {
                       return 32.0 + 9.0 * temp / 5.0;
                     }); // Result 69.8 86.9 32 37.76 212
      std::copy(std::begin(temps), std::end(temps),
                std::ostream_iterator<double>{ std::cout, " " });
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }

    {
      // Destination range is of a different type from the input range:
      using std::string;
      std::vector<string> words{ "one", "two", "three", "four", "five" };
      std::vector<size_t> hash_values;
      std::transform(std::begin(words), std::end(words), std::back_inserter(hash_values),
                     std::hash<string>()); // string hashing function
      std::copy(std::begin(hash_values), std::end(hash_values),
                std::ostream_iterator<size_t>{ std::cout, " " });
      std::cout << std::endl << std::string(50, '-') << std::endl;

      // NOTE: Because the destination range is specified as a back_insert_iterator
      // object, the transform() algorithm here would return an iterator of type
      // back_insert_iterator<vector<size_T>> so you could not use this as the end
      // iterator for the input range to the copy() algorithm.

      {
        // To make use of the iterator that transform() returns, the code would need to
        // be:
        std::vector<string> words{ "one", "two", "three", "four", "five" };
        std::vector<size_t> hash_values(words.size());
        auto end_iter = std::transform(std::begin(words), std::end(words),
                                       std::begin(hash_values), std::hash<string>());
        std::copy(std::begin(hash_values), end_iter,
                  std::ostream_iterator<size_t>{ std::cout, " " });
        std::cout << std::endl << std::string(50, '-') << std::endl;
      }
    }

    {
      //  Calling an algorithm from within the function that is applied by the transform()
      //  function to a range of elements.
      using std::string;
      std::deque<string> names{ "Stan Laurel", "Oliver Hardy", "Harold Lloyd" };
      std::transform(
        std::begin(names), std::end(names), std::begin(names), [](string& s) {
          // calling transform in a transform.  toupper() function is defined in the
          // cctype header:
          std::transform(std::begin(s), std::end(s), std::begin(s), ::toupper);
          return s;
        });
      std::copy(std::begin(names), std::end(names),
                std::ostream_iterator<string>{ std::cout, " " });
      std::cout << std::endl << std::string(50, '-') << std::endl;
    }
  }

  {
    // Replacing Elements in a Range

    // The replace() algorithm replaces elements matching a given value with a new value.
    std::deque<int> data{ 10, -5, 12, -6, 10, 8, -7, 10, 11 };
    std::replace(std::begin(data), std::end(data), 10, 99);
    std::copy(std::begin(data), std::end(data),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // Result: 99 -5 12 -6 99 8 -7 99 11

    // The replace_if() algorithm replaces elements with a new value when a predicate
    // returns true. The parameter type is typically a const reference to the element
    // type; the const is not mandatory but the predicate should not modify the argument.
    std::string password{ "This is a good choice!" };
    std::replace_if(std::begin(password), std::end(password),
                    [](char ch) { return std::isspace(ch); }, '_');
    std::cout << password << std::endl << std::string(50, '-') << std::endl;
    // Result: This_is_a_good_choice!
  }

  {
    // The replace_copy() algorithm does what replace() does but the result is stored in
    // another range, leaving the original unchanged.
    using std::string;
    std::vector<string> words{ "one", "none", "two", "three", "none", "four" };
    std::vector<string> new_words;
    std::replace_copy(std::begin(words), std::end(words), std::back_inserter(new_words),
                      string{ "none" },
                      string{ "0" });
    std::copy(std::begin(new_words), std::end(new_words),
              std::ostream_iterator<string>{ std::cout, " " });
    std::cout << std::endl << std::string(50, '-') << std::endl;
    // Result: "one", "0", "two", "three", "0", "four"
  }

  {
    // replace_copy_if(), which does the same as replace_if() but with the result stored
    // in another range.
    std::deque<int> data{ 10, -5, 12, -6, 10, 8, -7, 10, 11 };
    std::vector<int> data_copy;
    std::replace_copy_if(std::begin(data), std::end(data), std::back_inserter(data_copy),
                         [](int value) { return value == 10; },
                         99);
    std::copy(std::begin(data_copy), std::end(data_copy),
              std::ostream_iterator<int>{ std::cout, " " });
    std::cout << std::endl;
    // Result: 99 -5 12 -6 99 8 -7 99 11
  }
  return 0;
}
