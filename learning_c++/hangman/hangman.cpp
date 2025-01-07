/*
Future Changes:
	Add list of words to randomly choose from rather than user input
		Add option for user input, but hide the user input

	Allow guesses to be full words rather than just characters
		Improve validity checks on guesses
	
	Add visual (ASCII?) display of noose construction 
*/

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <limits>

// Function which sets up and initiates a new game
int playGame(){
// Setup  
 // Choose a word
  std::cout << "Write out your word here: "; // Ask user to input their chosen word
  std::string answer;			     // Create a variable to store the chosen word
  std::cin >> answer; 			     // Let the user input their word and save the chosen word as the answer
 
 // Set up progress display  
  std::string progress {""};  // Initialise a variable which shows which letters in the answer have already been guessed
  for (int c = 0; c < answer.length(); c++){
    progress.append("_");    // Progress will be displayed as a series of _'s
    }  			      
 
 // Initilisations for validity checks on guesses
  std::regex validInput {"[a-zA-Z]{1}"};  // Initialise a regex to determine if a given input is valid (a single character in this case)
  std::regex answer_regex {answer}; 	  // Initialises a variable to store the answer as a regex

  char guess {}; 		     	  // Initialise variable to store guess for this round


// Gameplay
 // Initialise Variables
  int guessNum {1};  	      // Keeps track of guess number
  int nooseConstruction {0};  // Begin building the noose to end game after enough wrong guesses
 
 // Begin while loop which ends after too many wrong guesses (10 in this case) 
  while (nooseConstruction < 10){ // nooseConstruction += 1 for each incorrect guess
				  // Game ends at 10 wrong guess

	// Check if all characters in answer have been guessed
	  if (progress == answer) { 
	    std::cout << "\nYou Win! The answer is: " << answer << '\n';
	    return 0; // End game
	  }	  

	// Display progress and answer length
	  std::cout << '\n' << progress << " (" << answer.length() << " letters)\n";

	  std::cout << "Guess " << guessNum << ": "; // Display guess number
	  std::cin >> guess; 			     // Input new guess
/*
	  std::regex guess_regex {guess};	     // Stores guess as a regex to use for comparison


	// Need to improve checks, doesn't add anything to noose if guess is wrong
	  if (guess == answer) { 
	    // If the guess is the correct answer then they win and the game ends
	    std::cout << "Correct! The answer was " << answer << ".\nYou Win!" << '\n'; 
	    return 0; // Ends game
	  } else  if (std::regex_match(guess, validInput) == false){  
	    // Provide a sense of guilt to a player when they provide an invalid guess  
	    std::cout << "OH NO OH GOD NEVER DO THAT AGAIN" << '\n'; 
	  }

	  std::smatch mtch;  // Initialise a regex match object
   		             // Will be used to find the position of matches in strings

	  std::regex_match (answer, mtch, std::regex{guess}); // Look for matches of guess in answer and store results in mtch
	  int matchCount = mtch.size(); 	 	// How many matches were there
*/

	// Update Progress
	  std::vector<size_t> guess_in_answer {};  // Initialise vector to store indexes of occurances of guess in the answer
	  size_t guess_pos { answer.find(guess) }; // Initialise var to store indexes of where guess is in the answer
						   // (The initial value stored is the first occurance of the guess, if any)

  	  while (guess_pos != std::string::npos) { 
	/* This loop seems to produce -1 at some point leading to a stack overflow. Hence we make sure to stop 
	   the loop as soon as guess_pos = -1 (= max possible occurances in a string due to stack overflow)*/

	    guess_in_answer.push_back(guess_pos);  	   // Add the position of an occurance of guess in answer
	    guess_pos = answer.find(guess, guess_pos + 1); // Begin from previous insance of guess to find the next instance 
							   // of guess in answer. Update guess_pos with this pos to repeat 
	  }
	  
	  for (size_t index : guess_in_answer) {
	    progress[index] = guess; 		 // Revels instances of guess in answer by updating respective _'s in progress
	  } 

	// Update Counters 
	  if (guess_in_answer.size() == 0) { nooseConstruction += 1; } // If they guessed incorrectly (ie no matches) build more noose
	  guessNum += 1;   				   	       // Start next guess
  } // End gameplay while loop

// Game Over
  std::cout << "\nYou Died :( \nThe answer was " << answer << ".\n"; // Display correct answer and Game Over message
  return 0; 							     // End current game 

}

int main() {

// Begin Game 
  playGame();  // Begin gameplay

// Post Game
  std::cout << "Play again? y/[n] "; // Ask to play again
  char playAgain {}; 		       // Initialise variable to store answer to "Play again?"

/* 
   Before prompting "Play again?", we need to clear the buffer from the previous std::cin since it still contains a '\n' from 
   pressing enter to complete a the previous input. '\n' is a delimiting character so will stop std::cin.get() from allowing any 
   further user input when fed in from the leftover buffer 
*/

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

/*
   The above line initiates std::cin and then tells it to ignore as many '\n's as it can. We don't need to press enter to complete this 
   command so there will be no backlogged '\n' in the buffer 
*/

  std::cin.get (playAgain); 	  // Allow input for "Play again?" (now without any backlogged '\n's from the buffer)

 // Check "Play again?" Response
  if (playAgain == 'y'){
    playGame(); }	 // If y or a phrase beginning with y is inputted, begin new game
  else { 
    return 0;    	 // If anything other than y or a phrase beginning with y is inputted, close game
  } 
 
  return 0;       	 // Closes game if if-else is exited somehow 
}  
