#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Incorrect_Charakters,
	Not_Lowercase,

};



class FBullCowGame {
public:
	FBullCowGame(); // constructor
	int32 GetCurrentTry() const;
	bool bIsGameWon() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus checkGuessValidity(FString) const;
	
	void Reset(); // TODO make a more tich return value
	
	FBullCowCount SubmitValidGuess(FString);


// please try and ignore this and focus on the inface above
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};