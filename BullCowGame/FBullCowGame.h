/* The game logic (no view code or direct user interaction)
the game is a simple guess the word game based on mastermind*/

#pragma once
#include <string>

// to make syntax unreal friendly
using FString = std::string;
using int32 = int;


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

enum class EDifficultyStatus
{
	Invalid_status,
	OK,
	Not_number,
	Not_difficultyLevel,
};



class FBullCowGame {
public:
	FBullCowGame(); // constructor
	int32 GetCurrentTry() const;
	bool GameStatus() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus checkGuessValidity(FString) const;
	EDifficultyStatus checkDifficultyValidity(FString) const;
	FString GetHiddenWord(int32) const;
	int32 GetMaxLevel() const;
	int32 GetMinLevel() const;
	
	
	void Reset(int32); 
	
	FBullCowCount SubmitValidGuess(FString);


// please try and ignore this and focus on the inface above
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	int32 MyMinLevel;
	int32 MyMaxLevel;
	bool bIsGameWon;
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsDigit(FString) const;
	bool IsValidLevel(FString) const;
};