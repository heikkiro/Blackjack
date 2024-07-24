#ifndef GAME_H
#define GAME_H

#include "defaultplayer.h"
#include "dealer.h"
#include "player.h"
#include "card.h"

#include <vector>
#include <string>


class Game //: public Dealer , public Player
{
public:
	Game();

	void begin();
	void playGame();
	void viewRulesAndGameplay();

};

#endif	// GAME_H