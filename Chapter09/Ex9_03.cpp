// Ex9_03.cpp
// Finding anagrams of a word

#include <algorithm> // For next_permutation()
#include <fstream>   // For file streams
#include <iostream>  // For standard streams
#include <iterator>  // For iterators and begin() and end()
#include <set>       // For set container
#include <string>    // For string class
#include <vector>    // For vector container

using std::string;

int main()
{
  // Read words from the file into a set container
  string file_in{ "dictionary.txt" };
  std::ifstream in{ file_in };
  if (!in) {
    std::cerr << file_in << " not open." << std::endl;
    exit(1);
  }
  std::set<string> dictionary{ std::istream_iterator<string>(in),
                               std::istream_iterator<string>() };
  std::cout << dictionary.size() << " words in dictionary." << std::endl;

  // -----------------------------------------------------------------------

  std::vector<string> words;
  string word;
  while (true) {
    std::cout << "\nEnter a word, or Ctrl+D to end:\n";
    if ((std::cin >> word).eof())
      break;
    string word_copy{ word };
    do {
      if (dictionary.count(word))
        words.push_back(word);
      std::next_permutation(std::begin(word), std::end(word));
    } while (word != word_copy);

    std::copy(std::begin(words), std::end(words),
              std::ostream_iterator<string>{ std::cout, " " });
    std::cout << std::endl;
    words.clear(); // Remove previous permutations
  }
  in.close(); // Close the file
}
