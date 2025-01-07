#include <iostream>
#include <string>
#include <regex>
#include <vector> 

int main() {
  std::string s {"Hello, World"};
  std::regex r {s};
  std::string blank {"____________"}; // Same length as "Hello, World"

//  r = "l";

  std::smatch smtch;
  std::regex_match(s, smtch, std::regex{"l"});

/* Want to figure out how to make one character in a string equal to the character in the same position of another string 
(eg "____" comapred to "abcd" and turn "____" into "_b__") */

  std::cout << "std::regex_match('Hello, World', r) returns " << smtch.str() << '\n';
  std::cout << "s has the value: " << s << '\n';

//  blank[smtch.position(0)] = s[smtch.position(0)];
//  std::cout << "replacement attempt leads to: " << blank << '\n';

  char {'l'};

  std::vector<size_t> c_in_s;
  size_t pos {s.find(c)};

  while (pos != std::string::npos) {
    c_in_s.push_back(pos);
    pos = s.find(c, pos + 1);
  } 

  std::cout << "The indicies of c in s are:";
    for (size_t index : c_in_s) {
    blank[index] = c;
    std::cout << ' ' << index;
  }
  std::cout << '\n';

  std::cout << "The updated blank string is: " << blank << '\n';
//  std::cout << "position of match 1: " << reveal << '\n';

  return 0;
}
