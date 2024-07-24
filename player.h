#ifndef PLAYER_H
#define PLAYER_H

#include "defaultplayer.h"

class Player : public DefaultPlayer
{
	//constructor
public:
	Player();

	//functions
public:
	void showPlayersCards();
	Card takeCard();			// used when hand is split
	void putCard(Card card);	// Used when hand is split

};


#endif  // DEALER_H