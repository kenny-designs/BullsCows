/*
This is the console executable, that makes use of the BullCow class
This acts as the view in the MVC pattern, and is responsible for all user
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to the Bulls and Cows word guessing game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n";
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "YOU GUESSED THE RIGHT WORD! YOU WIN!\n";
	}
	else
	{
		std::cout << "You lose...\n";
	}
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a word of length " << BCGame.GetHiddenWordLength() << "\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without any repeating characters!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word without any capitals!\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}
