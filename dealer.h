#ifndef DEALER_H
#define DEALER_H

#include "defaultplayer.h"

class Dealer : public DefaultPlayer
{
//constructors
public:	
	Dealer();

//functions
public:
	void showDealersCards(bool value);
};


#endif  // DEALER_H
