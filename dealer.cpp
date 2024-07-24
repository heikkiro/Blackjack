#include "dealer.h"

#include <iostream>


Dealer::Dealer() : DefaultPlayer()
{
}

void Dealer::showDealersCards(bool value)
{
	std::cout << "\n" << "\n" << "Dealers cards: " << std::endl;
	printCardsInHand(value);
	showHandValue(value);
	std::cout << "\n" << "\n" << "******************************************" << std::endl;
}