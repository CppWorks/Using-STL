// Ex9_10.cpp
// Using a string stream as the dictionary source to anagrams of a word

#include <algorithm> // For next_permutation()
#include <fstream>   // For file streams
#include <iostream>  // For standard streams
#include <iterator>  // For iterators and begin() and end()
#include <set>       // For set container
#include <sstream>   // For string streams
#include <string>    // For string class
#include <vector>    // For vector container

using std::string;

int main()
{
  string file_in{ "dictionary.txt" };
  std::ifstream in{ file_in };
  if (!in) {
    std::cerr << file_in << " not open." << std::endl;
    exit(1);
  }
  std::stringstream instr; // String stream for file contents
  instr << in.rdbuf();

  // std::copy(std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>(),
  //                                              std::ostreambuf_iterator<char>{instr});
  in.close(); // Close the file

  std::vector<string> words;
  string word;
  auto end_iter = std::istream_iterator<string>{}; // End-of-stream iterator
  while (true) {
    std::cout << "\nEnter a word, or Ctrl+D to end: ";
    if ((std::cin >> word).eof())
      break;

    string word_copy{ word };
    do {
      instr.clear();  // Reset string stream EOF
      instr.seekg(0); // String stream position at beginning

      // Use find() to search instr for word
      if (std::find(std::istream_iterator<string>(instr), end_iter, word) != end_iter)
        words.push_back(word); // Store the word found

      std::next_permutation(std::begin(word), std::end(word));
    } while (word != word_copy);

    std::copy(std::begin(words), std::end(words),
              std::ostream_iterator<string>{ std::cout, " " });
    std::cout << std::endl;
    words.clear(); // Remove previous anagrams
  }
}
