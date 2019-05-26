#pragma once
#include <map>
#include "FBullCowGame.h"
#define TMap std::map // to make more Unreal friendly

FBullCowGame::FBullCowGame()
{ 
	MyCurrentTry = 0;
	bGameIsWon = false;
	Reset();
}

// const makes the method immutable
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if guess isn't isogram, return error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if guess isn't all lowercase, return error
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong, return error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}

	// otherwise, return OK
	return EGuessStatus::OK;
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	++MyCurrentTry;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength(); // assuming the same length as the guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; ++MHWChar)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; ++GChar)
		{
			// if they match then
			if (MyHiddenWord[MHWChar] == Guess[GChar])
			{
				// if they're in the same place, increment Bulls. Otherwise, Cows.
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
				break;
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 or 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		// make lowercase to support mixed case
		Letter = tolower(Letter);
		// if the key already exists in the map
		if (LetterSeen[Letter])
		{
			// it's not an isogram, return false
			return false;
		}

		// otherwise, insert it
		LetterSeen[Letter] = true;
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}
