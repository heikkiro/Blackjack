#ifndef DEFAULTPLAYER_H
#define DEFAULTPLAYER_H

#include <vector>
#include "card.h"


class DefaultPlayer 
{
public:
	DefaultPlayer();

// functions
public:
	void hit(Card card);	//a card that has been dealt from a deck is added to the players hand
	void clearHand();		//clear hand from cards, results in empty hand
	bool isBust();			
	bool isBlackjack();

	bool enoughToBet(double bet);
	double getChipAmount();
	void addToChips(double amount);
	void takeFromChips(double amount);

	int valueOfHand();
	void showHandValue(bool value);
	bool equalNumCards();

	void printCardsInHand(bool value); 


public:
	
	std::vector<Card> hand;
	Card card;

protected:
	double chipAmount;
};


#endif	//DEFAULTPLAYER_H
