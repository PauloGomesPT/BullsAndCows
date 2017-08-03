/*Lógica do jogo. Utiliza interface com o utilizador para 
saber o tamanho da palavra a adivinhar*/

#pragma once
#include <string>
#include <iostream>

//Sintaxe tipo Unreal
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};



class FBullCowGame
{
public:
	FBullCowGame();//construtor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	void GetHiddenWord();

	bool IsGameWon() const;
	EGuessStatus CheckValidity(FString) const;

	void Reset();
	
	//método pra contar bulls e cows e incrementar tentativa assumindo tentativa válida
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};