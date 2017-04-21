#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::GameStatus() const {return bIsGameWon;}


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isnt an isogram 
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}
	else if (!IsLowercase(Guess)) // if the GUES ISNT ALL LOWERCASE
	{
		return EGuessStatus::Not_Lowercase; //TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength())  // if guess length is wrong 
	{
		return EGuessStatus::Wrong_Lenght; //TODO write function
	}
	else
	{
		return EGuessStatus::OK;
	}
		// return error

}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString ValidGuess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variabled
	FBullCowCount BullCowCount;

	// loop through letters in hidden word
	int32 HiddenWordLenght = GetHiddenWordLength();
	for (int32 HWChar = 0; HWChar < HiddenWordLenght; HWChar++) 
	{
		// compare guess-letters against the hidden word 
		for (int32 GChar = 0; GChar < ValidGuess.length(); GChar++)
		{
			// if they match then
			if (ValidGuess[GChar] == MyHiddenWord[HWChar]){
				// if they are in the same place
				if (GChar == HWChar) {
					// increment bulls
					BullCowCount.Bulls++;
				}
				else {
					// increment cows if not
					BullCowCount.Cows++;
				}
			}
					
		}
	}
	
	if (BullCowCount.Bulls == HiddenWordLenght) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//treat 0 nad 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }

	
	TMap<char, bool> LetterSeen; //setup map
	for (auto Letter : Guess)    //for all letters of the guess
	{
		Letter = tolower(Letter);         //handle mixed case
		
		if (LetterSeen[Letter] == true) { //check if letter has been seen already
			return false; //it is not an isogram
		}
		else {
			LetterSeen[Letter] = true; // set letter as seen
		}
	} 
	return true; // f.ex in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	//treat 0 nad 1 letter words as isograms
	//if (Guess.length() <= 1) { return true; }
	
	for (auto Letter : Guess)
	{ 
		if (!islower(Letter)) {	return false; }
	}

	return true;
}

