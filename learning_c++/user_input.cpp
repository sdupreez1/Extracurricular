#include <iostream>
#include <typeinfo>
#include <string>
#include <regex>

int main() {
  std::cout << "Please enter a number: "; // Ask user to enter a number

  std::string input ; // Initialise the variable which will become the user-inputted value. We use a string so that we can use regexes to check the input is valid later
  std::cin >> input;  // Allows user to input a value. That value will be assigned to x

  // This regex looks for any sequence of only digits, potentially followed by a decimal point, which can be followed by one or more digits 
  std::regex pattern("([0-9]*)(\.?)([0-9]+)"); 

  if (std::regex_match(input, pattern)){  // Check to make sure the inputted value was a number using the regex
    // Explain to the user that their choice was well made, implying they should be proud of themselves
    std::cout << "You entered " << input << ".\nGood choice.\n"; 
  } else {
    std::cout << "I asked for a number. \nHow foolish.\n"; // Can produce adverse user-side responses
  }

  return 0;
}
