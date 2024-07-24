#include "player.h"

#include <iostream>
#include <vector>


Player::Player() : DefaultPlayer()
{

}

void Player::showPlayersCards()
{
	std::cout << std::endl;
	std::cout << "Your cards: " << std::endl;
	printCardsInHand(true);
	showHandValue(true);
	std::cout << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
}

Card Player::takeCard()
{
	Card tempCard = hand[1];
	hand.pop_back();
	return tempCard;
}

void Player::putCard(Card card)
{
	hand.insert(hand.begin() + 0, card);
}
