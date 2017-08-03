/*Jogo de palavras simples que consiste em adivinhar uma palavra escondida de acordo
com tentativas fornecidas pelo utilizador até acertar ou atingir o número máximo de 
tentativas*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Sintaxe tipo Unreal
using FText = std::string;
using int32 = int;

//Protótipos funções
void PlayGame();
FText GetValidGuess();
bool AskToPlayAGame();
FBullCowGame BCGame; //criar uma instância de um jogo
void PrintGameSumary();

//Entrada Jogo
int main()
{
	bool Again = false;
	BCGame.GetHiddenWord();
	do
	{
		PlayGame();
		Again=AskToPlayAGame();
	} 
	while (Again == true);

	return 0;//Saída Jogo
}

//Joga uma única vez
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries=BCGame.GetMaxTries();
	//loop para tentativas enquanto jogo não estiver ganho
	while(!BCGame.IsGameWon()&&BCGame.GetCurrentTry()<=MaxTries)
	{
		FText Guess = GetValidGuess();

		//submeter jogada válida e receber valores de bulls e cows
		FBullCowCount BullCowcount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowcount.Bulls;
		std::cout << ". Cows = " << BullCowcount.Cows << "\n\n";	
	}

	//Indica informações do resultado da tentativa 
	PrintGameSumary();
	return;
}

//loop continuo até tentativa válida
FText GetValidGuess()
{

	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do
	{
		int32 CurTry = BCGame.GetCurrentTry();
		//Pede tentativa
		std::cout << "Tentativa " << CurTry << " de "<<BCGame.GetMaxTries ()<<". Indique a sua tentativa: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckValidity(Guess);
		//Tratatmento da palavra recebida
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Indique uma palavra de " << BCGame.GetHiddenWordLength() << " letras.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Indique uma palavra sem letras repetidas.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Indique uma palavra em minusculas.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);//continuar loop até não haver erros
	return Guess;
}

bool AskToPlayAGame()
{
	std::cout << "Quer jogar de novo com a mesma palavra? (s/n)" << std::endl;
	FText Resposta = " ";
	std::getline(std::cin, Resposta);
	return (Resposta[0] == 's' || Resposta[0] == 'S');
}

void PrintGameSumary()
{
	if (BCGame.IsGameWon())
		std::cout << "Ganhou! Bem jogado!\n";
	else
		std::cout << "Melhor sorte para a proxima!\n";

}