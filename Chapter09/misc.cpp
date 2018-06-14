#include "../Chapter04/Ex4_01/Name.h"

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
#include <iomanip>

// As you know, a stream iterator is a single pass iterator - it can be used only once -
// that reads from a stream if it’s an input stream iterator or writes to a stream if it’s
// an output stream iterator. A stream iterator can only transfer data of one given type
// to or from a stream. If you want to use a stream iterator to transfer a series of data
// items of different types, you must arrange to package the data items into an object of
// a single type, and ensure that a stream insertion and/or extraction operator function
// for that type exists. Incrementing an input stream iterator doesn’t just shift the
// iterator to point to the next data item - it reads a value from the stream

// The type of data to be read or written is defined by the first template type argument.

int main() {
  using std::string;
  {
    // Input Stream Iterators

    // An input stream iterator is an input iterator that can extract data from a stream
    // in text mode, which implies that you cannot use it with binary streams.  Two stream
    // iterators are typically used to read all values from a stream: a begin iterator
    // that points to the first value to be read and an end iterator that points to the
    // end of the stream. The end iterator is identified when the end-of-file (EOF) stream
    // state for an input stream is recognized.

    // creating input stream iterators:
    std::istream_iterator<string> in{ std::cin }; // Reads strings from cin
    std::istream_iterator<string> end_in;         // End-of-stream iterator -  when EOF is recognized.

    {
      // defining stream iterators to read a stream that contains wchar_t characters:
      std::basic_ifstream<wchar_t> file_in{ "no_such_file.txt" }; // File stream of wchar_t
      std::istream_iterator<std::wstring, wchar_t> in{file_in};   // Reads strings of wchar_t
      std::istream_iterator<std::wstring, wchar_t> end_in;        // End-of-stream iterator
    }

    {
      // using function members to read strings:
      std::cout << "Enter one or more words. Enter ! to end:\n";
      std::istream_iterator<string> in{ std::cin };  // Reads strings from cin
      std::vector<string> words;
      while (true) {
        string word = *in; // reference to the current string object in the stream
        if (word == "!")
          break;
        words.push_back(word);
        ++in; // reads a value from the underlying input stream and stores it in the iterator object
      }
      std::cout << "You entered " << words.size() << " words." << std::endl;
    }
  }

  {
    // another way to do example 1:
    std::cout << "Enter some integers.\n";
    std::istream_iterator<int> iter{ std::cin };  // Create begin input stream iterator...
    std::istream_iterator<int> end_iter;          // Create end input stream iterator
    std::cout << "Total is " << std::accumulate(iter, end_iter, 0) << std::endl;
  }

  {
    std::cin.clear();  // Clear EOF state
    // using floats:
    std::vector<double> data;
    std::cout << "Enter some numerical values - enter Ctrl+D to end.\n";
    std::copy(std::istream_iterator<double>{ std::cin }, std::istream_iterator<double>{},
              std::back_inserter(data));
  }

  {
    std::cin.clear();  // Clear EOF state
    // using vector container constructor that accepts a range to initialize the elements:
    std::cout << "Enter some numerical values - enter Ctrl+D to end.\n";
    std::vector<double> data{ std::istream_iterator<double>{ std::cin },
                              std::istream_iterator<double>{} };
  }

  {
    // Output Stream Iterators

    // Output stream iterators are defined by the ostream_iterator template that has a
    // first template parameter that is the type of value to be written and a second
    // template parameter that is the type of characters in the stream; the second
    // template parameter has a default value of char.

    //  If you write to a stream in text mode that you subsequently intend to read in text
    //  mode, you need delimiters between the values in the stream.
  }

  {
    std::cin.clear();  // Clear EOF state

    // Overloading the Insertion and Extraction Operators

    // see included file "../Chapter04/Ex4_01/Name.h":
    std::cout << "Enter names as first-name second-name. Enter Ctrl+D on a separate line "
                 "to end:\n";
    std::vector<Name> names{ std::istream_iterator<Name>{ std::cin },
                             std::istream_iterator<Name>{} };
    std::copy(std::begin(names), std::end(names),
              std::ostream_iterator<Name>{ std::cout, " " });
  }

  {
    // testing the actual type of the ostream object:

    /*
    inline std::ostream& operator<<(std::ostream& out, const Name& name)
    {
      if (typeid(out) != typeid(std::ostream))
        return out << name.first_name << " " << name.second_name;
      else
        return out << "Name: " << name.first_name << ' ' << name.second_name;
    }
    */

    // Now a name is prefixed with "Name: " only when it is written to a stream that is an
    // ostream object. For output to a file stream, or other type of stream derived from
    // ostream, the prefix is omitted.
  }

  {
    // Using Stream Iterators with Files

    // You can transfer data to and from a stream in text mode or in binary mode. The
    // stream iterators only work in text mode so you cannot use a stream iterator to read
    // or write a binary file.  In binary mode there’s no data conversion; bytes in memory
    // are written directly to file and vice versa.

    // File Stream Class Templates

    // There are three class templates that represent file streams: IFSTREAM that
    // represents a file input stream, OFSTREAM that defines file streams for output, and
    // FSTREAM that defines file streams you can both read and write. The file stream
    // templates inherit from istream and/or ostream so in text mode they work in the same
    // way as the standard streams.

    // What you can do with a file stream is determined by its open mode. Are defined in
    // the ios_base class:
    // binary - if not set text mode is used
    // app (append)
    // ate (At The End) - moves to end of file after opening
    // in (read)
    // out (write)
    // trunc (truncates existing file to zero length)

    {
      std::cin.clear();  // Clear EOF state

      // Stream Iterators and Algorithms

      // You can use stream iterators to specify the data source for any algorithm that
      // accepts input iterators to specify the data source. If an algorithm requires
      // forward, bidirectional, or random access iterators to define the input, you can’t
      // use stream iterators. When an algorithm accepts an output iterator as a
      // destination, it can be an output stream iterator.
      string file_in{ "dictionary.txt" };
      std::ifstream in{ file_in };
      if (!in) {
        std::cerr << file_in << " not open." << std::endl;
        exit(1);
      }

      std::map<char, size_t> word_counts;
      size_t perline{ 9 };
      // Get the words counts for each initial letter
      std::for_each(std::istream_iterator<string>{ in }, std::istream_iterator<string>{},
                    [&word_counts](const string& s) { word_counts[s[0]]++; });
      std::for_each(std::begin(word_counts), std::end(word_counts),
                    // Write out the counts
                    [perline](const std::pair<char, size_t>& pr) {
                      std::cout << pr.first << ": " << std::setw(5) << pr.second
                                << (((pr.first - 'a' + 1) % perline) ? " " : "\n");
                    });
      std::cout << std::endl;
    }
  }

  {
    // Stream Buffer Iterators

    // Stream buffer iterators are different from stream iterators in that they only
    // transfer characters to or from a stream buffer. They access the buffer for a stream
    // directly, so the insertion and extraction operators are not involved. There’s no
    // data conversion and there’s no need for delimiters in the data, although if there
    // are delimiters you can deal with them yourself. Because they read or write
    // characters with no data conversion, stream buffer iterators can work with binary
    // files.

    // Input Stream Buffer Iterators

    // passing the stream object to the constructor:
    std::istreambuf_iterator<char> in{ std::cin };
    // the end-of-stream iterator is produced by the default constructor:
    std::istreambuf_iterator<char> end_in;

    // Whatever you enter will be output
    std::cout << "Enter something: ";
    string rubbish{ in, end_in };
    std::cout << rubbish << std::endl;
  }

  {
    // dereferencing in in the loop expression demonstrates that it does not change the
    // iterator; as long as it’s not '*', the same character is read again in the loop
    // body before the iterator is incremented

    // Whatever you entered up to '*' or EOF
    std::istreambuf_iterator<char> in{ std::cin };
    std::istreambuf_iterator<char> end_in;
    char end_ch{ '*' };
    string rubbish;
    while (in != end_in && *in != end_ch)
      rubbish += *in++;
    std::cout << rubbish << std::endl;
  }

  {
    // Output Stream Buffer Iterators

    // You can create an ostreambuf_iterator object to write characters of a given type to
    // a stream by passing a stream object to the constructor:

    string file_name{ "junk.txt" };
    std::ofstream junk_out{ file_name };
    std::ostreambuf_iterator<char> out{ junk_out };

    // You can also create an output stream buffer object by passing the address of a
    // stream buffer to the constructor. You can produce object out above by writing:
    std::ostreambuf_iterator<char> out2{ junk_out.rdbuf() };
    // The rdbuf() member of the ofstream object returns the address of the internal
    // buffer for the stream.

    // to write characters of a different type, e.g. Unicode:
    string file_name1 {"words.txt"};
    // you can’t use ofstream because ofstream is an alias for type basic_ofstream<char>
    std::basic_ofstream<char32_t> words_out {file_name};
    std::ostreambuf_iterator<char32_t> out1 {words_out};

    // assignment operator of an ostreambuf_iterator object:
    string ad{ "Now is the discount of our winter tents!\n" };
    std::ostreambuf_iterator<char> iter{ std::cout }; // Iterator for output to cout
    for (auto ch : ad)
      iter = ch; // Write the character to the stream

    // same result with std::copy():
    std::copy(std::begin(ad), std::end(ad), std::ostreambuf_iterator<char> {std::cout});

    // actually you would just write:
    std::cout << ad;
  }

  {
    // The stream buffer iterators don’t care how the original file was written. You could
    // define the file streams as streams of wchar_t characters, which are two byte
    // characters, like this:
    std::wifstream file_in{ "file_name" };
    std::wofstream file_out{ "file_copy", std::ios_base::out | std::ios_base::trunc };
    // You can then copy the original file as wchar_t characters:
    std::copy(std::istreambuf_iterator<wchar_t>{ file_in },
                  std::istreambuf_iterator<wchar_t>{},
                  std::ostreambuf_iterator<wchar_t>{ file_out });
    // It’s only necessary to change the template type parameter for the stream buffer
    // iterators.
  }

  {
    // String Streams and Stream and Stream Buffer Iterators

    // You can use stream iterators and stream buffer iterators to transfer data to and
    // from a string stream. Almost anything you can do with a file stream, you can also
    // do with a string stream.
  }
  return 0;
}
