#pragma once
#include "FBullCowGame.h"
#include <map>
#define Tmap std::map



void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FBullCowGame::FBullCowGame(){Reset();}



int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const{return  MyHiddenWord.length();}

void FBullCowGame::GetHiddenWord()
{
	//Introdução Jogo
	std::cout << "\n\nBem-Vindo ao Bulls e Cows" << std::endl;
	std::cout << "          \\---/        ---" << std::endl;
	std::cout << "          (0 0)       (0 0)" << std::endl;
	std::cout << "  /--------(oo)       (oo)---------\\" << std::endl;
	std::cout << " /|  BULL   |           |    COW   |\\" << std::endl;
	std::cout << "  |-------|-|           |-|--------|" << std::endl;
	std::cout << "  | |     | |           | |      | |" << std::endl;
	std::cout << "Adivinhe a palavra de " << GetHiddenWordLength() << " letras que esta escondida!" << std::endl;
	std::cout << "Indique quantas letras tera a palavra escondida (3 a 7): \n";
	int32 escolha;
	std::cin >> escolha;
	Tmap <int32, FString> HiddenWord { { 3,"mas" },{ 4,"cabo" },{5,"ameno"},{6,"trengo"},{7,"planeta"} };
	MyHiddenWord = HiddenWord[escolha];
	std::cin.ignore();
	return ;
}

bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const 
{
	Tmap<int32, int32> WordLengthToMaxTries{ { 3,4 }, {4,7}, {5,10}, {6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::CheckValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	//Se não estiver tudo em minusculas TODO ver se está tudo em minúsculas
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	//Se não tem o mesmo comprimento 
	else if (Guess.length()!=GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	//Senão
	else
	{
		return EGuessStatus::OK;
	}
		//devolver ok

	return EGuessStatus::OK;
}

//recebe resposta válida e devolve bulls e cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length();//assumir mesmo comprimento das duas palavras

	//loop pelas letras na tentativa
	for (int32 GChar = 0; GChar < WordLenght; GChar++)
	{
		//comparar letras com a palavra escondida
		for (int32 MHWChar = 0; MHWChar < WordLenght; MHWChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				//incrementar bulls se estiverem no mesmo sitio
				if (GChar == MHWChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
				//incrementar cows se estiverem em sitios diferentes
			}
		}
	}
	if (BullCowCount.Bulls == WordLenght)
		bGameIsWon = true;
	else
		bGameIsWon = false;
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//tratar palavras de 0 ou 1 letras como isogramas
	if (Word.length() <= 1){return true; }

	//setup mapa
	Tmap <char, bool> LetterSeen;
	//loop pelas letras da palavra
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	//se alguma tiver 2 no dicionário
		//retornar falso
	//senão 
		//adicionar ao dicionário
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
}
