/** this is the consel executable, that makes use of the bullCow class
this acts as a the view in a MVC pattern, and is responcible for all user interaction. 
for game logic see FBullCowGame class.

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// the entry point for our game 
int main()
{
	bool bWantsToPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bWantsToPlayAgain = AskToPlayAgain();
	} while (bWantsToPlayAgain);
	
	return 0; //exit the game
}

// Introduce the game
void PrintIntro() {
	// TODO Improve intro tekst
	//constexpr int32 GetHiddenWordLength() = 5;
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl; // TODO remvove this line

	// loop  for the number of turns asking for guesses
	// TODO change form FOR to WHile loop once we are validating guess
	for (int32 count = 1; count <= MaxTries; count++)
	{
		FText Guess = GetValidGuess();
		
		// submit valid guess to ghe game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO Add game sumary
}

// loop continually untill the player enters a valid guess
FText GetValidGuess()
{
	EGuessStatus status = EGuessStatus::Invalid_status;
	FText Guess = "";
	do {
		// get the guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Guess " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		status = BCGame.checkGuessValidity(Guess);
		switch (status) {
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please use lowercase only.\n";
			break;
		case EGuessStatus::Incorrect_Charakters:
			std::cout << "Please only letters only.\n";
			break;
		default:
			//assuming no errors
			break;
		}
		std::cout << std::endl;
	} while (status != EGuessStatus::OK); //keep looping til we get no errors
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n): ";
	FText Responce = "";
	std::getline(std::cin, Responce);


	return (Responce[0] == 'y' || Responce[0] == 'Y');
}
