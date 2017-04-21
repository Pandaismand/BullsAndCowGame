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
void PrintGameSummary();

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
	system("CLS");
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

	// loop asking for guesse while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.GameStatus() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		
		// submit valid guess to ghe game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	// game sumary
	PrintGameSummary();
	return;
}

// loop continually untill the player enters a valid guess
FText GetValidGuess()
{
	EGuessStatus status = EGuessStatus::Invalid_status;
	FText Guess = "";
	do {
		// get the guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Guess " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		status = BCGame.checkGuessValidity(Guess);
		switch (status) {
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please use lowercase only.\n\n";
			break;
		case EGuessStatus::Incorrect_Charakters:
			std::cout << "Please only letters only.\n\n";
			break;
		default:
			//assuming no errors
			break;
		}
	} while (status != EGuessStatus::OK); //keep looping til we get no errors
	
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n): ";
	FText Responce = "";
	std::getline(std::cin, Responce);


	return (Responce[0] == 'y' || Responce[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.GameStatus()) {
		std::cout << "CONGRATS!! you won the game.\n";
	}
	else {
		std::cout << "better luck next time. LOOOSER.\n";
	}
	return;
}
