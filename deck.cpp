#include "deck.h"
#include "card.h"

#include <iostream>
#include <vector>
#include <random>		// for shuffling the deck
#include <algorithm>	// for shuffling the deck

using namespace std;

//Declare static variable
int Deck::cardsDealt = 0;


Deck::Deck() : deck() {}


Deck::~Deck()
{
}

void Deck::assignCardsToDeck()
{
	int value = 0;

	//put Diamond -suit cards to the deck
	for (int i = 1; i < 14; i++)
	{
		if (1 <= i && i <= 10) value = i;
		else value = 10;						// jack, queen and king have value of 10

		Card currentCard = Card(i, 'D', value);
		deck.push_back(currentCard);
	}

	//put Club -suit cards to the deck
	for (int i = 1; i < 14; i++)
	{
		if (1 <= i && i <= 10) value = i;
		else value = 10;

		Card currentCard = Card(i, 'C', value);
		deck.push_back(currentCard);
	}

	//put Heart -suit cards to the deck
	for (int i = 1; i < 14; i++)
	{
		if (1 <= i && i <= 10) value = i;
		else value = 10;

		Card currentCard = Card(i, 'H', value);
		deck.push_back(currentCard);
	}

	//put Spade -suit cards to the deck
	for (int i = 1; i < 14; i++)
	{
		if (1 <= i && i <= 10) value = i;
		else value = 10;

		Card currentCard = Card(i, 'S', value);
		deck.push_back(currentCard);
	}
}


vector<Card> Deck::deckShuffle()
{
	// Initialize random dumber generator
	for (int i = 0; i < 5; i++)
	{
		random_device rand;
		mt19937 g(rand());

		shuffle(deck.begin(), deck.end(), rand);
	}

	cardsDealt = 0;	// restore card index to 0 -> no cards dealt, dealing restarts from first index

	return deck;
}


Card Deck::deal()
{
	Card nextCard = deck[cardsDealt];
	cardsDealt += 1;
	return nextCard;
}
