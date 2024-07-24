#include "card.h"

// Constructor
Card::Card()
{
	this->num = 0;
	this->suit = 'x';
	this->value = 0;
}

// Constructor
Card::Card(int num, char suit, int value)
{
	this->num = num;
	this->suit = suit;
	this->value = value;
}


int Card::getNum() const
{
	return num;
}


char Card::getSuit() const 
{
	return suit;
}


int Card::getValue() const
{
	return value;
}