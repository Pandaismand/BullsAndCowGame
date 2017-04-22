#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(1); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::GameStatus() const {return bIsGameWon;}
int32 FBullCowGame::GetMaxLevel() const { return MyMaxLevel; }
int32 FBullCowGame::GetMinLevel() const { return MyMinLevel; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

FString FBullCowGame::GetHiddenWord(int32 difficulty) const
{
	TMap<int32, FString> DificultyToHiddenWordLength{ {1,"sun"}, {2,"fire"}, {3,"coins"}, {4,"planet"} }; // setting the hidden words
	return DificultyToHiddenWordLength[difficulty];
}




int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> GuessLenghtToMaxTries{ {3,3}, {4,5}, {5,7}, {6,9} };
	return GuessLenghtToMaxTries[GetHiddenWordLength()];
}


void FBullCowGame::Reset(int32 difficulty)
{
	constexpr int32 MIN_LEVEL = 1;
	constexpr int32 MAX_LEVEL = 4;

	MyMinLevel = MIN_LEVEL;
	MyMaxLevel = MAX_LEVEL;
	MyHiddenWord = GetHiddenWord(difficulty);
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isnt an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the GUES ISNT ALL LOWERCASE
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
}

EDifficultyStatus FBullCowGame::checkDifficultyValidity(FString Input) const
{
	if (IsDigit(Input)) // if it is a digit
	{
		if (!IsValidLevel(Input)) {   //  check if its is NOT a vald level
			return EDifficultyStatus::Not_difficultyLevel; 
		}
		return EDifficultyStatus::OK;	
	}
	else
	{
		return EDifficultyStatus::Not_number;
	}

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

bool FBullCowGame::IsDigit(FString Input) const
{
	for (auto charakter : Input)
	{
		if (!isdigit(charakter)) { return false; }
	}
	return true;
}

bool FBullCowGame::IsValidLevel(FString input) const
{
		int32 selectedLevel = std::stoi(input);
		if (selectedLevel < MyMinLevel || selectedLevel > MyMaxLevel) { return false; }

	return true;
}

