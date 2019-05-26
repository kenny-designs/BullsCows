/* The game logic (no view code or direct user interaction)
The game is a simple gues the word game based on Mastermind
*/

#pragma once
#include <string>

// make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// JUST SO YOU KNOW, NEVER EVER USE NAMESPACES IN HEADER FILES!

// all valued initialzed to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// C++11 allows us to use the class keyword for a strongly typed enum
// that way, we can use OK in multiple enums instead of just one
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	// constructor
	FBullCowGame();

	// const makes the method immutable
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	// values set in the constructor
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
