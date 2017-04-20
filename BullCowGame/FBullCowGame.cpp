#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString Guess) const
{
	if (false) // if the guess isnt an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the GUES ISNT ALL LOWERCASE
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())  // if guess length is wrong 
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else
	{
		return EGuessStatus::OK;
	}
		// return error

}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString ValidGuess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variabled
	FBullCowCount BullCowCount;

	// loop through letters in guess
	int32 HiddenWordLenght = MyHiddenWord.length();
	for (int32 HWChar = 0; HWChar < HiddenWordLenght; HWChar++) 
	{
		// compare letters against the hidden word 
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
	return BullCowCount;
}

bool FBullCowGame::bIsGameWon() const
{
	return false;
}
