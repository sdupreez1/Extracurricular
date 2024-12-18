// Want to find difference between the time it takes to print to console using std::endl vs \n

#include <iostream>
#include <chrono>

int main() {
  // Record start time (for the std::endl block of code)
  auto start_endl = std::chrono::high_resolution_clock::now();

  int x { 5 };
  std::cout << x << std::endl; // Using std::endl
 
  // Record end time taken to print using std::endl
  auto end_endl = std::chrono::high_resolution_clock::now();

  // Calculate elapsed time in milliseconds when using std::endl
  std::chrono::duration<double, std::milli> elapsed_endl = end_endl - start_endl;

  // Record start time before using \n
  auto start_n = std::chrono::high_resolution_clock::now();

  // Use \n to print to console
  std::cout << x << "\n";

  // Record end time for using \n to print to console§
  auto end_n = std::chrono::high_resolution_clock::now();

  // Calculte elapsed time for using \n
  std::chrono::duration<double, std::milli> elapsed_n = end_n - start_n;

  // Display both times and their difference
  std::cout << "Time taken when using std::endl was: " << elapsed_endl.count() << " ms\n";
  std::cout << "Time taken when using \\n was: " << elapsed_n.count() << " ms\n";
  std::cout << "Using \\n was faster by:" << elapsed_endl.count() - elapsed_n.count() << " ms\n";

  return 0;
}
