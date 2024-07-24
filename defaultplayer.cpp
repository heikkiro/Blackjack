#include "defaultplayer.h"
#include "deck.h"
#include "card.h"

#include <vector>
#include <iostream>

//Constructor
DefaultPlayer::DefaultPlayer()
{
	this->chipAmount = 0;
	vector<Card> hand({});
}


// Add a card to player or dealers hand
void DefaultPlayer::hit(Card card)
{
	hand.push_back(card);
}


// clear the hand from cards for another round
void DefaultPlayer::clearHand()
{
	hand.clear();
}

//calculate value of the hand
int DefaultPlayer::valueOfHand()
{
	int sum = 0;
	bool cardIsAce = false;
	for (Card card : hand)
	{
		int cardsValue = card.getValue();
		if (cardsValue == 1) cardIsAce = true;
		sum += cardsValue;
	}

	if (cardIsAce == true && sum < 12) sum += 10;

	return sum;
}

// Check if player goes over 21
bool DefaultPlayer::isBust()
{
	if (valueOfHand() > 21) return true;

	else return false;
}

// Check if player has blackjack
bool DefaultPlayer::isBlackjack()
{
	if ((valueOfHand() == 21) && (hand.size() == 2)) return true;

	else return false;
}


void DefaultPlayer::printCardsInHand(bool value) 
{
	size_t range = 0;

	if (value == true)
	{
		range = hand.size();
	}

	else range = 1;

	for (int i = 0; i < range; i++)
	{
		char suit = hand[i].getSuit();
		std::string s;
		switch (suit)
		{
		case 'S':
			s = " of Spades";
			break;

		case 'D':
			s = " of Diamonds";
			break;

		case 'H':
			s = " of Hearts";
			break;

		case 'C':
			s = " of Clubs";
			break;

		}

		int n = hand[i].getNum();
		std::string literalNumber;
		switch (n)
		{
		case 1:
			literalNumber = "Ace";
			break;

		case 2:
			literalNumber = "Two";
			break;

		case 3:
			literalNumber = "Three";
			break;

		case 4:
			literalNumber = "Four";
			break;

		case 5:
			literalNumber = "Five";
			break;

		case 6:
			literalNumber = "Six";
			break;

		case 7:
			literalNumber = "Seven";
			break;

		case 8:
			literalNumber = "Eight";
			break;

		case 9:
			literalNumber = "Nine";
			break;

		case 10:
			literalNumber = "Ten";
			break;

		case 11:
			literalNumber = "Jack";
			break;

		case 12:
			literalNumber = "Queen";
			break;

		case 13:
			literalNumber = "King";
			break;

		case 0:
			literalNumber = "(no cards)";
			break;
		}

		if (n == 0)
		{
			break;
		}

		// The case when dealer has two cards and the other is not shown
		else if(value == false)
		{
			std::cout << literalNumber << s << "        " << "# Card is face down #";
			//std::cout << "(" << n << ") " << literalNumber << s << "        " << "# Card is face down #";
		}

		// Normal case when player has two or more cards and the dealer begins it's own turn
		else
		{
			std::cout << literalNumber << s << "        ";
			//std::cout << "(" << n << ") " << literalNumber << s << "        ";
		}

	}
	std::cout << std::endl;
	//std::cout << "Your hands current value is [ " << valueOfHand() << " ]" << std::endl;
}

// Prints out the current hand value
// False boolean value is used when dealer has two cards and it's still the players turn
void DefaultPlayer::showHandValue(bool value)
{
	if (value == true)
	{
		std::cout << "Current value of hand is [ " << valueOfHand() << " ]" << std::endl;
	}

	else if (value == false)
	{
		std::cout << "Current value of hand is [ *unknown* ]" << std::endl;
	}

}


double DefaultPlayer::getChipAmount()
{
	return this->chipAmount;
}


void DefaultPlayer::addToChips(double amount)
{
	this->chipAmount += amount;
}


void DefaultPlayer::takeFromChips(double amount)
{
	this->chipAmount -= amount;
}

// Checks if player has enough chips to play another round, double down or split pairs
bool DefaultPlayer::enoughToBet(double bet)
{
	if (bet <= this->chipAmount) return true;
	else return false;
}

// Function for checking if card numbers are equal for splitting pairs.
bool DefaultPlayer::equalNumCards()
{
	if (hand[0].getNum() == hand[1].getNum()) return true;

	else return false;
}